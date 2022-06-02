#include "../include/idse.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "jsonParser.cpp"

using namespace std;

jsonParser *parser = new jsonParser();
vector<string> oligos;

/*  Creates vector of oligo number and respective oligo string from given input fafsta file
    Note: Input file should have oligos in increasing order
*/
vector<string> generateOligosVector() {
    ifstream inFile;
    // Opens input FASTA file
    inFile.open(parser->inputFileName);
    string line;
    // Scans each line and creates vector of oligos
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

/* Generates insertion, deletion, substitution, or no error depending on percent weights of each specified
   by the user (in json)
*/
int generateIdsType() {
    double rnd = (double)randomIdsDist(generator) / 100.0;
    // Map of indelsub error percentenages
    map<int, float> errorWeights = {{0, parser->insertErrorRate}, {1, parser->deleteErrorRate}, {2, parser->substitutionErrorRate}, {3, 1 - parser->insertErrorRate - parser->deleteErrorRate - parser->substitutionErrorRate}};
    // Insert error
    if (rnd <= errorWeights[0]) {
        return 0;
    }
    // Delete error
    else if (rnd > errorWeights[0] && rnd <= errorWeights[0] + errorWeights[1]) {
        return 1;
    }
    // Substitution Error
    else if (rnd > errorWeights[0] + errorWeights[1] && rnd <= errorWeights[0] + errorWeights[1] + errorWeights[2]) {
        return 2;
    }
    // No Error
    return 3;
}

/* Performs insertion, deletion, and substitution on an oligo string (applied to each base)
 */
string performIds(string str) {
    // Error applied to each base in oligo
    string newStr = "";
    for (int i = 0; i < str.size(); i++) {
        int randIds = generateIdsType();
        char randBas = RANDOMBASE;
        newStr += performError(str.substr(i, 1), 0, randIds, randBas);
    }
    return newStr;
}

string performError(string str, int pos, int errorType, char base) {
    // Insert error applied
    if (errorType == 0) {
        str.insert(pos, 1, base);
        // Delete error applied
    } else if (errorType == 1) {
        str.erase(pos, 1);
        // Substitution error applied
    } else if (errorType == 2) {
        if (pos == -1) {
            return str + base;
        }
        // Make sure substitution is not same base as old one
        while (base == str[pos]) {
            base = RANDOMBASE;
        }
        str[pos] = base;
    }
    return str;
}

/* Creates orderedMap and unordered output files of oligo number and respective oligo string
 */
void generateOrderedOutputFile(vector<string> oligos) {
    // Open unordered and orderedMap files
    ofstream orderedOutFile;
    orderedOutFile.open(parser->orderedOutput, ios::out | ios::trunc);
    unordered_map<int, string> orderedMap;
    uniform_int_distribution<int> randomOligo(0, parser->numberOligos - 1);
    // Loop number of reads # of times
    for (int i = 0; i < parser->numberReads; i++) {
        // Randomly select oligo from oligos vector (akin to a sequencer selecing a random oligo in a DNA pool)
        int oligoNumber = randomOligo(generator);
        // Get string with indelsub errors
        if (orderedMap.find(oligoNumber) == orderedMap.end()) {
            string errorStr = performIds(oligos[oligoNumber]);
            orderedMap[oligoNumber] = errorStr;
        }
    }
    // Sort unordered oligo vector
    std::vector<std::pair<int, string>> elems(orderedMap.begin(), orderedMap.end());
    std::sort(elems.begin(), elems.end());
    // Add each sorted oligo to orderedMap output file
    for (const auto &[key, value] : elems) {
        orderedOutFile << ">" << key + 1 << "\n"
                       << value << endl;
    }
    orderedOutFile.close();
}

void generateUnorderedOutputFile(vector<string> oligos) {
    uniform_int_distribution<int> randomOligo(0, parser->numberOligos - 1);
    for (int i = 1; i < parser->numberSamples + 1; i++) {
        ofstream unorderedOutFile;
        unorderedOutFile.open((parser->unorderedOutput).substr(0, (parser->unorderedOutput).size() - 7) + to_string(i) + ".fafsta", ios::out | ios::trunc);
        for (int i = 0; i < parser->numberReads; i++) {
            // Randomly select oligo from oligos vector (akin to a sequencer selecing a random oligo in a DNA pool)
            int oligoNumber = randomOligo(generator);
            // Get string with indelsub errors
            string errorStr = performIds(oligos[oligoNumber]);
            // Add random oligo to unordered output file
            unorderedOutFile << ">" << (oligoNumber + 1) << "\n"
                             << errorStr << endl;
        }
        unorderedOutFile.close();
    }
}
