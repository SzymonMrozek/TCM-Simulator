//
//  convolutional_encoder.h
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef convolutional_encoder_h
#define convolutional_encoder_h

#include <vector>



class ConvolutionalEncoder{
    
    
    
public:
    
    ConvolutionalEncoder(std::vector<std::vector<int>>* next_stage_matrix,
                         std::vector<std::vector<int>>* output_matrix);
    void encode(std::vector<int>* input_data_stream);
    std::vector<int>* getOutputDataStream();

    
private:
    
    int current_state_;
    
    std::vector<std::vector<int>>* next_state_matrix_;
    std::vector<std::vector<int>>* output_matrix_;
    
    std::vector<int>* input_data_stream_;
    std::vector<int>* output_data_stream_;
};


#endif /* convolutional_encoder_h */
