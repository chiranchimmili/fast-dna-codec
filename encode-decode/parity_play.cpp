#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include "parity_play.h"

using namespace std;

int main() {
    string str = "Hello World";
    string encoded = encode(str);
    cout << decode(encoded) << endl;
    
    encoded.replace(encoded.size() - 1, 1 , "T");     // change to incorrect base (SVR)
    cout << decode(encoded) << endl;
    return 0;
}

string encode(string str) {
    string binary = "";
    for (char& c : str) {
        binary += bitset<8>(c).to_string();
    }
    string parityByte = bitset<8>(count(binary.begin(), binary.end(), '1') % 255).to_string();
    binary += parityByte;
    return binaryToBase(binary);
}

string decode(string baseStr) {
    string str = "";
    string binary = baseToBinary(baseStr);
    for (int i = 0; i < binary.size() - 8; i+=8) {
        string byte = binary.substr(i, 8);
        str += char(bitset<8>(byte).to_ulong());
    }
    int parityCount = stoi(binary.substr(binary.size() - 8, 8), nullptr, 2);
    if (count(binary.begin(), binary.end() - 8, '1') == parityCount) {
        return str;
    } else {
        return "Parity error";
    }
}

string binaryToBase(string binary) {
    string baseStr = "";
    for (int i = 0; i < binary.size(); i+=2) {
        baseStr += binaryBase[binary.substr(i, 2)];
    }
    return baseStr;
}

string baseToBinary(string str) {
    string binary = "";
    for (int i = 0; i < str.size(); i++) {
        binary += baseBinary[str.substr(i, 1)];
    }
    return binary;
}


