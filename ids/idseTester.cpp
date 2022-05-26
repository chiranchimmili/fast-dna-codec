#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "idse.cpp"
#include "../include/idseTester.hpp"

using namespace std;

int main() {
    parser->parseJSONFile("sample.json");
    generateRandomInputFile();

    ifstream inFile;
    ofstream unorderedOutFile;
    ofstream orderedOutFile;

    vector<string> populatedOligos = generateOligosVector(inFile);
    generateOutputFiles(unorderedOutFile, orderedOutFile, populatedOligos);
}

void generateRandomInputFile() {
    ofstream randomInFile;
    randomInFile.open(parser->input, ios::out | ios::trunc);
    for (int i = 1; i < parser->numberOligos + 1; i++) {
        randomInFile << '>' << i << "\n" << randomOligo() << endl;
    }
    randomInFile.close();
}

string randomOligo() {
    string oligo = "";
    for (int i = 0; i < parser->lengthOligos; i++) {
        oligo += RANDOMBASE;
    }
    return oligo;
}
