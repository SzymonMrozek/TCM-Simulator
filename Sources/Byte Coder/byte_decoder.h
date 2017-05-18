//
//  byte_decoder.h
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef byte_decoder_h
#define byte_decoder_h

#include <vector>

class ByteDecoder{
    
    
    // This class is used for converting 8-bit value into N-bit pieces
    // Usage :
    // - construct with input stream of 8 bit (char) and size of bit piece
    // - call decode()
    // - result is saved in bit_pieces_stream so jus get it
    
    
public:
    
    ByteDecoder(std::vector<char>* input_stream, int bit_piece_size);
    ~ByteDecoder();
    
    void decode();
    std::vector<int>* getBitPiecesStream();
    
    
private:
    
    std::vector<int>* bit_pieces_stream_;
    std::vector<char>* input_stream_;
    const int bit_piece_size_;// number from 1 to 8 
    
    int* mask_;
    int* inverse_mask_;

    
};


#endif /* byte_decoder_h */
