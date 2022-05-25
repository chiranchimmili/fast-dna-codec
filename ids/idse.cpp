#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "../include/idse.h"
#include "jsonParser.cpp"

using namespace std;

vector<string> oligos;
random_device rand_dev;
mt19937 generator(rand_dev());
uniform_int_distribution<int> randomOligo(1, 274);
uniform_int_distribution<int> randomIds(1, 100);
jsonParser *parser = new jsonParser();

int main() {
    parser->parseFile("sample.json");

    ifstream inFile;
    ofstream unorderedOutFile;
    ofstream orderedOutFile;

    vector<string> populatedOligos = generateOligosVector(inFile);
    generateOutputFiles(unorderedOutFile, orderedOutFile, populatedOligos);
}

vector<string> generateOligosVector(ifstream &inFile) {
    inFile.open(parser->input);
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            if (line[0] != '>') {
                oligos.push_back(line);
            }
        }
    }
    inFile.close();
    return oligos;
}

void generateOutputFiles(ofstream &unorderedOutFile, ofstream &orderedOutFile, vector<string> oligos) {
    unorderedOutFile.open(parser->unorderedOutput, ios::out | ios::trunc);
    orderedOutFile.open(parser->orderedOutput, ios::out | ios::trunc);
    vector<pair<int, string>> ordered;

    for (int i = 0; i < parser->numberReads; i++) {
        int oligoNumber = randomOligo(generator);
        string errorStr = performIds(oligos[oligoNumber]);
        ordered.emplace_back(oligoNumber, errorStr);
        unorderedOutFile << ">" << oligoNumber << "\n" << errorStr << endl;
    }
    sort(ordered.begin(), ordered.end());
    for (int i = 0; i < ordered.size(); i++) {
        orderedOutFile << ">" << ordered[i].first << "\n" << ordered[i].second << endl;
    }
    unorderedOutFile.close();
    orderedOutFile.close();
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





