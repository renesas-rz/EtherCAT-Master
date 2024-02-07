#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Need 3 arguments: 1) kernel source dir, 2) previous version, 3) version to add"
    exit 1
fi

KERNELDIR=$1
PREVER=$2
KERNELVER=$3

IGCDIR=drivers/net/ethernet/intel/igc

FILES="igc_base.c igc_defines.h igc_diag.h igc_ethtool.c igc_hw.h igc_i225.h igc_mac.h igc_nvm.c  igc_phy.c  igc_ptp.c   igc_tsn.c  igc_xdp.c"
FILES="$FILES igc_base.h igc_diag.c igc_dump.c igc.h igc_i225.c igc_mac.c igc_main.c igc_nvm.h igc_phy.h igc_regs.h igc_tsn.h igc_xdp.h"

for f in $FILES; do
    echo $f
    o=${f/\./-$KERNELVER-orig.}
    e=${f/\./-$KERNELVER-ethercat.}
    cp -v $KERNELDIR/$IGCDIR/$f $o
    chmod 644 $o
    cp -v $o $e
    op=${f/\./-$PREVER-orig.}
    ep=${f/\./-$PREVER-ethercat.}
    diff -up $op $ep | patch -p1 --no-backup-if-mismatch $e
    sed -i s/$PREVER-ethercat.h/$KERNELVER-ethercat.h/ $e
    git add $o $e
    echo -e "\t$e \\" >> Makefile.am
    echo -e "\t$o \\" >> Makefile.am
done

echo "Don't forget to update Makefile.am!"
