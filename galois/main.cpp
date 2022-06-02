#include "galois.cpp"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    GaloisField GF;
    std::vector<int> a{1, 0, 1, 1, 0, 0, 0, 1};
    std::vector<int> b{1, 1, 1, 1, 0, 1, 0, 0};

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
