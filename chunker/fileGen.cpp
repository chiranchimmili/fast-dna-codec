#include <fstream>
#include <iostream>
#include <vector>
#include <random>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> randomNum(0, 94);

void generateFile(int numberBytes) {
    std::ofstream file;
    file.open("../files/chunk.txt");
    std::string line;
    for (int i = 0; i < numberBytes; i++) {
        int num = randomNum(generator);
        char byte = 32 + num;

        file << byte;
    }
    file.close();
}

std::string readFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);

    // Assuming input file will be one continous string of bytes
    std::string line;
    getline(file, line);
    file.close();
    return line;
}
