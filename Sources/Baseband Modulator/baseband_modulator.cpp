//
//  baseband_modulator.cpp
//  TCM-Simulator
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include "baseband_modulator.h"

BasebandModulator::BasebandModulator(std::map<int,std::complex<double>>* output_map) :
        output_map_(new std::map<int,std::complex<double>>(*output_map)),
        output_data_stream_(new std::vector<std::complex<double>>) { }

BasebandModulator::~BasebandModulator(){
    delete output_map_;
    delete output_data_stream_;
}

void BasebandModulator::encode(std::vector<int>* input_data_stream){
    
    output_data_stream_ -> clear();

    for(auto element : *input_data_stream){
    
        output_data_stream_->push_back(output_map_->operator[](element));
    }
}
std::vector<std::complex<double>>* BasebandModulator::getOutputDataStream(){

    return output_data_stream_;
}
