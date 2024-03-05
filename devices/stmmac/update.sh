#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Need 3 arguments: 1) kernel source dir, 2) previous version, 3) version to add"
    exit 1
fi

KERNELDIR=$1
PREVER=$2
KERNELVER=$3

IGBDIR=drivers/net/ethernet/stmicro/stmmac

FILES="stmmac_main.c stmmac_ethtool.c stmmac_mdio.c ring_mode.c  \
chain_mode.c dwmac_lib.c dwmac1000_core.c dwmac1000_dma.c \
dwmac100_core.c dwmac100_dma.c enh_desc.c norm_desc.c     \
mmc_core.c stmmac_hwtstamp.c stmmac_ptp.c dwmac4_descs.c  \
dwmac4_dma.c dwmac4_lib.c dwmac4_core.c dwmac5.c hwif.c \
stmmac_tc.c dwxgmac2_core.c dwxgmac2_dma.c dwxgmac2_descs.c \
stmmac_xdp.c \
common.h \
descs.h \
descs_com.h \
dwmac1000.h \
dwmac100.h \
dwmac4_descs.h \
dwmac4_dma.h \
dwmac4.h \
dwmac5.h \
dwmac_dma.h \
dwxgmac2.h \
dwxlgmac2.h \
hwif.h \
mmc.h \
stmmac.h \
stmmac_pcs.h \
stmmac_ptp.h \
stmmac_xdp.h \
dwmac-intel.c \
dwmac-intel.h \
stmmac_pci.c"

set -x

for f in $FILES; do
    echo $f
    o=${f/\./-$KERNELVER-orig.}
    e=${f/\./-$KERNELVER-ethercat.}
    cp $KERNELDIR/$IGBDIR/$f $o
    chmod 644 $o
    cp $o $e
    op=${f/\./-$PREVER-orig.}
    ep=${f/\./-$PREVER-ethercat.}
    diff -up $op $ep | patch -p1 $e
    sed -i s/$PREVER-ethercat.h/$KERNELVER-ethercat.h/ $e
    git add $o $e
done
