//
//  message_encoder.cpp
//  TCM-Simulator
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#include <stdio.h>
#include "message_encoder.h"


MessageEncoder::MessageEncoder() :
        char_output_stream_(new std::vector<char>) { }

MessageEncoder::~MessageEncoder(){

    delete char_output_stream_;
}

void MessageEncoder::encode(std::string new_message){
    message_ = new_message;
    char_output_stream_ -> clear();
    
    for(int i = 0; i<new_message.size();++i){
        char_output_stream_->push_back(new_message[i]);
    }

    char_output_stream_->push_back(' ');
}

std::vector<char>* MessageEncoder::getCharStream(){

    return char_output_stream_;
}

