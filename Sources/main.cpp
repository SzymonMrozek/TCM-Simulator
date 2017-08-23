//
//  main.cpp
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <iostream>
#include "Byte Coder/byte_decoder.h"
#include "Byte Coder/byte_encoder.h"
#include "Message Coder/message_encoder.h"
#include "Message Coder/message_decoder.h"
#include "Convolutional Coder/convolutional_encoder.h"
#include "Baseband Modulator/baseband_modulator.h"
#include "Viterbi Decoder/viterbi_decoder.h"
#include "Noise Adder/noise_adder.h"
#include "constants.h"
#include <string>

// MARK: - Global shared variables
std::map<int,std::complex<double>> CONSTELLATION;
std::vector<std::vector<int>> CODER_OUTPUT;
std::vector<std::vector<int>> CODER_NEXT_STATE;
int NUMBER_OF_STATES;
int NUMBER_OF_INPUTS;
char* MESSAGE;
double VARIANCE;
bool SHOULD_TRUNCATE = false;
bool IS_RUNNING_FROM_SCRIPT = false;
int CODER_SET = 1;
double SNR = 0.0;

// MARK: - Global functions
extern double getBER(std::vector<int>* original_stream, std::vector<int>* recieved_stream);
int processRunArguments(int argc, const char * argv[]);
template <typename T> void show(std::vector<T>*);

int main(int argc, const char * argv[]) {

    int run_results = processRunArguments(argc,argv);
    if (run_results != 0) {
        return run_results;
    }
    initAndLoad(CODER_SET);

    // Convert to chars
    auto message_encoder = new MessageEncoder();
    message_encoder -> encode(MESSAGE);
//    show(message_encoder->getCharStream());

    // From byte to symbols
    auto byte_decoder = new ByteDecoder(message_encoder->getCharStream(),NUMBER_OF_INPUTS);
    byte_decoder -> decode();
//    show(byte_decoder->getBitPiecesStream());

    // Convolutional encoder
    auto convolutional_encoder = new ConvolutionalEncoder(&CODER_NEXT_STATE,&CODER_OUTPUT);
    convolutional_encoder -> encode(byte_decoder->getBitPiecesStream());
//    show(convolutional_encoder->getOutputDataStream());

    // Baseband modulator
    auto baseband_modulator = new BasebandModulator(&CONSTELLATION);
    baseband_modulator -> encode(convolutional_encoder->getOutputDataStream());
//    show(baseband_modulator->getOutputDataStream());

    // Additive white gaussian noise
    auto noise_variance = VARIANCE / pow(10.0,SNR/10.0);
    auto noise_adder = new NoiseAdder(0.0,noise_variance);
    noise_adder->addNoiseToStream(baseband_modulator->getOutputDataStream());
//    show(noise_adder->getNoisedStream());

    // Viterbi decoder
    auto viterbi_decoder = new ViterbiDecoder(&CODER_NEXT_STATE, &CODER_OUTPUT, &CONSTELLATION, NUMBER_OF_STATES);
    viterbi_decoder->decode(noise_adder->getNoisedStream());
//    show(viterbi_decoder->getDecodedStreamFromTrellis());

    // Concat symbols to byte
    auto byte_encoder = new ByteEncoder(viterbi_decoder->getDecodedStreamFromTrellis() ,NUMBER_OF_INPUTS);
    byte_encoder -> encode();

    auto message_decoder = new MessageDecoder();
    message_decoder -> decode(byte_encoder->getCharStream());
    
    auto message_received = message_decoder -> getMessage();

    double ber = getBER(byte_decoder->getBitPiecesStream(),viterbi_decoder->getDecodedStreamFromTrellis());

    if(!IS_RUNNING_FROM_SCRIPT) {
        std::cout << "I've sent:    " << std::endl << MESSAGE << std::endl << std::endl;
        std::cout << "And received: " << std::endl << message_received << std::endl << std::endl;
        std::cout << "BER = " << ber << std::endl<<std::endl;
    } else {
        save(ber, BER_File, SHOULD_TRUNCATE);
        save(SNR, SNR_File, SHOULD_TRUNCATE);
    }

    delete message_encoder;
    delete byte_decoder;
    delete convolutional_encoder;
    delete baseband_modulator;
    delete noise_adder;
    delete viterbi_decoder;
    delete byte_encoder;
    delete message_decoder;

    return 0;
}

int processRunArguments(int argc, const char * argv[]) {

    if(argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "-help")) {
        std::cout << "USAGE:" << std::endl;
        std::cout << "First parameter - coder set ( qpsk - 1 / 8psk -2 / 16qam -3)" << std::endl;
        std::cout << "Second parameter - SNR range beginning in dB" << std::endl << std::endl;
        std::cout << "Third  parameter - SNR range end (max)" << std::endl << std::endl;
        std::cout << "Fourth parameter - SNR index from range" << std::endl << std::endl;
        std::cout << "Fifth  parameter - SNR number of analysis points" << std::endl << std::endl;
        std::cout << "Sixth  parameter (optional) - should truncate output files";
        return 1;
    }

    if(argc >= 6) {
        CODER_SET = std::stoi(argv[1]);
        if ( CODER_SET < 1 || CODER_SET > 3 ) {
            std::cout << "WRONG CODER SET !!! " << std::endl;
            return 1;
        }
        int SNR_start = std::stoi(argv[2]);
        int SNR_end   = std::stoi(argv[3]);
        int SNR_values_count = std::stoi(argv[4]);
        int SNR_index = std::stoi(argv[5]);

        SNR = SNR_start + double(SNR_index)*(double(SNR_end - SNR_start)/double(SNR_values_count));
        IS_RUNNING_FROM_SCRIPT = true;
        if(argc == 7) {
            SHOULD_TRUNCATE = std::string(argv[6]) == "yes";
        }
    }
    return 0;
}

template <typename T> void show(std::vector<T>* array) {
    for (auto element : *array) {
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}
