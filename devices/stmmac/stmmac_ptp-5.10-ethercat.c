// SPDX-License-Identifier: GPL-2.0-only
/*******************************************************************************
  PTP 1588 clock using the STMMAC.

  Copyright (C) 2013  Vayavya Labs Pvt Ltd


  Author: Rayagond Kokatanur <rayagond@vayavyalabs.com>
*******************************************************************************/
#include "stmmac-5.10-ethercat.h"
#include "stmmac_ptp-5.10-ethercat.h"

#if IS_ENABLED(CONFIG_RZT2H_ETHSS)
#include <linux/net/renesas/rzt2h-ethss.h>
#include <linux/net/renesas/rzt2h_timer_hwtstamp.h>
#endif

/**
 * stmmac_adjust_freq
 *
 * @ptp: pointer to ptp_clock_info structure
 * @ppb: desired period change in parts ber billion
 *
 * Description: this function will adjust the frequency of hardware clock.
 */
static int stmmac_adjust_freq(struct ptp_clock_info *ptp, s32 ppb)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	unsigned long flags;
	u32 diff, addend;
	int neg_adj = 0;
	u64 adj;

	if (ppb < 0) {
		neg_adj = 1;
		ppb = -ppb;
	}

	addend = priv->default_addend;
	adj = addend;
	adj *= ppb;
	diff = div_u64(adj, 1000000000ULL);
	addend = neg_adj ? (addend - diff) : (addend + diff);

	spin_lock_irqsave(&priv->ptp_lock, flags);
	stmmac_config_addend(priv, priv->ptpaddr, addend);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	return 0;
}

/**
 * stmmac_adjust_time
 *
 * @ptp: pointer to ptp_clock_info structure
 * @delta: desired change in nanoseconds
 *
 * Description: this function will shift/adjust the hardware clock time.
 */
static int stmmac_adjust_time(struct ptp_clock_info *ptp, s64 delta)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	unsigned long flags;
	u32 sec, nsec;
	u32 quotient, reminder;
	int neg_adj = 0;
	bool xmac;

	xmac = priv->plat->has_gmac4 || priv->plat->has_xgmac;

	if (delta < 0) {
		neg_adj = 1;
		delta = -delta;
	}

	quotient = div_u64_rem(delta, 1000000000ULL, &reminder);
	sec = quotient;
	nsec = reminder;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	stmmac_adjust_systime(priv, priv->ptpaddr, sec, nsec, neg_adj, xmac);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	return 0;
}

/**
 * stmmac_get_time
 *
 * @ptp: pointer to ptp_clock_info structure
 * @ts: pointer to hold time/result
 *
 * Description: this function will read the current time from the
 * hardware clock and store it in @ts.
 */
static int stmmac_get_time(struct ptp_clock_info *ptp, struct timespec64 *ts)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	unsigned long flags;
	u64 ns = 0;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	stmmac_get_systime(priv, priv->ptpaddr, &ns);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	*ts = ns_to_timespec64(ns);

	return 0;
}

/**
 * stmmac_set_time
 *
 * @ptp: pointer to ptp_clock_info structure
 * @ts: time value to set
 *
 * Description: this function will set the current time on the
 * hardware clock.
 */
static int stmmac_set_time(struct ptp_clock_info *ptp,
			   const struct timespec64 *ts)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	unsigned long flags;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	stmmac_init_systime(priv, priv->ptpaddr, ts->tv_sec, ts->tv_nsec);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	return 0;
}

static int stmmac_enable(struct ptp_clock_info *ptp,
			 struct ptp_clock_request *rq, int on)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	struct stmmac_pps_cfg *cfg;
	int ret = -EOPNOTSUPP;
	unsigned long flags;

	switch (rq->type) {
	case PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		if (rq->perout.flags)
			return -EOPNOTSUPP;

		cfg = &priv->pps[rq->perout.index];

		cfg->start.tv_sec = rq->perout.start.sec;
		cfg->start.tv_nsec = rq->perout.start.nsec;
		cfg->period.tv_sec = rq->perout.period.sec;
		cfg->period.tv_nsec = rq->perout.period.nsec;

		spin_lock_irqsave(&priv->ptp_lock, flags);
		ret = stmmac_flex_pps_config(priv, priv->ioaddr,
					     rq->perout.index, cfg, on,
					     priv->sub_second_inc,
					     priv->systime_flags);
		spin_unlock_irqrestore(&priv->ptp_lock, flags);
		break;
	default:
		break;
	}

	return ret;
}

#if IS_ENABLED(CONFIG_RZT2H_ETHSS)
static int ethsw_timer_adjust_freq(struct ptp_clock_info *ptp, s32 ppb)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	struct renesas_rzt2h_eqos *eqos = (struct renesas_rzt2h_eqos *)(priv->plat->bsp_priv);
	unsigned long flags;
	u64 tick;
	s64 delta;
	u32 tick_diff;
	int neg_adj = 0;

	tick_diff = priv->default_addend;
	tick = (u64)tick_diff + NSEC_PER_SEC;

	delta = (s64)tick * ppb;
	delta = div_s64(delta, NSEC_PER_SEC);

	tick += delta;

	if (tick < NSEC_PER_SEC) {
		neg_adj = 1;
		tick_diff = NSEC_PER_SEC - tick;
	} else {
		tick_diff = tick - NSEC_PER_SEC;
	}

	spin_lock_irqsave(&priv->ptp_lock, flags);
	ethsw_time_adjust_inc(eqos->ethss->ethsw_base, tick_diff, neg_adj,
			      priv->plat->clk_ptp_rate, eqos->ethsw_ptp_timer);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	return 0;
}

static int ethsw_timer_adjust_time(struct ptp_clock_info *ptp, s64 delta)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	struct renesas_rzt2h_eqos *eqos = (struct renesas_rzt2h_eqos *)(priv->plat->bsp_priv);
	struct timespec64 ts;
	unsigned long flags;
	s64 now;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	ethsw_time_get(eqos->ethss->ethsw_base, &now, eqos->ethsw_ptp_timer);
	ts = ns_to_timespec64(now + delta);
	ethsw_time_set(eqos->ethss->ethsw_base, ts.tv_sec, ts.tv_nsec, eqos->ethsw_ptp_timer);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	return 0;
}

static int ethsw_timer_get_time(struct ptp_clock_info *ptp, struct timespec64 *ts)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	struct renesas_rzt2h_eqos *eqos = (struct renesas_rzt2h_eqos *)(priv->plat->bsp_priv);
	unsigned long flags;
	u64 ns = 0;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	ethsw_time_get(eqos->ethss->ethsw_base, &ns, eqos->ethsw_ptp_timer);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	*ts = ns_to_timespec64(ns);

	return 0;
}

static int ethsw_timer_set_time(struct ptp_clock_info *ptp,
				const struct timespec64 *ts)
{
	struct stmmac_priv *priv =
	    container_of(ptp, struct stmmac_priv, ptp_clock_ops);
	struct renesas_rzt2h_eqos *eqos = (struct renesas_rzt2h_eqos *)(priv->plat->bsp_priv);
	unsigned long flags;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	ethsw_time_set(eqos->ethss->ethsw_base, ts->tv_sec, ts->tv_nsec, eqos->ethsw_ptp_timer);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	return 0;
}

/* structure describing a PTP hardware clock */
static struct ptp_clock_info stmmac_ptp_clock_ops = {
	.owner = THIS_MODULE,
	.name = "stmmac ptp",
	.max_adj = 100000000,
	.n_alarm = 0,
	.n_ext_ts = 0,
	.n_per_out = 0, /* will be overwritten in stmmac_ptp_register */
	.n_pins = 0,
	.pps = 0,
	.adjfreq = ethsw_timer_adjust_freq,
	.adjtime = ethsw_timer_adjust_time,
	.gettime64 = ethsw_timer_get_time,
	.settime64 = ethsw_timer_set_time,
	.enable = stmmac_enable,
};

#else

/* structure describing a PTP hardware clock */
static struct ptp_clock_info stmmac_ptp_clock_ops = {
	.owner = THIS_MODULE,
	.name = "stmmac ptp",
	.max_adj = 62500000,
	.n_alarm = 0,
	.n_ext_ts = 0,
	.n_per_out = 0, /* will be overwritten in stmmac_ptp_register */
	.n_pins = 0,
	.pps = 0,
	.adjfreq = stmmac_adjust_freq,
	.adjtime = stmmac_adjust_time,
	.gettime64 = stmmac_get_time,
	.settime64 = stmmac_set_time,
	.enable = stmmac_enable,
};

#endif

/**
 * stmmac_ptp_register
 * @priv: driver private structure
 * Description: this function will register the ptp clock driver
 * to kernel. It also does some house keeping work.
 */
void stmmac_ptp_register(struct stmmac_priv *priv)
{
	int i;

	for (i = 0; i < priv->dma_cap.pps_out_num; i++) {
		if (i >= STMMAC_PPS_MAX)
			break;
		priv->pps[i].available = true;
	}

	if (priv->plat->ptp_max_adj)
		stmmac_ptp_clock_ops.max_adj = priv->plat->ptp_max_adj;

	stmmac_ptp_clock_ops.n_per_out = priv->dma_cap.pps_out_num;

	spin_lock_init(&priv->ptp_lock);
	priv->ptp_clock_ops = stmmac_ptp_clock_ops;

	priv->ptp_clock = ptp_clock_register(&priv->ptp_clock_ops,
					     priv->device);
	if (IS_ERR(priv->ptp_clock)) {
		netdev_err(priv->dev, "ptp_clock_register failed\n");
		priv->ptp_clock = NULL;
	} else if (priv->ptp_clock)
		netdev_info(priv->dev, "registered PTP clock\n");
}

/**
 * stmmac_ptp_unregister
 * @priv: driver private structure
 * Description: this function will remove/unregister the ptp clock driver
 * from the kernel.
 */
void stmmac_ptp_unregister(struct stmmac_priv *priv)
{
	if (priv->ptp_clock) {
		ptp_clock_unregister(priv->ptp_clock);
		priv->ptp_clock = NULL;
		pr_debug("Removed PTP HW clock successfully on %s\n",
			 priv->dev->name);
	}
}
