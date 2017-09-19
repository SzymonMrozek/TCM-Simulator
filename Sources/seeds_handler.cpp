//
// Created by Szymon Mrozek on 19.09.2017.
//


#include <random>
#include <climits>
#include <string>
#include <fstream>

void saveSeedFile() {

    auto engine = std::default_random_engine();
    auto generator = std::uniform_int_distribution<int>();
    std::ofstream seed_file("seeds.txt", std::ios::trunc);
    auto seed_step =  INT_MAX/ 1200;

    for(auto i = 0; i < INT_MAX; ++i){
        if (i % seed_step == 0){
            int value = generator(engine);
            seed_file << value << std :: endl;
        }
    }
    seed_file.close();

}

int getSeedForIteration(int iteration) {
    auto text_line = new char[256];
    std::ifstream seeds_file("seeds.txt");

    for (auto i = 0; i < iteration; ++i) {
        seeds_file.ignore(std::numeric_limits<std::streamsize>::max(), seeds_file.widen('\n'));
    }
    seeds_file.getline(text_line, 256);
    return std::atoi(text_line);
}
