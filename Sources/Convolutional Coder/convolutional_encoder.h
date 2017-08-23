//
//  convolutional_encoder.h
//  TCM-Simulator
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef convolutional_encoder_h
#define convolutional_encoder_h

#include <vector>

class ConvolutionalEncoder{

//    Use this class when you want to convolution encode binary symbols
//    Constructors parameters are :
//        - next_state_matrix - vector of vectors representing next state given by input symbol
//        - output_matrix - vector of vectors represeting output given by input symbol
//    Call encode, and then getOutputDataStream

public:
    
    ConvolutionalEncoder(std::vector<std::vector<int>>* next_stage_matrix,
                         std::vector<std::vector<int>>* output_matrix);
    ~ConvolutionalEncoder();

    void encode(std::vector<int>* input_data_stream);
    std::vector<int>* getOutputDataStream();

    
private:
    
    int current_state_;
    
    std::vector<std::vector<int>>* next_state_matrix_;
    std::vector<std::vector<int>>* output_matrix_;
    
    std::vector<int>* output_data_stream_;
};


#endif /* convolutional_encoder_h */
