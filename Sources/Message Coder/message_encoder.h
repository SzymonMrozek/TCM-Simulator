//
//  message_encoder.h
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef message_encoder_h
#define message_encoder_h

#include <string>
#include <vector>


class MessageEncoder{
    
    
public:
    
    MessageEncoder();
    ~MessageEncoder();
    void encode(std::string new_message);
    std::vector<char>* getCharStream();
    
    
private:
    
    std::string message_;
    std::vector<char>* char_output_stream_;
    
};

#endif /* message_encoder_h */
