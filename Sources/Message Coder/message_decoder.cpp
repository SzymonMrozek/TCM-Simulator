//
//  message_decoder.cpp
//  TCM-Simulator
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include "message_decoder.h"
#include <iostream>

MessageDecoder::MessageDecoder() { }

MessageDecoder::~MessageDecoder() { }

void MessageDecoder::decode(std::vector<char>* char_stream){
    
    message_ = "";
    for(auto character : *char_stream){
        message_ += character;
    }
}

std::string MessageDecoder::getMessage(){
    
    return message_;
}
