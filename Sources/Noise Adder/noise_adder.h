//
// Created by Szymon Mrozek on 17.08.2017.
//

#ifndef TCM_SIMULATOR_NOISEADDER_H
#define TCM_SIMULATOR_NOISEADDER_H
#include <cstdlib>
#include <random>
#include <complex>
#include <vector>
#include <iostream>

class NoiseAdder {

public:

    NoiseAdder(double mean, double var);
    void addNoiseToStream(std::vector<std::complex<double>>* input_stream);
    std::vector<std::complex<double>>* getNoisedStream();
private:
    const double mean_;
    const double var_;

    std::default_random_engine* engine_;
    std::normal_distribution<double>* distribution_;
    std::vector<std::complex<double>>* output_stream_;



};


#endif //TCM_SIMULATOR_NOISEADDER_H
