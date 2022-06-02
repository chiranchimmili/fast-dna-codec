#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>


int n; 
std::vector<int> IP;

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

struct VectorHasher {
    int operator()(const std::vector<int> &V) const {
        int hash = V.size();
        for (auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

std::vector<int> incVector(std::vector<int> v, int length) {
    int a = length - 1;
    while (v[a] == 1 && a > 0) {
        v[a] = 0;
        a--;
    }
    v[a] = 1;
    return v;
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

int main() {
    std::vector<int> a{1, 0, 1, 1, 0, 0, 0, 1};
    std::vector<int> b{1, 1, 1, 1, 0, 1, 0, 0};
    IP = {1, 0, 1, 1};
    n = 2;
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> mult = multLookup();
    std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher>, VectorHasher> div = divLookup(mult);

    // std::vector<int> c = e[a][b];
    // for (int &i : c) {
    //     std::cout << i << std::endl;
    // }
    // std::vector<int> a{0, 1, 1, 0, 0, 1, 0, 1};
    // std::vector<int> b{1, 0, 1, 0, 1, 1, 0, 0};
    // std::vector<int> result = multiplyPolynomials(a, b);
    // for (int i : result) {
    //     std::cout << i << std::endl;
    // }
    // for (auto& t : e) {
    //     std::cout << e.size() << std::endl;
    //     for (auto& x : t.second) {
    //         std::cout << "EEEEEEEEEEEEEEEEEEEEEE" << std::endl;
    //         for (int f : x) {
    //             std::cout << f << std::endl;
    //         }
    //     }
    // }
    // for (auto& t : e) {
    //     std::cout << "E" << std::endl;
    //     for (auto& x : t.first) {
    //         std::cout << x << std::endl;
            
    //     }
    // }

    // std::vector<int> divisor{1, 0, 0, 0, 1, 1, 0, 1, 1};
    // std::vector<int> dividend{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0};

    // std::vector<int> result = longDivision(divisor, dividend);
    // for (int i : result) {
    //     std::cout << i << std::endl; //
    // }
}

