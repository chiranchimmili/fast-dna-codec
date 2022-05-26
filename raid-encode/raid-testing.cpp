#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <cstddef>
#include <algorithm>
#include "raid.cpp"
 
using namespace std;

int byteVectorLengthTest;
string chars {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?"};
random_device rd;
mt19937 generator(rd());

int main() {
    string str = rand_str(120);
    vector<unsigned char> bytes;
    for (unsigned char c : str) {
        bytes.push_back(c);
    }
    byteVectorLengthTest = 10;

    int removedByte = rand_int(bytes.size() - 1);

    vector<vector<unsigned char>> encoded = encode(bytes, byteVectorLength);
    int column = removedByte % byteVectorLength;
    int row = removedByte / byteVectorLength;
    encoded[row][column] = 0;
    cout << decode(encoded, removedByte) << endl;
} 

string rand_str (size_t length) {
    const size_t char_size = chars.size();
    uniform_int_distribution<> random_int(0, char_size - 1);
    string output;
    for (size_t i=0; i<length; ++i) {
        output.push_back(chars[random_int(generator)]);
    }
    return output;
}

int rand_int(int max) {
    uniform_int_distribution<> random_int(0, max);
    return random_int(generator);
}


