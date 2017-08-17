cmake_minimum_required(VERSION 3.7)
project(TCM_Simulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        "Sources/Baseband Modulator/baseband_modulator.cpp"
        "Sources/Baseband Modulator/baseband_modulator.h"
        "Sources/Byte Coder/byte_decoder.cpp"
        "Sources/Byte Coder/byte_decoder.h"
        "Sources/Byte Coder/byte_encoder.cpp"
        "Sources/Byte Coder/byte_encoder.h"
        "Sources/Convolutional Coder/convolutional_encoder.cpp"
        "Sources/Convolutional Coder/convolutional_encoder.h"
        Sources/main.cpp
        "Sources/Message Coder/message_decoder.cpp"
        "Sources/Message Coder/message_decoder.h"
        "Sources/Message Coder/message_encoder.cpp"
        "Sources/Message Coder/message_encoder.h"
        "Sources/Viterbi Decoder/viterbi_decoder.cpp"
        "Sources/Viterbi Decoder/viterbi_decoder.h"
        Sources/constants.cpp
        "Sources/Noise Adder/noise_adder.cpp"
        "Sources/Noise Adder/noise_adder.h")


add_executable(TCM_Simulator ${SOURCE_FILES})