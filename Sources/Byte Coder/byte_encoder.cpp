//
//  byte_encoder.cpp
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "byte_encoder.h"
#include <iostream>


ByteEncoder::ByteEncoder(std::vector<int>* input_stream, int bit_piece_size) : bit_piece_size_(bit_piece_size),
        input_stream_(input_stream){
    
            char_stream_ = new std::vector<char>;
    
    
    
}


void ByteEncoder::encode(){
    
    
    auto byte_indexer = 0;
    auto bits_remaining = 0;
    
    
    int mask [8] = { 1, 3, 7, 15, 31, 63, 127, 255};
    int inverse_mask[8] = { 0b10000000, 0b11000000, 0b1110000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111111};
    
    
    auto int_value = 0;
    for(auto stream_iterator = 0; stream_iterator < input_stream_->size() - 1;){

        if(byte_indexer + bit_piece_size_ <= 8){
         
            auto input_value = input_stream_->operator[](stream_iterator);
            int_value |= (input_value << byte_indexer);
            
            byte_indexer += bit_piece_size_;
            
            if(byte_indexer == 8){
                byte_indexer = 0;
                char_stream_->push_back(static_cast<char>(int_value));
                int_value = 0;
            }
        }else{
            auto input_value = input_stream_->operator[](stream_iterator);

            bits_remaining = 8 - byte_indexer;
            int_value |= (mask[bits_remaining - 1] & input_value) << byte_indexer;
            
            char_stream_ -> push_back(static_cast<char>(int_value));
            byte_indexer = bit_piece_size_ - bits_remaining;
            
            int_value = (input_value & (mask[bit_piece_size_ - 1] << bits_remaining)) >> bits_remaining;
            
        }
        ++ stream_iterator;
        
    }
    
}


std::vector<char>* ByteEncoder::getCharStream(){
    
    return char_stream_;
}
