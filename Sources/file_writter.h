//
// Created by Szymon Mrozek on 19.08.2017.
//

#ifndef TCM_SIMULATOR_FILEWRITTER_H
#define TCM_SIMULATOR_FILEWRITTER_H

#include <fstream>

struct SimulatorResultFile {
    const char * file_path;
} SNR_File, BER_File;

template <typename T> void save(T value, SimulatorResultFile file, bool should_truncate){

    std::ios_base::openmode  opening_mode = should_truncate ? std::ios_base::trunc : std::ios_base::app;
    std::ofstream output_file(file.file_path, opening_mode);
    output_file << value << std::endl;
    output_file.close();
}

#endif // TCM_SIMULATOR_FILEWRITTER_H