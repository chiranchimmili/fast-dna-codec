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

void test(Galois::G256 field, std::vector<uint8_t> **message, std::vector<uint8_t> *genPoly) {
    for (int i = 0; i < 16; i++) {
        Galois::Elem a(&field, (**message)[i]);
        for (int j = 0; j < 5; j++) {
            Galois::Elem b(&field, (*genPoly)[j]);
            if (b.val != 0) {
                Galois::Elem c(&field, (**message)[i + j]);
                Galois::Elem d(&field, (a / b).val);
                (**message)[i + j] = (c - d).val;
            }
        }
    }
}

std::vector<uint8_t> test2(std::vector<uint8_t> messageArray, std::vector<uint8_t> genPoly) {
    Galois::G256 field;
    std::vector<uint8_t> divisionArray(5, 0);

    for (int i = 0; i < 17; i++) {
        for (int k = 0; k < 5; k++) {
            if (i > 0) {
                Galois::Elem a(&field, messageArray[i + k - 1]);
                Galois::Elem b(&field, divisionArray[k]);
                messageArray[i + k - 1] = (a - b).val;
            }
        }

        for (int m = 0; m < 5; m++) {
            divisionArray[m] = 0;
        }

        for (int j = 0; j < 5; j++) {
            Galois::Elem d(&field, genPoly[j]);
            Galois::Elem e(&field, messageArray[i]);
            if (d.val != 0) {
                uint8_t div = (e / d).val;
                divisionArray[j] = div;
            }
        }
    }
    return messageArray;
}

int main() {
    std::vector<uint8_t> messageArray{0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
    //  std::vector<uint8_t> testArray{0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
    std::vector<uint8_t> genPoly{0x1, 0x0, 0x0, 0x1, 0x1};  // x^4 + x + 1

    // std::vector<uint8_t> *m = test(&messageArray, &genPoly);
    Galois::G256 field;
    for (int k = 0; k < 100; k++) {
        std::vector<uint8_t> *message = new std::vector<uint8_t>();
        for (int i = 0; i < 20; i++) {
            (*message).push_back(randomNum(generator));
        }

        std::vector<uint8_t> testArray = *message;
        test(field, &message, &genPoly);

        for (int i = 0; i < 20; i++) {
            std::vector<uint8_t> *x = &testArray;
            (*x)[i] = randomNum(generator);
            for (int j = i + 1; j < 20; j++) {
                (*x)[j] = randomNum(generator);
                test(field, &x, &genPoly);
                if ((*x)[16] == (*message)[16] && (*x)[17] == (*message)[17] && (*x)[18] == (*message)[18] && (*x)[19] == (*message)[19]) {
                    std::cout << "No error" << std::endl;
                }
            }
        }
    }
}

// int main() {
//     uint8_t messageArray[] = {0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
//     uint8_t divisionArray[5] = {0x0};

//     uint8_t genPoly[] = {0x1, 0x0, 0x0, 0x1, 0x1};  // x^4 + x + 1

//     Galois::G256 field;
//     for (int m = 0; m < 100; m++) {
//         // for (int i = 0; i < 17; i++) {
//         //     for (int k = 0; k < 5; k++) {
//         //         if (i > 0) {
//         //             Galois::Elem a(&field, messageArray[i + k - 1]);
//         //             Galois::Elem b(&field, divisionArray[k]);
//         //             messageArray[i + k - 1] = (a - b).val;
//         //         }
//         //     }

//         //     for (int m = 0; m < 5; m++) {
//         //         divisionArray[m] = 0;
//         //     }

//         //     for (int j = 0; j < 5; j++) {
//         //         Galois::Elem d(&field, genPoly[j]);
//         //         Galois::Elem e(&field, messageArray[i]);
//         //         if (d.val != 0) {
//         //             uint8_t div = (e / d).val;
//         //             divisionArray[j] = div;
//         //         }
//         //     }
//         // }
//         for (int i = 0; i < 16; i++) {
//             Galois::Elem a(&field, messageArray[i]);
//             for (int j = 0; j < 5; j++) {
//                 Galois::Elem b(&field, genPoly[j]);
//                 if (b.val != 0) {
//                     Galois::Elem c(&field, messageArray[i + j]);
//                     Galois::Elem d(&field, (a / b).val);
//                     messageArray[i + j] = (c - d).val;
//                 }
//             }
//         }
//     }
// }