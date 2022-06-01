#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>


// std::unordered_map<std::vector<int>, std::unordered_map<std::vector<int>, std::vector<int>>> createMultiplcationTable(int n) {

// }

struct VectorHasher {
    int operator()(const std::vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHasher> test(int c) {
    int n = pow(2, c);
    std::cout << n << std::endl;
    std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHasher> result;
    std::vector<int> x{0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        std::vector<std::vector<int>> toAdd;
        std::vector<int> y{0, 0, 0, 0, 0, 0, 0, 0};
        for (int j = 0; j < n; j++) {
            toAdd.push_back(y);
            int a = c - 1;
            while (y[a] == 1 && a > 0) {
                y[a] = 0;
                a--;
            }
            y[a] = 1;
        }
        result[x] = toAdd;
        int b = c - 1;
        while (x[b] == 1 && b > 0) {
            x[b] = 0;
            b--;
        }
        x[b] = 1;
    }
    return result;
}



int main() {
    std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHasher> e = test(8);
    // for (auto& t : e) {
    //     std::cout << "E" << std::endl;
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
}

