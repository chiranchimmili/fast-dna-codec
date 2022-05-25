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
    parser->setParameters();

    ifstream inFile;
    ofstream outFile;

    vector<string> oligos = generateOligosVector(inFile, parser);
    generateOutputFile(outFile, parser, oligos);
}

vector<string> generateOligosVector(ifstream &inFile, jsonParser *parser) {
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

void generateOutputFile(ofstream &outFile, jsonParser *parser, vector<string> oligos) {
    outFile.open(parser->output, ios::out | ios::trunc);
    for (int i = 0; i < parser->numberReads; i++) {
        int oligoNumber = randomOligo(generator);
        string errorStr = performIds(oligos[oligoNumber]);
        outFile << ">" << oligoNumber << "\n" << errorStr << endl;
    }
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




