#include "../include/galois.hpp"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "polynomial.cpp"

class GaloisField {
   public:
    // Default is GF(2^2)
    GaloisField() {
        setLookupTables();
    };
    GaloisField(int n, std::vector<int> IP) : n(n), IP(IP) {
        setLookupTables();
    }

    std::vector<int> mult(std::vector<int> a, std::vector<int> b) {
        return multTable[a][b];
    }
    std::vector<int> div(std::vector<int> a, std::vector<int> b) {
        return divTable[a][b];
    }
    std::vector<int> add(std::vector<int> a, std::vector<int> b) {
        return addTable[a][b];
    }
    std::vector<int> sub(std::vector<int> a, std::vector<int> b) {
        return subTable[a][b];
    }

   private:
    int n = 2;
    std::vector<int> IP = {1, 0, 1, 1};
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> multTable;
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> divTable;
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> addTable;
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> subTable;

    void setLookupTables() {
        multTable = multLookup();
        divTable = divLookup();
        addTable = addLookup();
        subTable = subLookup();
    }

    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> multLookup() {
        int total = pow(2, n);
        std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> mult;
        std::vector<int> x(n, 0);
        for (int i = 0; i < total; i++) {
            std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> toAdd;
            std::vector<int> y(n, 0);
            for (int j = 0; j < total; j++) {
                toAdd[y] = longDivision(IP, multiplyPolynomials(x, y));
                y = incVector(y, n);
            }
            mult[x] = toAdd;
            x = incVector(x, n);
        }
        return mult;
    }
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> divLookup() {
        std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> div = multTable;
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

    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> addLookup() {
        int total = pow(2, n);
        std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> add;
        std::vector<int> x(n, 0);
        for (int i = 0; i < total; i++) {
            std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> toAdd;
            std::vector<int> y(n, 0);
            for (int j = 0; j < total; j++) {
                std::vector<int> z(n, 0);
                for (int k = 0; k < n; k++) {
                    z[k] = x[k] ^ y[k];
                }
                toAdd[y] = z;
                y = incVector(y, n);
            }
            add[x] = toAdd;
            x = incVector(x, n);
        }
        return add;
    }
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> subLookup() {
        std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> sub = addTable;
        int total = pow(2, n);
        std::vector<int> x(n, 0);
        for (int i = 0; i < total; i++) {
            std::vector<int> y(n, 0);
            for (int j = 0; j < total; j++) {
                subTable[addTable[x][y]][x] = y;
                y = incVector(y, n);
            }
            x = incVector(x, n);
        }
        return sub;
    }
};
