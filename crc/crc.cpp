#include "../include/crc.hpp"

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
/*
 * The width of the CRC calculation and result.
 * Modify the typedef for a 16 or 32-bit CRC standard.
 */

typedef uint32_t crc;
#define GENERATOR_POLY 0xad0424f3;
#define WIDTH (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

crc crcTable[256];

void crcInit(void) {
    crc remainder;
    /*
     * Compute the remainder of each possible dividend.
     */
    for (int dividend = 0; dividend < 256; ++dividend) {
        /*
         * Start with the dividend followed by zeros.
         */
        remainder = dividend << (WIDTH - 8);

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (uint8_t bit = 8; bit > 0; --bit) {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT) {
                remainder = (remainder << 1) ^ GENERATOR_POLY;
            } else {
                remainder = (remainder << 1);
            }
        }

        /*
         * Store the result into the table.
         */
        crcTable[dividend] = remainder;
    }

} /* crcInit() */

crc crcFast(uint8_t const message[], int nBytes) {
    uint8_t data;
    crc remainder = 0;

    /*
     * Divide the message by the polynomial, a byte at a time.
     */
    for (int byte = 0; byte < nBytes; ++byte) {
        data = message[byte] ^ (remainder >> (WIDTH - 8));
        remainder = crcTable[data] ^ (remainder << 8);
    }
    /*
     * The final remainder is the CRC.
     */
    return (remainder);

} /* crcFast() */

std::string hexer(int i) {
    std::ostringstream ss;
    ss << "0x" << std::hex << i;
    std::string result = ss.str();
    return result;
}

std::string binary(std::string s) {
    std::stringstream ss;
    ss << std::hex << s;
    unsigned n;
    ss >> n;
    std::bitset<8> b(n);
    // outputs "00000000000000000000000000001010"
    return b.to_string();
}


void x(std::vector<uint8_t> array) {
    std::vector<std::string> y;
    for (uint8_t num : array) {
        y.push_back(hexer(num));
    }
    std::vector<std::string> z;
    for (std::string s : y) {
        z.push_back(binary(s));
    }

    std::cout << z.size() << std::endl;
    int curr = 255;
    for (std::string c : z) {
        for (char b : c) {
            if (b == '1') {
                std::cout << "x^" << curr << "+" << std::endl;
            }
            curr--;
        }
    } 
}


int main() {

    crcInit();
    uint8_t message[] = {0xFF, 0x48, 0x12, 0x9C, 0xA, 0x53, 0xFD, 0x10, 0xFF, 0x48, 0x12, 0x9C, 0xA, 0x53, 0xFD, 0x10, 0xFF, 0x48, 0x12, 0x9C, 0xA, 0x53, 0xFD, 0x10, 0xFF, 0x48, 0x12, 0x9C, 0xA, 0x53, 0xFD, 0x10};
    //x(message);
    std::cout << crcFast(message, 32) << std::endl;
}
