#include <iostream>
#include <string>
#include "ids.h"

using std::string;

int main() {
    srand (time (NULL));
    string str = "AATCGCTA";
    int randIds = rand() % 3;
    int randPos = rand() % str.length();
    char randBas = randomBase();
    
    if (randIds == 0) {
        str.insert(randPos, 1 , randBas);
    }
    else if (randIds == 1) {
        str.erase(randPos, 1);
    }
    else {
        while (randBas == str[randPos]) {
            randBas = randomBase();
        }
        str[randPos] = randBas;
    }
    std::cout << str;
}

char randomBase() {
    return bases[rand() % 4];
}

