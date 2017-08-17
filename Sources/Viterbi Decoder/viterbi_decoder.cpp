//
// Created by Szymon Mrozek on 15.08.2017.
//

#include "viterbi_decoder.h"


ViterbiDecoder::ViterbiDecoder(std::vector<std::vector<int>> *next_state, std::vector<std::vector<int>> *output,
                               std::map<int, std::complex<double>> *constelation, const int number_of_states)
        : next_state_(next_state), output_(output), constelation_(constelation),
          number_of_states_(number_of_states) {
    cost_memory_ = new std::vector<std::vector<Path*>*>;
}

void ViterbiDecoder::decode(std::vector<std::complex<double>> *input_data_stream) {

    auto minimal_paths = new std::vector<Path*>;

    for(auto input_signal : *input_data_stream) {
        minimal_paths = initMiminalPaths(); // clear temorary minimal paths
        for (auto current_state = 0; current_state < next_state_->size(); current_state++) {
            // State analysis
            for (auto input = 0; input < next_state_->operator[](current_state).size(); input++) {
                // Possible input in state analysis
                auto next_state = next_state_->operator[](current_state)[input];
                auto current_path = new Path();
                current_path->from_state = current_state;
                current_path->to_state = next_state;
                current_path->input = input;
                auto current_output = output_->operator[](current_state)[input];
                current_path->cost = getEuclideanDistance(input_signal, current_output);

                if (cost_memory_->size() > 0){
                    current_path->cost += cost_memory_->back()->operator[](current_state)->cost;
                }

                if (minimal_paths->operator[](next_state) == nullptr) {
                    minimal_paths->operator[](next_state) = current_path;
                } else if (minimal_paths->operator[](next_state)->cost > current_path->cost) {
                    minimal_paths->operator[](next_state) = current_path;
                }
            }
        }
        cost_memory_->push_back(minimal_paths);
    }
}

std::vector<int>* ViterbiDecoder::getDecodedStreamFromTrellis() {

    auto decoded_stream = new std::vector<int>;

    auto last_index = cost_memory_->size() - 1;
    auto cost_sums = new std::vector<double>;

    // Find the minimal path
    for (auto i = 0; i < number_of_states_ ; i++ ){
        cost_sums->push_back(0.0);
    }
    for (auto i = 0; i < cost_memory_->size() ; i++) {
        for ( auto j = 0; j < cost_memory_->operator[](i)->size(); j++) {
            cost_sums->operator[](j) += cost_memory_->operator[](i)->operator[](j)->cost;
        }
    }
    auto min_index = 0;

    for (auto i = 0; i < number_of_states_ ; i++ ){
        if ( cost_sums->operator[](i) < cost_sums->operator[](min_index)) {
            min_index = i;
        }
    }
    auto min_path = cost_memory_->operator[](last_index)->operator[](min_index);

    for (auto i = 0; i < cost_memory_->operator[](last_index)->size(); i++) {
        if (cost_memory_->operator[](last_index)->operator[](i)->cost < min_path->cost) {
            min_path = cost_memory_->operator[](last_index)->operator[](i);
        }
    }
    auto previous_state = min_path->from_state;
    for (int i = cost_memory_->size() - 1; i >= 0 ; i--) {
        decoded_stream->push_back(cost_memory_->operator[](i)->operator[](previous_state)->input);
        previous_state = cost_memory_->operator[](i)->operator[](previous_state)->from_state;
    }

    std::reverse(std::begin(*decoded_stream), std::end(*decoded_stream));
    return decoded_stream;
}

std::vector<Path*>* ViterbiDecoder::initMiminalPaths() {

    auto new_minimal_paths = new std::vector<Path*>();
    for (auto i = 0; i < number_of_states_ ; i++) {
        new_minimal_paths->push_back(nullptr);
    }
    return new_minimal_paths;
}

double ViterbiDecoder::getEuclideanDistance(std::complex<double> signal_point, int constelation_point) {
    auto dx = signal_point.real() - constelation_->operator[](constelation_point).real();
    auto dy = signal_point.imag() - constelation_->operator[](constelation_point).imag();
    return std::abs(std::complex<double>(dx, dy));
}


