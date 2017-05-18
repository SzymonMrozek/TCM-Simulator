//
//  baseband_modulator.cpp
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <stdio.h>
#include "baseband_modulator.h"



BasebandModulator::BasebandModulator(std::map<int,std::complex<double>>* output_map){
    
    output_map_ = output_map;
    output_data_stream_ = new std::vector<std::complex<double>>;
}
BasebandModulator::~BasebandModulator(){
    
}

void BasebandModulator::encode(std::vector<int>* input_data_stream){
    
    output_data_stream_ -> clear();
    input_data_stream_ = input_data_stream;
    
    for(auto element : *input_data_stream_){
    
        output_data_stream_->push_back(output_map_->operator[](element));
    }
}
std::vector<std::complex<double>>* BasebandModulator::getOutputDataStream(){

    return output_data_stream_;
}
