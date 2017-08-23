//
// Created by Szymon Mrozek on 17.08.2017.
//
#include <vector>

extern int NUMBER_OF_INPUTS;

// This method calculates BER by comparing original stream to stream that was recieved

double getBER(std::vector<int>* original_stream, std::vector<int>* recieved_stream) {

    auto bits_errors = 0;
    auto bits_total = 0;

    for ( auto i = 0; i < original_stream->size() && i < recieved_stream->size(); i++) {
        auto mask = 1;
        for(auto bit = 0; bit < NUMBER_OF_INPUTS; bit ++ ) {
            if ((original_stream->operator[](i) & mask)!= (recieved_stream->operator[](i) & mask)) {
                  bits_errors++;
            }
            bits_total++;
            mask <<= 1;
        }
    }
    return (double)bits_errors/(double)bits_total;
}

