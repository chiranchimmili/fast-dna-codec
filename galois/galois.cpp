#include "../include/galois.hpp"
#include "polynomial.cpp"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

class GaloisField {

   public:
    // Default is GF(2^2)
    GaloisField() {
        setLookupTables();
    };
    GaloisField(int n, std::vector<int> IP): n(n), IP(IP) {
        GaloisField();
    }

    private:
    int n = 2;
    std::vector<int> IP = {1, 0, 1, 1};
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> multTable;
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> divTable;

    void setLookupTables() {
        multTable = multLookup();
        divTable = divLookup(multTable);
    }

    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> multLookup() {
        int total = pow(2, n);
        std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> result;
        std::vector<int> x(n, 0);
        for (int i = 0; i < total; i++) {
            std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> toAdd;
            std::vector<int> y(n, 0);
            for (int j = 0; j < total; j++) {
                toAdd[y] = longDivision(IP, multiplyPolynomials(x, y));
                y = incVector(y, n);
            }
            result[x] = toAdd;
            x = incVector(x, n);
        }
        return result;
    }
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> divLookup(std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> mult) {
        std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> div = mult;
        int total = pow(2, n);
        std::vector<int> x(n, 0);
        for (int i = 0; i < total; i++) {
            std::vector<int> y(n, 0);
            for (int j = 0; j < total; j++) {
                div[longDivision(IP, multiplyPolynomials(x, y))][x] = y;
                y = incVector(y, n);
            }
            x = incVector(x, n);
        }
        return div;
    }
};
