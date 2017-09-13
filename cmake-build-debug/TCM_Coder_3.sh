#!/bin/bash
# TCM Simulator script first coder 

SNRStart=-6.0
SNREnd=10.0
SNRNumberOfPoints=1000

./TCM_Simulator 3 $SNRStart $SNREnd $SNRNumberOfPoints 0 yes

for ITERATOR in {1..999}
do
	./TCM_Simulator 3 $SNRStart $SNREnd $SNRNumberOfPoints $ITERATOR
done
