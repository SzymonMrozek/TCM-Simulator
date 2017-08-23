//
//  byte_encoder.h
//  TCM-Simulator
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef byte_encoder_h
#define byte_encoder_h

#include <vector>

class ByteEncoder{

    // This class is used for converting N-bit pieces into 8-bit value
    // Usage :
    // - construct with input stream of N-bit int, and size of bit piece (N)
    // - call encode()
    // - result is saved in char_stream so just get it

public:
    
    ByteEncoder(std::vector<int>* input_stream, int bit_piece_size);
    ~ByteEncoder();
    
    void encode();
    std::vector<char>* getCharStream();

private:
    
    std::vector<char>* char_output_stream_;
    std::vector<int>* input_stream_;
    const int bit_piece_size_; // number from 1 to 8
};

#endif /* byte_encoder_h */
