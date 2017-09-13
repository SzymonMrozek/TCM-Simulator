
close all 

numberOfCoders = 3; 

for i = 1 : numberOfCoders
    
    system(sprintf('bash ./TCM_Coder_%d.sh',i));
    snrFile = fopen('SNR','r');
    berFile = fopen('BER','r');
    snr = fscanf(snrFile,'%f');
    ber = fscanf(berFile,'%f');
    semilogy(snr,ber,'linewidth',3);
    hold on
end

grid on
ylim([ 10^(-3), 1]);
legend('Koder 1/2','Koder 2/3','koder 3/4');
xlabel('SNR [dB]');
ylabel('BER');
title('Zale¿no¶æ BER od SNR');



