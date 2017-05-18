//
//  baseband_modulator.h
//  TCM-Simulatior TEMP
//
//  Created by Szymon Mrozek on 17.05.2017.
//  Copyright © 2017 Szymon Mrozek. All rights reserved.
//

#ifndef baseband_modulator_h
#define baseband_modulator_h


#include <vector>
#include <map>
#include <complex>




class BasebandModulator{
    

public:
    
    BasebandModulator(std::map<int,std::complex<double>>* output_map);
    ~BasebandModulator();
    
    void encode(std::vector<int>* input_data_stream);
    std::vector<std::complex<double>>* getOutputDataStream();
    
    
private:
    
    std::map<int,std::complex<double>>* output_map_;
    
    std::vector<int>* input_data_stream_;
    std::vector<std::complex<double>>* output_data_stream_;
    
    
};
#endif /* baseband_modulator_h */
