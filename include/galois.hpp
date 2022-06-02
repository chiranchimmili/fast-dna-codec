#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

struct VectorHasher {
    int operator()(const std::vector<int> &V) const {
        int hash = V.size();
        for (auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};