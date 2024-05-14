#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Need 3 arguments: 1) kernel source dir, 2) previous version, 3) version to add"
    exit 1
fi

KERNELDIR=$1
PREVER=$2
KERNELVER=$3

GENETDIR=drivers/net/ethernet/broadcom/genet

FILES="bcmgenet.c bcmgenet.h bcmgenet_wol.c bcmmii.c"

for f in $FILES; do
    echo $f
    o=${f/\./-$KERNELVER-orig.}
    e=${f/\./-$KERNELVER-ethercat.}
    cp -v $KERNELDIR/$GENETDIR/$f $o
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

cp $KERNELDIR/$GENETDIR/../unimac.h unimac-$KERNELVER-orig.h
cp $KERNELDIR/$GENETDIR/../unimac.h unimac-$KERNELVER-ethercat.h
git add unimac-$KERNELVER-orig.h unimac-$KERNELVER-ethercat.h
echo -e "\tunimac-$KERNELVER-ethercat.h \\" >> Makefile.am
echo -e "\tunimac-$KERNELVER-orig.h \\" >> Makefile.am

echo "Don't forget to update Makefile.am!"
