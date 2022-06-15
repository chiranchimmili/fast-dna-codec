#include "../galois/G256log.cpp"

#include <stdint.h>

#include <bitset>
#include <iostream>
#include <random>
#include <string>


Galois::G256 field;


std::vector<uint8_t> polyMult(std::vector<uint8_t> *a, std::vector<uint8_t> *b) {
    std::vector<uint8_t> result((*a).size() + (*b).size() - 1);

    for (int i = 0; i < (*a).size(); i++) {
        Galois::Elem c(&field, (*a)[i]);
        for (int j = 0; j < (*b).size(); j++) {
            Galois::Elem d(&field, (*b)[j]);
            (result)[i + j] ^= (c * d).val;
        }
    }
    return result;
}

uint8_t GFPower(int x, int power) {
    return field.antilog[(field.log[x] * power) % 255];
}

std::vector<uint8_t> genPoly(int n) {
    std::vector<uint8_t> result{1};
    for (int i = 0; i < n; i++) {
        std::vector<uint8_t> a = {1, GFPower(2, i)};
        result = polyMult(&result, &a);
    }
    return result;
}

uint8_t eval(std::vector<uint8_t> *poly, Galois::Elem *c) {
    Galois::Elem d(&field, (*poly)[0]);
    for (int i = 1; i < (*poly).size(); i++) {
        Galois::Elem e(&field, ((*c) * d).val);
        Galois::Elem f(&field, (*poly)[i]);
        d.val = (e + f).val;
    }
    return d.val;
}

std::vector<uint8_t> syndrome(std::vector<uint8_t> *encoded, int n) {
    std::vector<uint8_t> result(n);
    for (int i = 0; i < n; i++) {
        Galois::Elem a(&field, GFPower(256, i));
        result[i] = eval(encoded, &a);
    }
    return result;
}

int main() {
    
    std::vector<uint8_t> a = {23, 4, 9, 131, 42};
    std::vector<uint8_t> b = {16, 52, 13, 211, 30, 19};

    std::vector<uint8_t> c = genPoly(4);

    std::vector<uint8_t> message = {146, 163, 17, 183, 147, 228, 171, 179, 47, 218, 144, 93, 68, 187, 77, 51, 42, 195, 209, 220, 65, 
        18, 141, 123};
    std::vector<uint8_t> synd = syndrome(&message, 4);
    for (uint8_t e : synd) {
        std::cout << unsigned(e) << std::endl;
    }

}
