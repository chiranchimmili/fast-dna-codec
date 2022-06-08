#include "../include/crc.hpp"
#include "G256.cpp"

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <array>

// typedef uint32_t crc;
// #define GENERATOR_POLY (0xad0424f3);
// #define WIDTH (8 * sizeof(crc))
// #define TOPBIT (1 << (WIDTH - 1))

// std::array<crc, 256> generateLookupTable() {
//     std::array<crc, 256> table;
//     crc remainder;
//     for (int dividend = 0; dividend < 256; ++dividend) {
//         remainder = dividend << (WIDTH - 8);
//         for (uint8_t bit = 0; bit < 8; bit++) {
//             remainder = (remainder << 1) ^ ((remainder & TOPBIT) ? 0xad0424f3 : 0);
//         }
//         table[dividend] = remainder;
//     }
//     return table;
// } 

// crc crcFast(const std::array<uint8_t, 32> byteArray) {
//     static auto const crcLookupTable = generateLookupTable();
//     uint8_t data;
//     crc remainder = 0;

//     for (int byte = 0; byte < byteArray.size(); ++byte) {
//         data = byteArray[byte] ^ (remainder >> (WIDTH - 8));
//         remainder = crcLookupTable[data] ^ (remainder << 8);
//     }
//     return remainder;
// }

// std::string hexer(int i) {
//     std::ostringstream ss;
//     ss << "0x" << std::hex << i;
//     std::string result = ss.str();
//     return result;
// }

// std::string binary(std::string s) {
//     std::stringstream ss;
//     ss << std::hex << s;
//     unsigned n;
//     ss >> n;
//     std::bitset<8> b(n);
//     // outputs "00000000000000000000000000001010"
//     return b.to_string();
// }

// void x(std::vector<uint8_t> array) {
//     std::vector<std::string> y;
//     for (uint8_t num : array) {
//         y.push_back(hexer(num));
//     }
//     std::vector<std::string> z;
//     for (std::string s : y) {
//         z.push_back(binary(s));
//     }

//     std::cout << z.size() << std::endl;
//     int curr = 255;
//     for (std::string c : z) {
//         for (char b : c) {
//             if (b == '1') {
//                 std::cout << "x^" << curr << "+" << std::endl;
//             }
//             curr--;
//         }
//     } 
// }





int main() {

    uint8_t messageArray[] = {0x92, 0xa3, 0x11, 0xb7, 0x93, 0xe4, 0xab, 0xb3, 0x2f, 0xda, 0x90, 0x5d, 0x44, 0xbb, 0x4d, 0x33, 0x2a, 0xc3, 0xd1, 0xdc};
    uint8_t divisionArray[20] = {0x0};

    uint8_t genPoly[] = {0x1, 0x0, 0x0, 0x1};

    Galois::G256 field;
    for (int i = 0; i < 16; i++) {
        Galois::Elem a(&field, messageArray[i]);
        Galois::Elem b(&field, divisionArray[i]);
        divisionArray[i] = (a - b).val;
        
        for (int j = 0; j < 4; j++) {
            Galois::Elem d(&field, genPoly[j]);
            Galois::Elem e(&field, divisionArray[i]);
            if (d.val != 0) {
                uint8_t div = (e / d).val;
                divisionArray[i + j] = div;
            }
        }
    }
 }