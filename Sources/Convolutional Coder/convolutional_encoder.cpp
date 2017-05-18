//
//  convolutional_encoder.cpp
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <stdio.h>
#include "convolutional_encoder.h"



ConvolutionalEncoder::ConvolutionalEncoder(int number_of_inputs, int number_of_states, std::vector<std::vector<int>>* next_stage_matrix, std::vector<std::vector<int>>* output_matrix) : number_of_states_(number_of_states), current_state_(0), next_state_matrix_(next_stage_matrix),
    output_matrix_(output_matrix){
        
        output_data_stream_ = new std::vector<int>;
    
}

void ConvolutionalEncoder::encode(std::vector<int>* input_data_stream){
    
    input_data_stream_ = input_data_stream;
    output_data_stream_->clear();
    
    for(auto current_element : *input_data_stream_){
    
        auto output = output_matrix_->operator[](current_state_).operator[](current_element);
        current_state_ = next_state_matrix_->operator[](current_state_).operator[](current_element);
        output_data_stream_->push_back(output);
        
    }

}
std::vector<int>* ConvolutionalEncoder::getOutputDataStream(){
    
    return output_data_stream_;
}
