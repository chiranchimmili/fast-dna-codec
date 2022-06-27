#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <random>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> randomNum(0, 94);

void generateFile(int numberBytes, std::string fileName) {
    std::ofstream file;
    file.open(fileName);
    std::string line;

    // int count = 1;

    for (int i = 0; i < numberBytes; i++) {
        int num = randomNum(generator);
        char byte = 32 + num;
        file << byte;
        // if (count % 205 == 0) {
        //     file << '\n';
        // }
        // count++;
    }
    file.close();
}

std::string readFile(std::string fileName) {
    std::ifstream file;
    file.open(fileName);
    std::string output = "";
    std::string line;
    while (getline(file, line)) {
        output += line + " ";
    };
    file.close();
    return output;
}
