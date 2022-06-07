//#pragma optimize("", off)
#include "galois.cpp"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    //GaloisField GF(8, {1, 0, 0, 0, 1, 1, 0, 1, 1});
    std::vector<int> a{1, 0, 1, 1, 0, 0, 0, 1};
    std::vector<int> b{1, 1, 1, 1, 0, 1, 0, 0};

    // std::cout << '\n' << "mult" << std::endl;
    // std::vector<int> c = GF.mult(a, b);
    // for (int i = 0; i < 20; i++) {
    //     GF = GaloisField(8, {1, 0, 0, 0, 1, 1, 0, 1, 1});
    // }
    long long int ab = 1;
    long long int bb = 2;
    long long int bc;
    for (int i = 0; i < 2000000000; i++) {
        bc = ab + bb;
        // for (int &i : c) {
        //     std::cout << i;
        // }
    }
    // std::cout << '\n' << "div" << std::endl;
    // c = GF.div(a, b);
    // // for (int &i : c) {
    // //     std::cout << i;
    // // }
    // std::cout << '\n' << "add" << std::endl;
    // c = GF.add(a, b);
    // // for (int &i : c) {
    // //     std::cout << i;
    // // }
    // std::cout << '\n' << "sub" << std::endl;
    // c = GF.sub(a, b);
    // // for (int &i : c) {
    //     std::cout << i;
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
