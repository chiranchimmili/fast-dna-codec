#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include "parity_play.h"

using std::string;
using namespace std;

int main() {
    string str = "Hello World";
    str = parityAdd(stringToBinary(str));
    std::cout << str;
    return 0;
}

string stringToBinary(string str) {
    string binary = "";
    for (char& c : str) {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

string parityAdd(string str) {
    if (std::count(str.begin(), str.end(), '1') % 2 == 1) {
        return str += '1';
    } else {
        return str += '0';
    }
}


