#!/bin/bash
# TCM Simulator script first coder 

SeedIndex=$1
SNRStart=-6.0
SNREnd=10.0
SNRNumberOfPoints=200

./TCM_Simulator 3 $SNRStart $SNREnd $SNRNumberOfPoints 0 $SeedIndex yes

for ITERATOR in {1..199}
do
	./TCM_Simulator 3 $SNRStart $SNREnd $SNRNumberOfPoints $ITERATOR $SeedIndex
done
