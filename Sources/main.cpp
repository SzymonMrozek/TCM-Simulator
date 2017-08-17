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
#include "ViterbiDecoder/ViterbiDecoder.h"




auto CONSTELATION = new std::map<int,std::complex<double>>;
std::vector<std::vector<int>> CODER_OUTPUT;
std::vector<std::vector<int>> CODER_NEXT_STATE;
int NUMBER_OF_STATES;
int NUMBER_OF_INPUTS;


void initAndLoad(){

    auto _qpsk_map = new std::map<int,std::complex<double>>;
    std::vector<std::vector<int>> one_in_two_out_output;
    std::vector<std::vector<int>> one_in_two_out_next_state;
    auto number_of_states = 4;


    one_in_two_out_output.push_back({0,3});
    one_in_two_out_output.push_back({3,0});
    one_in_two_out_output.push_back({2,1});
    one_in_two_out_output.push_back({1,2});

    one_in_two_out_next_state.push_back({0,2});
    one_in_two_out_next_state.push_back({0,2});
    one_in_two_out_next_state.push_back({1,3});
    one_in_two_out_next_state.push_back({1,3});

    _qpsk_map -> operator[](0) = std::complex<double>(0.707,0.707);
    _qpsk_map -> operator[](1) = std::complex<double>(-0.707,0.707);
    _qpsk_map -> operator[](2) = std::complex<double>(-0.707,-0.707);
    _qpsk_map -> operator[](3) = std::complex<double>(0.707,-0.707);

    auto _8psk_map = new std::map<int,std::complex<double>>;
    std::vector<std::vector<int>> two_in_three_out_output;
    std::vector<std::vector<int>> two_in_three_out_next_state;


//    CONSTELATION = _qpsk_map;
//    CODER_NEXT_STATE = one_in_two_out_next_state;
//    CODER_OUTPUT = one_in_two_out_output;
//    NUMBER_OF_STATES = number_of_states;
//    NUMBER_OF_INPUTS = 1;

    _8psk_map -> operator[](0) = std::complex<double>(0.0, 0.0);
    _8psk_map -> operator[](1) = std::complex<double>(0.707, 0.707);
    _8psk_map -> operator[](2) = std::complex<double>(0.0, 1.0);
    _8psk_map -> operator[](3) = std::complex<double>(-0.707, 0.707);
    _8psk_map -> operator[](4) = std::complex<double>(-1.0, 0.0);
    _8psk_map -> operator[](5) = std::complex<double>(-0.707, -0.707);
    _8psk_map -> operator[](6) = std::complex<double>(0.0, -1.0);
    _8psk_map -> operator[](7) = std::complex<double>(0.707, -0.707);

    two_in_three_out_output.push_back({0,2,4,6});
    two_in_three_out_output.push_back({2,0,6,4});
    two_in_three_out_output.push_back({1,3,5,7});
    two_in_three_out_output.push_back({3,1,7,5});

    two_in_three_out_next_state.push_back({0,2,0,2});
    two_in_three_out_next_state.push_back({0,2,0,2});
    two_in_three_out_next_state.push_back({1,3,1,3});
    two_in_three_out_next_state.push_back({1,3,1,3});

    CONSTELATION = _8psk_map;
    CODER_NEXT_STATE = two_in_three_out_next_state;
    CODER_OUTPUT = two_in_three_out_output;
    NUMBER_OF_STATES = number_of_states;
    NUMBER_OF_INPUTS = 2;
}

int main(int argc, const char * argv[]) {
    initAndLoad();

    auto message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

    auto message_encoder = new MessageEncoder();
    message_encoder -> encode(message);

    for(auto element : *message_encoder->getCharStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    auto byte_decoder = new ByteDecoder(message_encoder->getCharStream(),NUMBER_OF_INPUTS);
    byte_decoder -> decode();
    
    
    for(auto element : *byte_decoder->getBitPiecesStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    
    auto convolutional_encoder = new ConvolutionalEncoder(2,&CODER_NEXT_STATE,&CODER_OUTPUT);
    convolutional_encoder -> encode(byte_decoder->getBitPiecesStream());
    
    
    for(auto element : *convolutional_encoder->getOutputDataStream()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;


    auto baseband_modulator = new BasebandModulator(CONSTELATION);
    baseband_modulator -> encode(convolutional_encoder->getOutputDataStream());



    // Additive white gaussian noise






    // Viterbi decoder


    auto viterbi_decoder = new ViterbiDecoder(&CODER_NEXT_STATE, &CODER_OUTPUT, CONSTELATION, NUMBER_OF_STATES);
    viterbi_decoder->decode(baseband_modulator->getOutputDataStream());
    
    auto byte_encoder = new ByteEncoder(viterbi_decoder->getDecodedStreamFromTrellis() ,NUMBER_OF_INPUTS);
    byte_encoder -> encode();

    for(auto element : *viterbi_decoder->getDecodedStreamFromTrellis()){
        std::cout<<element<< " ";
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    
    auto message_decoder = new MessageDecoder();
    message_decoder -> decode(byte_encoder->getCharStream());
    
    auto message_recieved = message_decoder -> getMessage();
    
    std::cout << "I've sent - " << message << std::endl;
    std::cout << "And recieved - " << message_recieved << std::endl;
    
    
    return 0;
}
