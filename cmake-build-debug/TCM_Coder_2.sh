#!/bin/bash
# TCM Simulator script first coder 

SeedIndex=$1
SNRStart=-6.0
SNREnd=10.0
SNRNumberOfPoints=1000

./TCM_Simulator 2 $SNRStart $SNREnd $SNRNumberOfPoints 0 $SeedIndex yes

for ITERATOR in {1..999}
do
	./TCM_Simulator 2 $SNRStart $SNREnd $SNRNumberOfPoints $ITERATOR $SeedIndex
done
