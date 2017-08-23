//
// Created by Szymon Mrozek on 15.08.2017.
//

#ifndef TCM_SIMULATOR_VITERBIDECODER_H
#define TCM_SIMULATOR_VITERBIDECODER_H

#include <vector>
#include <complex>
#include <map>

struct Path {

public:

    friend bool operator > (const Path& lhs,const Path& rhs) {
        return lhs.cost > rhs.cost;
    }

    int from_state;
    int to_state;
    double cost;
    int input;
};

class ViterbiDecoder {


//    Usage : create decoder with convolution coder properties ( next state array and output array ),
//    also constellation map is needed and number of coder states
//    Then you need to call decode function and getDecodedStreamFromTrellis


public:


    ViterbiDecoder(std::vector<std::vector<int>> *next_state, std::vector<std::vector<int>> *output,
                       std::map<int, std::complex<double>>* constellation, const int number_of_states);
    ~ViterbiDecoder();

    void decode(std::vector<std::complex<double>>* input_data_stream);
    std::vector<int>* getDecodedStreamFromTrellis();

private:

    std::vector<std::vector<int>>* next_state_;
    std::vector<std::vector<int>>* output_;
    std::map<int,std::complex<double>>* constellation_;
    std::vector<std::vector<Path*>*>* cost_memory_; // whole viterbi paths `tree`
    const int number_of_states_;

    double getEuclideanDistance(std::complex<double> signal_point, int constellation_point);
    std::vector<Path*>* initMinimalPaths() ;
};

#endif //TCM_SIMULATOR_VITERBIDECODER_H
