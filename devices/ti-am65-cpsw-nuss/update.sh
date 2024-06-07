#!/bin/bash

set -x

KERNELDIR=/mnt/work/linux/drivers/net/ethernet/ti/
KERNELVER=6.8
PREVER=6.1

for f in *-$PREVER-orig.*; do
    b=${f/-$PREVER-orig\./.}
    o=${b/\./-$KERNELVER-orig.}
    e=${b/\./-$KERNELVER-ethercat.}
    cp -v $KERNELDIR/$b $o
    chmod 644 $o
    cp -v $o $e
    op=$f
    ep=${b/\./-$PREVER-ethercat.}
    diff -u $op $ep | patch -p1 $e
    sed -i s/$PREVER-ethercat.h/$KERNELVER-ethercat.h/ $e
    #git add $o $e
done
