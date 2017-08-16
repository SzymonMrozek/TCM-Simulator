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

public:


    ViterbiDecoder(std::vector<std::vector<int>> *next_state, std::vector<std::vector<int>> *output,
                       std::map<int, std::complex<double>> *constelation, const int number_of_states);

    void decode(std::vector<std::complex<double>>* input_data_stream);
    std::vector<int>* getDecodedStreamFromTrellis();

private:

    std::vector<std::vector<int>>* next_state_;
    std::vector<std::vector<int>>* output_;
    std::map<int,std::complex<double>>* constelation_;
    std::vector<std::vector<Path*>*>* cost_memory_;
    const int number_of_states_;

    double getEuclideanDistance(std::complex<double> signal_point, int constelation_point);
    std::vector<Path*>* initMiminalPaths() ;

};


#endif //TCM_SIMULATOR_VITERBIDECODER_H
