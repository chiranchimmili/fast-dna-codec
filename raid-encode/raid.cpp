#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <cstddef>
#include <bitset>
#include "raid.hpp"
 
using namespace std;


int main() {
    string str = "abcdfesdjlp3kdnaj501";;
    vector<unsigned char> bytes;
    for (unsigned char c : str) {
        bytes.push_back(c);
    }
    vector<vector<unsigned char>> encoded = encode(bytes, 5);
    cout << decode(encoded, 5) << endl;
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

string decode(vector<vector<unsigned char>> encoded, int removed) {
    int column = removed % 5;
    int row = removed / 5;
    encoded[row][column] = 0;
    unsigned char xorByte;
    for (int i = 0; i < encoded.size(); i++) {
        //cout << static_cast<unsigned>(encoded[i][column]) << endl;
        xorByte ^= encoded[i][column];
    }
    encoded[row][column] = xorByte;

    string str = "";
    for (int i = 0; i < encoded.size() - 1; i++) {
        for (unsigned char c : encoded[i]) {
            str.push_back(c);
        }
    }
    return str;
}




