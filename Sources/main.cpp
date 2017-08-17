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

std::map<int,std::complex<double>> CONSTELATION;
std::vector<std::vector<int>> CODER_OUTPUT;
std::vector<std::vector<int>> CODER_NEXT_STATE;
int NUMBER_OF_STATES;
int NUMBER_OF_INPUTS;
char* MESSAGE;

extern void initAndLoad();
template <typename T> void show(std::vector<T>*);

int main(int argc, const char * argv[]) {
    initAndLoad();

    // Convert to chars
    auto message_encoder = new MessageEncoder();
    message_encoder -> encode(MESSAGE);
//    show(message_encoder->getCharStream());

    // From byte to symbols
    auto byte_decoder = new ByteDecoder(message_encoder->getCharStream(),NUMBER_OF_INPUTS);
    byte_decoder -> decode();
    show(byte_decoder->getBitPiecesStream());

    // Convolutional encoder
    auto convolutional_encoder = new ConvolutionalEncoder(&CODER_NEXT_STATE,&CODER_OUTPUT);
    convolutional_encoder -> encode(byte_decoder->getBitPiecesStream());
    show(convolutional_encoder->getOutputDataStream());

    // Baseband modulator
    auto baseband_modulator = new BasebandModulator(&CONSTELATION);
    baseband_modulator -> encode(convolutional_encoder->getOutputDataStream());
    show(baseband_modulator->getOutputDataStream());

    // Additive white gaussian noise
    auto mean = 0.3;
    auto variance = 0.3;
    auto noise_adder = new NoiseAdder(mean,variance);
    noise_adder->addNoiseToStream(baseband_modulator->getOutputDataStream());


    // Viterbi decoder
    auto viterbi_decoder = new ViterbiDecoder(&CODER_NEXT_STATE, &CODER_OUTPUT, &CONSTELATION, NUMBER_OF_STATES);
    viterbi_decoder->decode(baseband_modulator->getOutputDataStream());
    show(viterbi_decoder->getDecodedStreamFromTrellis());

    // Concat symbols to byte
    auto byte_encoder = new ByteEncoder(viterbi_decoder->getDecodedStreamFromTrellis() ,NUMBER_OF_INPUTS);
    byte_encoder -> encode();
    show(byte_decoder->getBitPiecesStream());

    auto message_decoder = new MessageDecoder();
    message_decoder -> decode(byte_encoder->getCharStream());
    
    auto message_recieved = message_decoder -> getMessage();
    
    std::cout << "I've sent - " << MESSAGE << std::endl;
    std::cout << "And recieved - " << message_recieved << std::endl;
    
    
    return 0;
}

template <typename T> void show(std::vector<T>* array) {
    for (auto element : *array) {
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}
