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
	igc-5.14-ethercat.h \
	igc-5.14-orig.h \
	igc-5.15-ethercat.h \
	igc-5.15-orig.h \
	igc-6.1-ethercat.h \
	igc-6.1-orig.h \
	igc-6.4-ethercat.h \
	igc-6.4-orig.h \
	igc-6.6-ethercat.h \
	igc-6.6-orig.h \
	igc_base-5.14-ethercat.c \
	igc_base-5.14-ethercat.h \
	igc_base-5.14-orig.c \
	igc_base-5.14-orig.h \
	igc_base-5.15-ethercat.c \
	igc_base-5.15-ethercat.h \
	igc_base-5.15-orig.h \
	igc_base-5.15-orig.c \
	igc_base-5.15-orig.h \
	igc_base-6.1-ethercat.c \
	igc_base-6.1-ethercat.h \
	igc_base-6.1-orig.c \
	igc_base-6.1-orig.h \
	igc_base-6.4-ethercat.c \
	igc_base-6.4-ethercat.h \
	igc_base-6.4-orig.c \
	igc_base-6.4-orig.h \
	igc_base-6.6-ethercat.c \
	igc_base-6.6-ethercat.h \
	igc_base-6.6-orig.c \
	igc_base-6.6-orig.h \
	igc_defines-5.14-ethercat.h \
	igc_defines-5.14-orig.h \
	igc_defines-5.15-ethercat.h \
	igc_defines-5.15-orig.h \
	igc_defines-6.1-ethercat.h \
	igc_defines-6.1-orig.h \
	igc_defines-6.4-ethercat.h \
	igc_defines-6.4-orig.h \
	igc_defines-6.6-ethercat.h \
	igc_defines-6.6-orig.h \
	igc_diag-5.14-ethercat.c \
	igc_diag-5.14-ethercat.h \
	igc_diag-5.14-orig.c \
	igc_diag-5.14-orig.h \
	igc_diag-5.15-ethercat.c \
	igc_diag-5.15-ethercat.h \
	igc_diag-5.15-orig.c \
	igc_diag-5.15-orig.h \
	igc_diag-6.1-ethercat.c \
	igc_diag-6.1-ethercat.h \
	igc_diag-6.1-orig.c \
	igc_diag-6.1-orig.h \
	igc_diag-6.4-ethercat.c \
	igc_diag-6.4-ethercat.h \
	igc_diag-6.4-orig.c \
	igc_diag-6.4-orig.h \
	igc_diag-6.6-ethercat.c \
	igc_diag-6.6-ethercat.h \
	igc_diag-6.6-orig.c \
	igc_diag-6.6-orig.h \
	igc_dump-5.14-ethercat.c \
	igc_dump-5.14-orig.c \
	igc_dump-5.15-ethercat.c \
	igc_dump-5.15-orig.c \
	igc_dump-6.1-ethercat.c \
	igc_dump-6.1-orig.c \
	igc_dump-6.4-ethercat.c \
	igc_dump-6.4-orig.c \
	igc_dump-6.6-ethercat.c \
	igc_dump-6.6-orig.c \
	igc_ethtool-5.14-ethercat.c \
	igc_ethtool-5.14-orig.c \
	igc_ethtool-5.15-ethercat.c \
	igc_ethtool-5.15-orig.c \
	igc_ethtool-6.1-ethercat.c \
	igc_ethtool-6.1-orig.c \
	igc_ethtool-6.4-ethercat.c \
	igc_ethtool-6.4-orig.c \
	igc_ethtool-6.6-ethercat.c \
	igc_ethtool-6.6-orig.c \
	igc_hw-5.14-ethercat.h \
	igc_hw-5.14-orig.h \
	igc_hw-5.15-ethercat.h \
	igc_hw-5.15-orig.h \
	igc_hw-6.1-ethercat.h \
	igc_hw-6.1-orig.h \
	igc_hw-6.4-ethercat.h \
	igc_hw-6.4-orig.h \
	igc_hw-6.6-ethercat.h \
	igc_hw-6.6-orig.h \
	igc_i225-5.14-ethercat.c \
	igc_i225-5.14-ethercat.h \
	igc_i225-5.14-orig.c \
	igc_i225-5.14-orig.h \
	igc_i225-5.15-ethercat.c \
	igc_i225-5.15-ethercat.h \
	igc_i225-5.15-orig.c \
	igc_i225-5.15-orig.h \
	igc_i225-6.1-ethercat.c \
	igc_i225-6.1-ethercat.h \
	igc_i225-6.1-orig.c \
	igc_i225-6.1-orig.h \
	igc_i225-6.4-ethercat.c \
	igc_i225-6.4-ethercat.h \
	igc_i225-6.4-orig.c \
	igc_i225-6.4-orig.h \
	igc_i225-6.6-ethercat.c \
	igc_i225-6.6-ethercat.h \
	igc_i225-6.6-orig.c \
	igc_i225-6.6-orig.h \
	igc_mac-5.14-ethercat.c \
	igc_mac-5.14-ethercat.h \
	igc_mac-5.14-orig.c \
	igc_mac-5.14-orig.h \
	igc_mac-5.15-ethercat.c \
	igc_mac-5.15-ethercat.h \
	igc_mac-5.15-orig.c \
	igc_mac-5.15-orig.h \
	igc_mac-6.1-ethercat.c \
	igc_mac-6.1-ethercat.h \
	igc_mac-6.1-orig.c \
	igc_mac-6.1-orig.h \
	igc_mac-6.4-ethercat.c \
	igc_mac-6.4-ethercat.h \
	igc_mac-6.4-orig.c \
	igc_mac-6.4-orig.h \
	igc_mac-6.6-ethercat.c \
	igc_mac-6.6-ethercat.h \
	igc_mac-6.6-orig.c \
	igc_mac-6.6-orig.h \
	igc_main-5.14-ethercat.c \
	igc_main-5.14-orig.c \
	igc_main-5.15-ethercat.c \
	igc_main-5.15-orig.c \
	igc_main-6.1-ethercat.c \
	igc_main-6.1-orig.c \
	igc_main-6.4-ethercat.c \
	igc_main-6.4-orig.c \
	igc_main-6.6-ethercat.c \
	igc_main-6.6-orig.c \
	igc_nvm-5.14-ethercat.c \
	igc_nvm-5.14-ethercat.h \
	igc_nvm-5.14-orig.c \
	igc_nvm-5.14-orig.h \
	igc_nvm-5.15-ethercat.c \
	igc_nvm-5.15-ethercat.h \
	igc_nvm-5.15-orig.h \
	igc_nvm-5.15-orig.c \
	igc_nvm-6.1-ethercat.c \
	igc_nvm-6.1-ethercat.h \
	igc_nvm-6.1-orig.c \
	igc_nvm-6.1-orig.h \
	igc_nvm-6.4-ethercat.c \
	igc_nvm-6.4-ethercat.h \
	igc_nvm-6.4-orig.c \
	igc_nvm-6.4-orig.h \
	igc_nvm-6.6-ethercat.c \
	igc_nvm-6.6-ethercat.h \
	igc_nvm-6.6-orig.c \
	igc_nvm-6.6-orig.h \
	igc_phy-5.14-ethercat.c \
	igc_phy-5.14-ethercat.h \
	igc_phy-5.14-orig.c \
	igc_phy-5.14-orig.h \
	igc_phy-5.15-ethercat.c \
	igc_phy-5.15-ethercat.h \
	igc_phy-5.15-orig.h \
	igc_phy-5.15-orig.c \
	igc_phy-6.1-ethercat.c \
	igc_phy-6.1-ethercat.h \
	igc_phy-6.1-orig.c \
	igc_phy-6.1-orig.h \
	igc_phy-6.4-ethercat.c \
	igc_phy-6.4-ethercat.h \
	igc_phy-6.4-orig.c \
	igc_phy-6.4-orig.h \
	igc_phy-6.6-ethercat.c \
	igc_phy-6.6-ethercat.h \
	igc_phy-6.6-orig.c \
	igc_phy-6.6-orig.h \
	igc_ptp-5.14-ethercat.c \
	igc_ptp-5.14-orig.c \
	igc_ptp-5.15-ethercat.c \
	igc_ptp-5.15-orig.c \
	igc_ptp-6.1-ethercat.c \
	igc_ptp-6.1-orig.c \
	igc_ptp-6.4-ethercat.c \
	igc_ptp-6.4-orig.c \
	igc_ptp-6.6-ethercat.c \
	igc_ptp-6.6-orig.c \
	igc_regs-5.14-ethercat.h \
	igc_regs-5.14-orig.h \
	igc_regs-5.15-ethercat.h \
	igc_regs-5.15-orig.h \
	igc_regs-6.1-ethercat.h \
	igc_regs-6.1-orig.h \
	igc_regs-6.4-ethercat.h \
	igc_regs-6.4-orig.h \
	igc_regs-6.6-ethercat.h \
	igc_regs-6.6-orig.h \
	igc_tsn-5.14-ethercat.c \
	igc_tsn-5.14-ethercat.h \
	igc_tsn-5.14-orig.c \
	igc_tsn-5.14-orig.h \
	igc_tsn-5.15-ethercat.c \
	igc_tsn-5.15-ethercat.h \
	igc_tsn-5.15-orig.h \
	igc_tsn-5.15-orig.c \
	igc_tsn-6.1-ethercat.c \
	igc_tsn-6.1-ethercat.h \
	igc_tsn-6.1-orig.c \
	igc_tsn-6.1-orig.h \
	igc_tsn-6.4-ethercat.c \
	igc_tsn-6.4-ethercat.h \
	igc_tsn-6.4-orig.c \
	igc_tsn-6.4-orig.h \
	igc_tsn-6.6-ethercat.c \
	igc_tsn-6.6-ethercat.h \
	igc_tsn-6.6-orig.c \
	igc_tsn-6.6-orig.h \
	igc_xdp-5.14-ethercat.c \
	igc_xdp-5.14-ethercat.h \
	igc_xdp-5.14-orig.c \
	igc_xdp-5.14-orig.h \
	igc_xdp-5.15-ethercat.c \
	igc_xdp-5.15-ethercat.h \
	igc_xdp-5.15-orig.h \
	igc_xdp-5.15-orig.c \
	igc_xdp-6.1-ethercat.c \
	igc_xdp-6.1-ethercat.h \
	igc_xdp-6.1-orig.c \
	igc_xdp-6.1-orig.h \
	igc_xdp-6.4-ethercat.c \
	igc_xdp-6.4-ethercat.h \
	igc_xdp-6.4-orig.c \
	igc_xdp-6.4-orig.h \
	igc_xdp-6.6-ethercat.c \
	igc_xdp-6.6-ethercat.h \
	igc_xdp-6.6-orig.c \
	igc_xdp-6.6-orig.h
