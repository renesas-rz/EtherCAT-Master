#------------------------------------------------------------------------------
#
#  Copyright (C) 2006-2021  Florian Pose, Ingenieurgemeinschaft IgH
#
#  This file is part of the IgH EtherCAT Master.
#
#  The IgH EtherCAT Master is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License version 2, as
#  published by the Free Software Foundation.
#
#  The IgH EtherCAT Master is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
#  Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with the IgH EtherCAT Master; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#  ---
#
#  The license mentioned above concerns the source code only. Using the
#  EtherCAT technology and brand is only permitted in compliance with the
#  industrial property and similar rights of Beckhoff Automation GmbH.
#
#------------------------------------------------------------------------------

include $(top_srcdir)/Makefile.kbuild

EXTRA_DIST = \
	e1000_82575-3.18-ethercat.c \
	e1000_82575-3.18-ethercat.h \
	e1000_82575-3.18-orig.c \
	e1000_82575-3.18-orig.h \
	e1000_82575-4.19-ethercat.c \
	e1000_82575-4.19-ethercat.h \
	e1000_82575-4.19-orig.c \
	e1000_82575-4.19-orig.h \
	e1000_82575-4.4-ethercat.c \
	e1000_82575-4.4-ethercat.h \
	e1000_82575-4.4-orig.c \
	e1000_82575-4.4-orig.h \
	e1000_82575-5.10-ethercat.c \
	e1000_82575-5.10-ethercat.h \
	e1000_82575-5.10-orig.c \
	e1000_82575-5.10-orig.h \
	e1000_82575-5.14-ethercat.c \
	e1000_82575-5.14-ethercat.h \
	e1000_82575-5.14-orig.c \
	e1000_82575-5.14-orig.h \
	e1000_82575-5.15-ethercat.c \
	e1000_82575-5.15-ethercat.h \
	e1000_82575-5.15-orig.c \
	e1000_82575-5.15-orig.h \
	e1000_82575-6.1-ethercat.c \
	e1000_82575-6.1-ethercat.h \
	e1000_82575-6.1-orig.c \
	e1000_82575-6.1-orig.h \
	e1000_defines-3.18-ethercat.h \
	e1000_defines-3.18-orig.h \
	e1000_defines-4.19-ethercat.h \
	e1000_defines-4.19-orig.h \
	e1000_defines-4.4-ethercat.h \
	e1000_defines-4.4-orig.h \
	e1000_defines-5.10-ethercat.h \
	e1000_defines-5.10-orig.h \
	e1000_defines-5.14-ethercat.h \
	e1000_defines-5.14-orig.h \
	e1000_defines-5.15-ethercat.h \
	e1000_defines-5.15-orig.h \
	e1000_defines-6.1-ethercat.h \
	e1000_defines-6.1-orig.h \
	e1000_hw-3.18-ethercat.h \
	e1000_hw-3.18-orig.h \
	e1000_hw-4.19-ethercat.h \
	e1000_hw-4.19-orig.h \
	e1000_hw-4.4-ethercat.h \
	e1000_hw-4.4-orig.h \
	e1000_hw-5.10-ethercat.h \
	e1000_hw-5.10-orig.h \
	e1000_hw-5.14-ethercat.h \
	e1000_hw-5.14-orig.h \
	e1000_hw-5.15-ethercat.h \
	e1000_hw-5.15-orig.h \
	e1000_hw-6.1-ethercat.h \
	e1000_hw-6.1-orig.h \
	e1000_i210-3.18-ethercat.c \
	e1000_i210-3.18-ethercat.h \
	e1000_i210-3.18-orig.c \
	e1000_i210-3.18-orig.h \
	e1000_i210-4.19-ethercat.c \
	e1000_i210-4.19-ethercat.h \
	e1000_i210-4.19-orig.c \
	e1000_i210-4.19-orig.h \
	e1000_i210-4.4-ethercat.c \
	e1000_i210-4.4-ethercat.h \
	e1000_i210-4.4-orig.c \
	e1000_i210-4.4-orig.h \
	e1000_i210-5.10-ethercat.c \
	e1000_i210-5.10-ethercat.h \
	e1000_i210-5.10-orig.c \
	e1000_i210-5.10-orig.h \
	e1000_i210-5.14-ethercat.c \
	e1000_i210-5.14-ethercat.h \
	e1000_i210-5.14-orig.c \
	e1000_i210-5.14-orig.h \
	e1000_i210-5.15-ethercat.c \
	e1000_i210-5.15-ethercat.h \
	e1000_i210-5.15-orig.c \
	e1000_i210-5.15-orig.h \
	e1000_i210-6.1-ethercat.c \
	e1000_i210-6.1-ethercat.h \
	e1000_i210-6.1-orig.c \
	e1000_i210-6.1-orig.h \
	e1000_mac-3.18-ethercat.c \
	e1000_mac-3.18-ethercat.h \
	e1000_mac-3.18-orig.c \
	e1000_mac-3.18-orig.h \
	e1000_mac-4.19-ethercat.c \
	e1000_mac-4.19-ethercat.h \
	e1000_mac-4.19-orig.c \
	e1000_mac-4.19-orig.h \
	e1000_mac-4.4-ethercat.c \
	e1000_mac-4.4-ethercat.h \
	e1000_mac-4.4-orig.c \
	e1000_mac-4.4-orig.h \
	e1000_mac-5.10-ethercat.c \
	e1000_mac-5.10-ethercat.h \
	e1000_mac-5.10-orig.c \
	e1000_mac-5.10-orig.h \
	e1000_mac-5.14-ethercat.c \
	e1000_mac-5.14-ethercat.h \
	e1000_mac-5.14-orig.c \
	e1000_mac-5.14-orig.h \
	e1000_mac-5.15-ethercat.c \
	e1000_mac-5.15-ethercat.h \
	e1000_mac-5.15-orig.c \
	e1000_mac-5.15-orig.h \
	e1000_mac-6.1-ethercat.c \
	e1000_mac-6.1-ethercat.h \
	e1000_mac-6.1-orig.c \
	e1000_mac-6.1-orig.h \
	e1000_mbx-3.18-ethercat.c \
	e1000_mbx-3.18-ethercat.h \
	e1000_mbx-3.18-orig.c \
	e1000_mbx-3.18-orig.h \
	e1000_mbx-4.19-ethercat.c \
	e1000_mbx-4.19-ethercat.h \
	e1000_mbx-4.19-orig.c \
	e1000_mbx-4.19-orig.h \
	e1000_mbx-4.4-ethercat.c \
	e1000_mbx-4.4-ethercat.h \
	e1000_mbx-4.4-orig.c \
	e1000_mbx-4.4-orig.h \
	e1000_mbx-5.10-ethercat.c \
	e1000_mbx-5.10-ethercat.h \
	e1000_mbx-5.10-orig.c \
	e1000_mbx-5.10-orig.h \
	e1000_mbx-5.14-ethercat.c \
	e1000_mbx-5.14-ethercat.h \
	e1000_mbx-5.14-orig.c \
	e1000_mbx-5.14-orig.h \
	e1000_mbx-5.15-ethercat.c \
	e1000_mbx-5.15-ethercat.h \
	e1000_mbx-5.15-orig.c \
	e1000_mbx-5.15-orig.h \
	e1000_mbx-6.1-ethercat.c \
	e1000_mbx-6.1-ethercat.h \
	e1000_mbx-6.1-orig.c \
	e1000_mbx-6.1-orig.h \
	e1000_nvm-3.18-ethercat.c \
	e1000_nvm-3.18-ethercat.h \
	e1000_nvm-3.18-orig.c \
	e1000_nvm-3.18-orig.h \
	e1000_nvm-4.19-ethercat.c \
	e1000_nvm-4.19-ethercat.h \
	e1000_nvm-4.19-orig.c \
	e1000_nvm-4.19-orig.h \
	e1000_nvm-4.4-ethercat.c \
	e1000_nvm-4.4-ethercat.h \
	e1000_nvm-4.4-orig.c \
	e1000_nvm-4.4-orig.h \
	e1000_nvm-5.10-ethercat.c \
	e1000_nvm-5.10-ethercat.h \
	e1000_nvm-5.10-orig.c \
	e1000_nvm-5.10-orig.h \
	e1000_nvm-5.14-ethercat.c \
	e1000_nvm-5.14-ethercat.h \
	e1000_nvm-5.14-orig.c \
	e1000_nvm-5.14-orig.h \
	e1000_nvm-5.15-ethercat.c \
	e1000_nvm-5.15-ethercat.h \
	e1000_nvm-5.15-orig.c \
	e1000_nvm-5.15-orig.h \
	e1000_nvm-6.1-ethercat.c \
	e1000_nvm-6.1-ethercat.h \
	e1000_nvm-6.1-orig.c \
	e1000_nvm-6.1-orig.h \
	e1000_phy-3.18-ethercat.c \
	e1000_phy-3.18-ethercat.h \
	e1000_phy-3.18-orig.c \
	e1000_phy-3.18-orig.h \
	e1000_phy-4.19-ethercat.c \
	e1000_phy-4.19-ethercat.h \
	e1000_phy-4.19-orig.c \
	e1000_phy-4.19-orig.h \
	e1000_phy-4.4-ethercat.c \
	e1000_phy-4.4-ethercat.h \
	e1000_phy-4.4-orig.c \
	e1000_phy-4.4-orig.h \
	e1000_phy-5.10-ethercat.c \
	e1000_phy-5.10-ethercat.h \
	e1000_phy-5.10-orig.c \
	e1000_phy-5.10-orig.h \
	e1000_phy-5.14-ethercat.c \
	e1000_phy-5.14-ethercat.h \
	e1000_phy-5.14-orig.c \
	e1000_phy-5.14-orig.h \
	e1000_phy-5.15-ethercat.c \
	e1000_phy-5.15-ethercat.h \
	e1000_phy-5.15-orig.c \
	e1000_phy-5.15-orig.h \
	e1000_phy-6.1-ethercat.c \
	e1000_phy-6.1-ethercat.h \
	e1000_phy-6.1-orig.c \
	e1000_phy-6.1-orig.h \
	e1000_regs-3.18-ethercat.h \
	e1000_regs-3.18-orig.h \
	e1000_regs-4.19-ethercat.h \
	e1000_regs-4.19-orig.h \
	e1000_regs-4.4-ethercat.h \
	e1000_regs-4.4-orig.h \
	e1000_regs-5.10-ethercat.h \
	e1000_regs-5.10-orig.h \
	e1000_regs-5.14-ethercat.h \
	e1000_regs-5.14-orig.h \
	e1000_regs-5.15-ethercat.h \
	e1000_regs-5.15-orig.h \
	e1000_regs-6.1-ethercat.h \
	e1000_regs-6.1-orig.h \
	igb-3.18-ethercat.h \
	igb-3.18-orig.h \
	igb-4.19-ethercat.h \
	igb-4.19-orig.h \
	igb-4.4-ethercat.h \
	igb-4.4-orig.h \
	igb-5.10-ethercat.h \
	igb-5.10-orig.h \
	igb-5.14-ethercat.h \
	igb-5.14-orig.h \
	igb-5.15-ethercat.h \
	igb-5.15-orig.h \
	igb-6.1-ethercat.h \
	igb-6.1-orig.h \
	igb_ethtool-3.18-ethercat.c \
	igb_ethtool-3.18-orig.c \
	igb_ethtool-4.19-ethercat.c \
	igb_ethtool-4.19-orig.c \
	igb_ethtool-4.4-ethercat.c \
	igb_ethtool-4.4-orig.c \
	igb_ethtool-5.10-ethercat.c \
	igb_ethtool-5.10-orig.c \
	igb_ethtool-5.14-ethercat.c \
	igb_ethtool-5.14-orig.c \
	igb_ethtool-5.15-ethercat.c \
	igb_ethtool-5.15-orig.c \
	igb_ethtool-6.1-ethercat.c \
	igb_ethtool-6.1-orig.c \
	igb_hwmon-3.18-ethercat.c \
	igb_hwmon-3.18-orig.c \
	igb_hwmon-4.19-ethercat.c \
	igb_hwmon-4.19-orig.c \
	igb_hwmon-4.4-ethercat.c \
	igb_hwmon-4.4-orig.c \
	igb_hwmon-5.10-ethercat.c \
	igb_hwmon-5.10-orig.c \
	igb_hwmon-5.14-ethercat.c \
	igb_hwmon-5.14-orig.c \
	igb_hwmon-5.15-ethercat.c \
	igb_hwmon-5.15-orig.c \
	igb_hwmon-6.1-ethercat.c \
	igb_hwmon-6.1-orig.c \
	igb_main-3.18-ethercat.c \
	igb_main-3.18-orig.c \
	igb_main-4.19-ethercat.c \
	igb_main-4.19-orig.c \
	igb_main-4.4-ethercat.c \
	igb_main-4.4-orig.c \
	igb_main-5.10-ethercat.c \
	igb_main-5.10-orig.c \
	igb_main-5.14-ethercat.c \
	igb_main-5.14-orig.c \
	igb_main-5.15-ethercat.c \
	igb_main-5.15-orig.c \
	igb_main-6.1-ethercat.c \
	igb_main-6.1-orig.c \
	igb_ptp-3.18-ethercat.c \
	igb_ptp-3.18-orig.c \
	igb_ptp-4.19-ethercat.c \
	igb_ptp-4.19-orig.c \
	igb_ptp-4.4-ethercat.c \
	igb_ptp-4.4-orig.c \
	igb_ptp-5.10-ethercat.c \
	igb_ptp-5.10-orig.c \
	igb_ptp-5.14-ethercat.c \
	igb_ptp-5.14-orig.c \
	igb_ptp-5.15-ethercat.c \
	igb_ptp-5.15-orig.c \
	igb_ptp-6.1-ethercat.c \
	igb_ptp-6.1-orig.c \
	update.sh

#------------------------------------------------------------------------------
