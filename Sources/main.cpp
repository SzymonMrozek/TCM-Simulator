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
#include <string>

#define bit_piece_size 1

auto qpsk_map = new std::map<int,std::complex<double>>;
std::vector<std::vector<int>> my_coder_output;
std::vector<std::vector<int>> my_coder_next_state;

void init(){
    
    my_coder_output.push_back({0,3});
    my_coder_output.push_back({3,0});
    my_coder_output.push_back({2,1});
    my_coder_output.push_back({1,2});
    
    my_coder_next_state.push_back({0,2});
    my_coder_next_state.push_back({0,2});
    my_coder_next_state.push_back({1,3});
    my_coder_next_state.push_back({1,3});

    
    qpsk_map -> operator[](0) =  0.707 + 0.707i;
    qpsk_map -> operator[](1) =  -0.707 + 0.707i;
    qpsk_map -> operator[](2) =  -0.707 - 0.707i;
    qpsk_map -> operator[](3) =  0.707 - 0.707i;
}

int main(int argc, const char * argv[]) {
    init();
    
    auto message = "Is it working properly?";
    
    auto message_encoder = new MessageEncoder();
    message_encoder -> encode(message);
    
    for(auto element : *message_encoder->getCharStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    
    auto byte_decoder = new ByteDecoder(message_encoder->getCharStream(),bit_piece_size);
    byte_decoder -> decode();
    
    
    for(auto element : *byte_decoder->getBitPiecesStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    
    auto convolutional_encoder = new ConvolutionalEncoder(1,2,&my_coder_next_state,&my_coder_output);
    convolutional_encoder -> encode(byte_decoder->getBitPiecesStream());
    
    
    for(auto element : *convolutional_encoder->getOutputDataStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    
    auto basband_modulator = new BasebandModulator(qpsk_map);
    basband_modulator -> encode(convolutional_encoder->getOutputDataStream());
    
    
    for(auto element : *basband_modulator->getOutputDataStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    
    auto byte_encoder = new ByteEncoder(byte_decoder->getBitPiecesStream(),bit_piece_size);
    byte_encoder -> encode();
    
    auto message_decoder = new MessageDecoder();
    message_decoder -> decode(byte_encoder->getCharStream());
    
    auto message_recieved = message_decoder -> getMessage();
    
    std::cout << "I've sent - " << message << std::endl;
    std::cout << "And recieved - " << message_recieved << std::endl;
    
    
    return 0;
}
