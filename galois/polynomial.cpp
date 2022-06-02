#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "../include/polynomial.hpp"

int polynomialDegree(std::vector<int> polynomial) {
    int degree = polynomial.size() - 1;
    for (int i = 0; i < polynomial.size(); i++) {
        if (polynomial[i]) {
            break;
        }
        degree--;
    }
    return degree;
}

std::vector<int> multiplyPolynomials(std::vector<int> a, std::vector<int> b) {
    std::vector<int> result(2 * a.size() - 1);
    int x = a.size() - 1;
    for (int i = 0; i < a.size(); i++) {
        int y = b.size() - 1;
        for (int j = 0; j < b.size(); j++) {
            if (a[i] && b[j]) {
                if (result[result.size() - 1 - (x + y)]) {
                    result[result.size() - 1 - (x + y)] = 0;
                } else {
                    result[result.size() - 1 - (x + y)] = 1;
                }
            }
            y--;
        }
        x--;
    }
    return result;
}

std::vector<int> longDivision(std::vector<int> divisor, std::vector<int> dividend) {
    int divisorDegree = polynomialDegree(divisor);
    int dividendDegree = polynomialDegree(dividend);
    int originalDividendDegree = dividendDegree;
    while (divisorDegree <= dividendDegree) {
        std::vector<int> multipliedDivisor(dividend.size(), 0);
        for (int i = 0; i < divisor.size(); i++) {
            multipliedDivisor[dividend.size() - dividendDegree - 1 + i] = divisor[i];
        }
        for (int i = 0; i < dividend.size(); i++) {
            dividend[i] = multipliedDivisor[i] ^ dividend[i];
        }
        dividendDegree = polynomialDegree(dividend);
    }
    std::vector<int> subvector = {dividend.begin() + ((dividendDegree - divisorDegree) + 1), dividend.end()};
    return subvector;
}

std::vector<int> incVector(std::vector<int> v, int length) {
    int a = length - 1;
    while (v[a] == 1 && a > 0) {
        v[a] = 0;
        a--;
    }
    v[a] = 1;
    return v;
}