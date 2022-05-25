#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "idse.h"

using namespace std;

random_device rand_dev;
mt19937 generator(rand_dev());
uniform_int_distribution<int> randomOligo(1, 274);
uniform_int_distribution<int> randomIds(1, 100);


int main() {
    string input = "input.fafsta";
    string output = "output.fafsta";
    ifstream inFile;
    ofstream outFile;
    string line;

    inFile.open(input);
    outFile.open(output, ios::out | ios::trunc);

    if (!inFile) {
        cout << "input file does not exist" << endl;
        return 0;
    }
  
    vector<string> oligos(275);
    int i = 0;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            if (line[0] != '>') {
                oligos[i] = line;
                i++;
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        int oligoNumber = randomOligo(generator);
        string errorStr = performIds(oligos[oligoNumber]);
        outFile << ">" << oligoNumber << endl;
        outFile << errorStr << endl;;
    }

    inFile.close();
    outFile.close();
}


int generateIdsType() {
    int rnd = (double) randomIds(generator) / 100;
    if (rnd <= errorWeights[0]) {
        return 0;
    }
    else if (rnd > errorWeights[0] && rnd <= errorWeights[0] + errorWeights[1] ) {
        return 1;
    }
    else if (rnd > errorWeights[0] + errorWeights[1] && rnd <= errorWeights[0] + errorWeights[1] + errorWeights[3]) {
        return 2;
    }
    return 3;
}

string performIds(string str) {
    for (int i = 0; i < str.size(); i++) {
        int randIds = generateIdsType();
        char randBas = randomBase();
        if (randIds == 0) {
            str.insert(i, 1 , randBas);
            i++;
        } else if (randIds == 1) {
            str.erase(i, 1);
            i--;
        } else if (randIds == 2) {
            while (randBas == str[i]) {
                randBas = randomBase();
            }
            str[i] = randBas;
        } else {
            continue;
        }
    }
    return str;
}

char randomBase() {
    return bases[rand() % 4];
}




