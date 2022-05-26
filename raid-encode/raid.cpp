#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <cstddef>
#include "raid.hpp"
 
using namespace std;

const int byteVectorLength = 10;


int main() {
    // Static test
    string str = "abcdfesdjlp3kdnaj501abcdfesdjlp3kdnaj501";
    vector<unsigned char> bytes;
    for (unsigned char c : str) {
        bytes.push_back(c);
    }
    vector<vector<unsigned char>> encoded = encode(bytes, byteVectorLength);
    encoded.erase(encoded.begin() + 1);
    cout << decode(encoded, 1) << endl;
}

vector<vector<unsigned char>> encode(vector<unsigned char> bytes, int columns) {
    int numrows = bytes.size()/columns;
    vector<vector<unsigned char>> rows;
    int k = 0;
    for (int i = 0; i < numrows; i++) {
        vector<unsigned char> row;
        for (int j = k; j < k + columns; j++) {
            row.push_back(bytes[j]);
        }
        k+=columns;
        rows.push_back(row);
    }
    vector<unsigned char> xorRow;
    for (int i = 0; i < columns; i++) {
        unsigned char xorByte;
        for (vector<unsigned char> v : rows) {
            xorByte ^= v[i];
        }
        xorRow.push_back(xorByte);
    }
    rows.push_back(xorRow);
    return rows;
}

string decode(vector<vector<unsigned char>> encoded, int removedByteVector) {

    vector<unsigned char> xorRow;
    for (int i = 0; i < encoded[i].size(); i++) {
        unsigned char xorByte = static_cast<unsigned char>(0);
        for (vector<unsigned char> v : encoded) {
            xorByte ^= v[i];
        }
        xorRow.push_back(xorByte);
    }
    encoded.insert(encoded.begin() + removedByteVector, xorRow);

    string str = "";
    for (int i = 0; i < encoded.size() - 1; i++) {
        for (unsigned char c : encoded[i]) {
            str.push_back(c);
        }
    }
    return str;
}




