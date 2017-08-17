//
// Created by Szymon Mrozek on 17.08.2017.
//

#include <vector>
#include <map>
#include <complex>

extern std::map<int,std::complex<double>> CONSTELATION;
extern std::vector<std::vector<int>> CODER_OUTPUT;
extern std::vector<std::vector<int>> CODER_NEXT_STATE;
extern int NUMBER_OF_STATES;
extern int NUMBER_OF_INPUTS;
extern char* MESSAGE;


void initAndLoad(){

    auto _qpsk_map = new std::map<int,std::complex<double>>;
    std::vector<std::vector<int>> one_in_two_out_output;
    std::vector<std::vector<int>> one_in_two_out_next_state;
    auto one_in_two_out_number_of_states = 4;


    one_in_two_out_output.push_back({0,3});
    one_in_two_out_output.push_back({3,0});
    one_in_two_out_output.push_back({2,1});
    one_in_two_out_output.push_back({1,2});

    one_in_two_out_next_state.push_back({0,2});
    one_in_two_out_next_state.push_back({0,2});
    one_in_two_out_next_state.push_back({1,3});
    one_in_two_out_next_state.push_back({1,3});

    _qpsk_map -> operator[](0) = std::complex<double>(0.707,0.707);
    _qpsk_map -> operator[](1) = std::complex<double>(-0.707,0.707);
    _qpsk_map -> operator[](2) = std::complex<double>(-0.707,-0.707);
    _qpsk_map -> operator[](3) = std::complex<double>(0.707,-0.707);

//    CONSTELATION = *_qpsk_map;
//    CODER_NEXT_STATE = one_in_two_out_next_state;
//    CODER_OUTPUT = one_in_two_out_output;
//    NUMBER_OF_STATES = one_in_two_out_number_of_states;
//    NUMBER_OF_INPUTS = 1;

    auto _8psk_map = new std::map<int,std::complex<double>>;
    std::vector<std::vector<int>> two_in_three_out_output;
    std::vector<std::vector<int>> two_in_three_out_next_state;
    auto two_in_three_out_number_of_states = 4;

    _8psk_map -> operator[](0) = std::complex<double>(0.0, 0.0);
    _8psk_map -> operator[](1) = std::complex<double>(0.707, 0.707);
    _8psk_map -> operator[](2) = std::complex<double>(0.0, 1.0);
    _8psk_map -> operator[](3) = std::complex<double>(-0.707, 0.707);
    _8psk_map -> operator[](4) = std::complex<double>(-1.0, 0.0);
    _8psk_map -> operator[](5) = std::complex<double>(-0.707, -0.707);
    _8psk_map -> operator[](6) = std::complex<double>(0.0, -1.0);
    _8psk_map -> operator[](7) = std::complex<double>(0.707, -0.707);

    two_in_three_out_output.push_back({0,2,4,6});
    two_in_three_out_output.push_back({2,0,6,4});
    two_in_three_out_output.push_back({1,3,5,7});
    two_in_three_out_output.push_back({3,1,7,5});

    two_in_three_out_next_state.push_back({0,2,0,2});
    two_in_three_out_next_state.push_back({0,2,0,2});
    two_in_three_out_next_state.push_back({1,3,1,3});
    two_in_three_out_next_state.push_back({1,3,1,3});

    CONSTELATION = *_8psk_map;
    CODER_NEXT_STATE = two_in_three_out_next_state;
    CODER_OUTPUT = two_in_three_out_output;
    NUMBER_OF_STATES = two_in_three_out_number_of_states;
    NUMBER_OF_INPUTS = 2;

    MESSAGE = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

}