//
//  message_decoder.h
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef message_decoder_h
#define message_decoder_h

#include <vector>
#include <string>




class MessageDecoder{
    
    
public:
    
    MessageDecoder();
    ~MessageDecoder();
    void decode(std::vector<char>* char_stream);
    std::string getMessage();
    
    
private:
    
    std::string message_;
    
};

#endif /* message_decoder_h */
