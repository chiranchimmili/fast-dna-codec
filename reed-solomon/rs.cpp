#include <stdint.h>

#include <bitset>
#include <iostream>
#include <random>
#include <string>

#include "../crc/crc.cpp"
#include "../galois/G256log.cpp"

Galois::G256 Field;

std::vector<uint8_t> polyMult(std::vector<uint8_t> *a, std::vector<uint8_t> *b) {
    std::vector<uint8_t> result((*a).size() + (*b).size() - 1);

    for (int i = 0; i < (*a).size(); i++) {
        Galois::Elem c(&Field, (*a)[i]);
        for (int j = 0; j < (*b).size(); j++) {
            Galois::Elem d(&Field, (*b)[j]);
            (result)[i + j] ^= (c * d).val;
        }
    }
    return result;
}

uint8_t GFPower(int x, int power) {
    return Field.antilog[(Field.log[x] * power) % 255];
}

std::vector<uint8_t> genPoly(int n) {
    std::vector<uint8_t> result{1};
    for (int i = 0; i < n; i++) {
        std::vector<uint8_t> a = {1, GFPower(3, i)};
        result = polyMult(&result, &a);
    }
    return result;
}

uint8_t eval(std::vector<uint8_t> *poly, Galois::Elem *c) {
    Galois::Elem d(&Field, (*poly)[0]);
    for (int i = 1; i < 22; i++) {
        Galois::Elem e(&Field, ((*c) * d).val);
        Galois::Elem f(&Field, (*poly)[i]);
        d.val = (e + f).val;
    }
    return d.val;
}

std::vector<uint8_t> syndrome(std::vector<uint8_t> *encoded, int n) {
    std::vector<uint8_t> result(n);
    for (int i = 0; i < n; i++) {
        Galois::Elem a(&Field, GFPower(3, i));
        result[i] = eval(encoded, &a);
    }
    return result;
}

void oneError(std::vector<uint8_t> *randomMsgWithCRC, int count1) {
    for (int i = 0; i < 22; i++) {
        std::vector<uint8_t> x = *randomMsgWithCRC;
        uint8_t randNum = randomNum(generator);
        while (randNum == (x)[i]) {
            randNum = randomNum(generator);
        }
        (x)[i] = randNum;
        std::vector<uint8_t> synd = syndrome(&x, 2);

        if (!(synd[0]) && !(synd[1])) {
            count1 += 1;
        }
    }
}

void twoErrors(std::vector<uint8_t> *randomMsgWithCRC, int count2) {
    for (int i = 0; i < 22; i++) {
        std::vector<uint8_t> x = *randomMsgWithCRC;
        uint8_t randNum = randomNum(generator);
        while (randNum == (x)[i]) {
            randNum = randomNum(generator);
        }
        (x)[i] = randNum;
        for (int j = 1; j < 22; j++) {
            std::vector<uint8_t> y = x;
            uint8_t randNum = randomNum(generator);
            while (randNum == (y)[(i + j) % 22]) {
                randNum = randomNum(generator);
            }
            (y)[(i + j) % 22] = randNum;
            std::vector<uint8_t> synd = syndrome(&y, 2);

            if (!(synd[0]) && !(synd[1])) {
                count2 += 1;
            }
        }
    }
}

int main() {
    std::vector<uint8_t> genPoly{0x1, 0x02, 0x03};

    int count1 = 0;
    int count2 = 0;
    for (int l = 0; l < 100000; l++) {
        std::vector<uint8_t> *message = new std::vector<uint8_t>();
        for (int i = 0; i < 20; i++) {
            (*message).push_back(randomNum(generator));
        }
        message->push_back(0);
        message->push_back(0);

        std::vector<uint8_t> *randomMsgWithCRC = message;
        crc(&Field, randomMsgWithCRC, &genPoly);
        oneError(randomMsgWithCRC, count1);
    }
    for (int l = 0; l < 100000; l++) {
        std::vector<uint8_t> *message = new std::vector<uint8_t>();
        for (int i = 0; i < 20; i++) {
            (*message).push_back(randomNum(generator));
        }
        message->push_back(0);
        message->push_back(0);
        std::vector<uint8_t> *randomMsgWithCRC = message;
        crc(&Field, randomMsgWithCRC, &genPoly);
        twoErrors(randomMsgWithCRC, count2);
    }

    std::cout << "No 1 error detected count: " << count1 << std::endl;
    std::cout << "No 2 errors detected count: " << count2 << std::endl;
}
