#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "../include/idse.h"
#include "jsonParser.cpp"

using namespace std;

vector<string> oligos;
int numOligos;

vector<string> generateOligosVector(ifstream &inFile) {
    inFile.open(parser->input);         // Opens input FAFSTA file
    string line;
    while (getline(inFile, line)) {     // Scans each line and creates vector of oligos
        if (!line.empty()) {
            if (line[0] != '>') {
                oligos.push_back(line);
            }
        }
    }
    inFile.close();
    numOligos = oligos.size();
    return oligos;
}

int generateIdsType() {
    double rnd = (double) randomIds(generator) / 100.0;
    if (rnd <= errorWeights[0]) {     // Insert error
        return 0;
    }
    else if (rnd > errorWeights[0] && rnd <= errorWeights[0] + errorWeights[1] ) {    // Delete error
        return 1;
    }
    else if (rnd > errorWeights[0] + errorWeights[1] && rnd <= errorWeights[0] + errorWeights[1] + errorWeights[2]) {
        return 2;  // Substitution Error
    }
    return 3;     // No Error
}

string performIds(string str) {
    for (int i = 0; i < str.size(); i++) {
        int randIds = generateIdsType();
        char randBas = RANDOMBASE;
        if (randIds == 0) {
            str.insert(i, 1 , randBas);
            i++;
        } else if (randIds == 1) {
            str.erase(i, 1);
            i--;
        } else if (randIds == 2) {
            while (randBas == str[i]) {
                randBas = RANDOMBASE;
            }
            str[i] = randBas;
        } else {
            continue;
        }
    }
    return str;
}

void generateOutputFiles(ofstream &unorderedOutFile, ofstream &orderedOutFile, vector<string> oligos) {
    unorderedOutFile.open(parser->unorderedOutput, ios::out | ios::trunc);
    orderedOutFile.open(parser->orderedOutput, ios::out | ios::trunc);
    vector<pair<int, string>> ordered;
    uniform_int_distribution<int> randomOligo(0, numOligos - 1);

    for (int i = 0; i < parser->numberReads; i++) {
        int oligoNumber = randomOligo(generator);
        string errorStr = performIds(oligos[oligoNumber]);
        ordered.emplace_back(oligoNumber + 1, errorStr);
        unorderedOutFile << ">" << (oligoNumber + 1) << "\n" << errorStr << endl;
    }
    sort(ordered.begin(), ordered.end());
    for (int i = 0; i < ordered.size(); i++) {
        orderedOutFile << ">" << ordered[i].first << "\n" << ordered[i].second << endl;
    }
    unorderedOutFile.close();
    orderedOutFile.close();
}





