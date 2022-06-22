#include "../include/crc.hpp"
#include "../galois/G256log.cpp"

#include <stdint.h>

#include <bitset>
#include <iostream>
#include <random>
#include <string>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> randomNum(0, 255);

void crc(Galois::G256 *field, std::vector<uint8_t> *message, std::vector<uint8_t> *genPoly) {
    std::vector<uint8_t> retVec = *message;
    for (int i = 0; i < 20; i++) {
        Galois::Elem a(field, retVec[i]);
        for (int j = 0; j < 3; j++) {
            Galois::Elem b(field, (*genPoly)[j]);
            Galois::Elem c(field, retVec[i + j]);
            Galois::Elem d(field, (a * b).val);
            retVec[i + j] = (c - d).val;
        }
    }
    (*message)[20] = (retVec[20]);
    (*message)[21] = (retVec[21]);
}