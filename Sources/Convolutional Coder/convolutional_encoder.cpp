//
//  convolutional_encoder.cpp
//  TCM-Simulator
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <stdio.h>
#include "convolutional_encoder.h"


ConvolutionalEncoder::ConvolutionalEncoder(std::vector<std::vector<int>>* next_stage_matrix, std::vector<std::vector<int>>* output_matrix) :
        current_state_(0),
        next_state_matrix_(new std::vector<std::vector<int>>(*next_stage_matrix)),
        output_matrix_(new std::vector<std::vector<int>>(*output_matrix)),
        output_data_stream_ (new std::vector<int>) { }

ConvolutionalEncoder::~ConvolutionalEncoder() {

    delete next_state_matrix_;
    delete output_data_stream_;
    delete output_matrix_;
}

void ConvolutionalEncoder::encode(std::vector<int>* input_data_stream){

    output_data_stream_->clear();

    for(int current_element : *input_data_stream){

        auto output = output_matrix_->operator[](current_state_).operator[](current_element);
        current_state_ = next_state_matrix_->operator[](current_state_).operator[](current_element);
        output_data_stream_->push_back(output);

    }

}
std::vector<int>* ConvolutionalEncoder::getOutputDataStream(){

    return output_data_stream_;
}

