function [intervalUp, intervalDown] = confidence_interval(coderArray)


[~, numberOfSimulations] = size(coderArray);

coderMeanArray = mean(coderArray,2);
meanValue = mean(coderMeanArray);
standardDeviation = std(coderArray,1,2);
meanDeviation = mean(standardDeviation);
normalValue = 2.1448; 

intervalUp = meanValue + normalValue * meanDeviation / (sqrt(numberOfSimulations -1));
intervalDown = meanValue - normalValue * meanDeviation / (sqrt(numberOfSimulations -1));

end