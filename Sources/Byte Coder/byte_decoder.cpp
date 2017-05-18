//
//  byte_decoder.cpp
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "byte_decoder.h"
#include <iostream>


ByteDecoder::ByteDecoder(std::vector<char>* input_stream, int bit_piece_size) : bit_piece_size_(bit_piece_size),
            input_stream_(input_stream){
                                
                bit_pieces_stream_ = new std::vector<int>;
                                
                            
                                
}


void ByteDecoder::decode(){
    
    
    auto byte_indexer = 0;
    auto bits_remaining = 0;

    
    int mask [8] = { 1, 3, 7, 15, 31, 63, 127, 255};
    int inverse_mask[8] = { 0b10000000, 0b11000000, 0b1110000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111111};
    for(auto stream_iterator = 0; stream_iterator < input_stream_->size();){
        
        if(byte_indexer + bit_piece_size_ <= 8){
            // bit piece inside of byte
            auto stream_value = static_cast<int>(input_stream_ -> operator[](stream_iterator));
            auto value = (stream_value & (mask[bit_piece_size_-1] << byte_indexer))  >> byte_indexer;
            
            bit_pieces_stream_ -> push_back(value);
            byte_indexer += bit_piece_size_;
            
            if(byte_indexer == 8){
                byte_indexer = 0;
                ++stream_iterator;
            }
            
        }else{
            // bit piece contain two bytes
            
            bits_remaining = 8 - byte_indexer;
            
            auto stream_first_value = static_cast<int>(input_stream_ -> operator[](stream_iterator));
            auto first_mask = inverse_mask[bits_remaining-1];
            auto first_value = (stream_first_value & first_mask) >> byte_indexer;

            byte_indexer = bit_piece_size_ - bits_remaining;
            
            auto stream_second_value = static_cast<int>(input_stream_ -> operator[](stream_iterator + 1));
            auto second_mask = mask[byte_indexer -1];
            auto second_value = (stream_second_value & second_mask) << bits_remaining;
            bit_pieces_stream_ -> push_back(first_value | second_value);
            
            ++stream_iterator;
        }
    }
    
}


std::vector<int>* ByteDecoder::getBitPiecesStream(){
 
    return bit_pieces_stream_;
}


