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
    vector<string> populatedOligos = generateOligosVector();
    generateOutputFiles(populatedOligos);
}

/* Creates input file with randomized oligo strings of given number and length
*/
void generateRandomInputFile() {
    ofstream randomInFile;
    randomInFile.open(parser->input, ios::out | ios::trunc);
    for (int i = 1; i < parser->numberOligos + 1; i++) {
        randomInFile << '>' << i << "\n" << randomOligo() << endl;
    }
    randomInFile.close();
}

/* Creates random oligo string
*/
string randomOligo() {
    string oligo = "";
    for (int i = 0; i < parser->lengthOligos; i++) {
        oligo += RANDOMBASE;
    }
    return oligo;
}
