#include "../include/crc.hpp"

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <array>

typedef uint32_t crc;
#define GENERATOR_POLY (0xad0424f3);
#define WIDTH (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

std::array<crc, 256> generateLookupTable() {
    std::array<crc, 256> table;
    crc remainder;
    for (int dividend = 0; dividend < 256; ++dividend) {
        remainder = dividend << (WIDTH - 8);
        for (uint8_t bit = 0; bit < 8; bit++) {
            remainder = (remainder << 1) ^ ((remainder & TOPBIT) ? 0xad0424f3 : 0);
        }
        table[dividend] = remainder;
    }
    return table;
} 

crc crcFast(const std::array<uint8_t, 32> byteArray) {
    static auto const crcLookupTable = generateLookupTable();
    uint8_t data;
    crc remainder = 0;

    for (int byte = 0; byte < byteArray.size(); ++byte) {
        data = byteArray[byte] ^ (remainder >> (WIDTH - 8));
        remainder = crcLookupTable[data] ^ (remainder << 8);
    }
    return remainder;
}

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


