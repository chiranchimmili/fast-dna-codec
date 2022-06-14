#include "../include/crc.hpp"

#include <stdint.h>

#include <bitset>
#include <iostream>
#include <random>
#include <string>

#include "G256.cpp"

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> randomNum(0, 255);

void crc(Galois::G256 *field, std::vector<uint8_t> *message, std::vector<uint8_t> *genPoly) {
    std::vector<uint8_t> retVec = *message;
    for (int i = 0; i < 16; i++) {
        Galois::Elem a(field, retVec[i]);
        for (int j = 0; j < 5; j++) {
            if ((*genPoly)[j] != 0) {
                Galois::Elem b(field, (*genPoly)[j]);
                Galois::Elem c(field, retVec[i + j]);
                Galois::Elem d(field, (a / b).val);
                retVec[i + j] = (c - d).val;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        message->push_back(retVec[16 + i]);
    }
}

int main() {
    // std::vector<uint8_t> messageArray{0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
    // std::vector<uint8_t> randomMsgWithCRC{0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
    std::vector<uint8_t> genPoly{0x1, 0x0f, 0x36, 0x78, 0x40};  // x^4 + x + 1

    Galois::G256 field;
    int count = 0;
    for (int k = 0; k < 1000000; k++) {
        std::vector<uint8_t> *message = new std::vector<uint8_t>();
        for (int i = 0; i < 20; i++) {
            (*message).push_back(randomNum(generator));
        }
        //std::vector<uint8_t> messageArray{0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
        std::vector<uint8_t> *randomMsgWithCRC = message;

        crc(&field, randomMsgWithCRC, &genPoly);

        for (int i = 0; i < 24; i++) {
            std::vector<uint8_t> x = *randomMsgWithCRC;
            uint8_t randNum = randomNum(generator);
            while (randNum == (x)[i]) {
                randNum = randomNum(generator);
            }
            (x)[i] = randNum;
            for (int j = 1; j < 24; j++) {
                uint8_t randNum = randomNum(generator);
                while (randNum == (x)[(i + j) % 24]) {
                    randNum = randomNum(generator);
                }
                (x)[(i + j) % 24] = randNum;
                std::vector<uint8_t> subvector = {x.begin(), x.end() - 4};
                crc(&field, &subvector, &genPoly);
                if ((subvector)[20] == (x)[20] && (subvector)[21] == (x)[21] && (subvector)[22] == (x)[22] && (subvector)[23] == (x)[23]) {
                    count += 1;
                }
            }
        }
    }
    std::cout << count << std::endl;
}
