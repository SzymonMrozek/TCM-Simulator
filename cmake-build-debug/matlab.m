
close all 

numberOfCoders = 3;
numberOfSimulations = 20;

coder1 = [];
coder2 = [];
coder3 = [];

for simulation = 1 : numberOfSimulations 
    system(sprintf('bash ./TCM_Coder_1.sh %d', simulation));
    berFile = fopen('BER','r');
    coder1 = [coder1, fscanf(berFile,'%f')];
    simulation
end

ber = mean(coder1,2);
snrFile = fopen('SNR','r');
snr = fscanf(snrFile,'%f');
step = (snr(length(snr)) - snr(1))/ length(snr);
snrLight = -6:1:10;
berLightValues = [];
for i = 1 : length(snrLight)
   diff = snrLight(i) - snr(1);
   index = min(floor(diff / step) + 1, length(ber));
   berLightValues = [berLightValues; ber(index)];
end
[up, down] = confidence_interval(coder1);
semilogy(snr,ber,'linewidth',3);
hold on
upInterval = [];
downInterval = [];
upInterval(1:length(snrLight)) = up;
downInterval(1:length(snrLight)) = down;
% errorbar(snrLight, berLightValues,upInterval, downInterval);
% errorbarlogy;
grid on
ylim([ 10^(-3), 1]);
legend('Koder 1/2');
xlabel('SNR [dB]');
ylabel('BER');
title('Zale¿no¶æ BER od SNR');

for simulation = 1 : numberOfSimulations 
    system(sprintf('bash ./TCM_Coder_2.sh %d', simulation));
    berFile = fopen('BER','r');
    coder2 = [coder2, fscanf(berFile,'%f')];
    simulation
end








figure 
ber = mean(coder2,2);
snrFile = fopen('SNR','r');
snr = fscanf(snrFile,'%f');
step = (snr(length(snr)) - snr(1))/ length(snr);
snrLight = -6:1:10;
berLightValues = [];
for i = 1 : length(snrLight)
   diff = snrLight(i) - snr(1);
   index = min(floor(diff / step) + 1, length(ber));
   berLightValues = [berLightValues; ber(index)];
end
[up, down] = confidence_interval(coder2);
semilogy(snr,ber,'linewidth',3);
upInterval = [];
downInterval = [];
upInterval(1:length(snrLight)) = up;
downInterval(1:length(snrLight)) = down;
% errorbar(snrLight, berLightValues,upInterval, downInterval);
% errorbarlogy;
grid on
ylim([ 10^(-3), 1]);
legend('Koder 2/3');
xlabel('SNR [dB]');
ylabel('BER');
title('Zale¿no¶æ BER od SNR');






for simulation = 1 : numberOfSimulations 
    system(sprintf('bash ./TCM_Coder_3.sh %d', simulation));
    berFile = fopen('BER','r');
    coder3 = [coder3, fscanf(berFile,'%f')];
    simulation
end
figure 
ber = mean(coder2,2);
snrFile = fopen('SNR','r');
snr = fscanf(snrFile,'%f');
step = (snr(length(snr)) - snr(1))/ length(snr);
snrLight = -6:1:10;
berLightValues = [];
for i = 1 : length(snrLight)
   diff = snrLight(i) - snr(1);
   index = min(floor(diff / step) + 1, length(ber));
   berLightValues = [berLightValues; ber(index)];
end
[up, down] = confidence_interval(coder2);
semilogy(snr,ber,'linewidth',3);
upInterval = [];
downInterval = [];
upInterval(1:length(snrLight)) = up;
downInterval(1:length(snrLight)) = down;
% errorbar(snrLight, berLightValues,upInterval, downInterval);
% errorbarlogy;
grid on
ylim([ 10^(-3), 1]);
legend('Koder 3/4');
xlabel('SNR [dB]');
ylabel('BER');
title('Zale¿no¶æ BER od SNR');



figure 
semilogy(snr,mean(coder1,2),'linewidth',3);
hold on
semilogy(snr,mean(coder2,2),'linewidth',3);
hold on
semilogy(snr,mean(coder3,2),'linewidth',3);
grid on
ylim([ 10^(-3), 1]);
legend('Koder 1/2','Koder 2/3','Koder 3/4');
xlabel('SNR [dB]');
ylabel('BER');
title('Zale¿no¶æ BER od SNR');



