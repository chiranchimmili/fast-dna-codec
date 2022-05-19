#include <iostream>
#include <string>
#include "ids.h"

using namespace std;

int main() {
    srand (time (NULL));

    string str = "AATCGCTAGTAACTGGATGCGTCAATCT";
    int errorChance = 2;    // 2% error rate per base 
    cout << ids(str, errorChance) << endl;
}

string ids(string str, int percentError) {
    for (int i = 0; i < str.size(); i++) {
        if (rand() % 100 <= percentError) {
            int randIds = rand() % 100;
            char randBas = randomBase();

            if (randIds < 25) {
                str.insert(i, 1 , randBas);
            } else if (randIds >= 25 && randIds < 50) {
                str.erase(i, 1);
            } else {
                while (randBas == str[i]) {
                    randBas = randomBase();
                }
                str[i] = randBas;
            }
        }
    }
    return str;
}

char randomBase() {
    return bases[rand() % 4];
}

