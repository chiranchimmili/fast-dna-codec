#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "../include/idse.hpp"
#include "jsonParser.cpp"

using namespace std;

jsonParser *parser = new jsonParser();
vector<string> oligos;

/* Creates vector of oligo number and respective oligo string from given input fafsta file
*/
vector<string> generateOligosVector() {
    ifstream inFile;
    // Opens input FAFSTA file
    inFile.open(parser->input);         
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
    double rnd = (double) randomIdsDist(generator) / 100.0;
    // Map of indelsub error percentenages
    map<int, float> errorWeights = {
    {0, parser->insertErrorRate}, {1, parser->deleteErrorRate}, {2, parser->substitutionErrorRate}, 
    {3, 1 - parser->insertErrorRate - parser->deleteErrorRate - parser->substitutionErrorRate}
    };
    // Insert error
    if (rnd <= errorWeights[0]) {     
        return 0;
    }
    // Delete error
    else if (rnd > errorWeights[0] && rnd <= errorWeights[0] + errorWeights[1] ) {   
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
    for (int i = 0; i < str.size(); i++) {
        int randIds = generateIdsType();
        char randBas = RANDOMBASE;
        // Insert error applied
        if (randIds == 0) {
            str.insert(i, 1 , randBas);
            i++;
        // Delete error applied
        } else if (randIds == 1) {
            str.erase(i, 1);
            i--;
        // Substitution error applied
        } else if (randIds == 2) {
            // Make sure substitution is not same base as old one
            while (randBas == str[i]) {
                randBas = RANDOMBASE;
            }
            str[i] = randBas;
        // No error applied
        } else {
            continue;
        }
    }
    return str;
}

/* Creates ordered and unordered output files of oligo number and respective oligo string
*/
void generateOutputFiles(vector<string> oligos) {
    // Open unordered and ordered files
    ofstream unorderedOutFile;
    ofstream orderedOutFile;
    unorderedOutFile.open(parser->unorderedOutput, ios::out | ios::trunc);
    orderedOutFile.open(parser->orderedOutput, ios::out | ios::trunc);
    vector<pair<int, string>> ordered;
    uniform_int_distribution<int> randomOligo(0, parser->numberOligos - 1);

    // Loop number of reads # of times
    for (int i = 0; i < parser->numberReads; i++) {
        // Randomly select oligo from oligos vector (akin to a sequencer selecing a random oligo in a DNA pool)
        int oligoNumber = randomOligo(generator);
        // Get strin with indelsub errors
        string errorStr = performIds(oligos[oligoNumber]);
        // Maintain vector of oligos so we can create ordered output file
        ordered.emplace_back(oligoNumber + 1, errorStr);
        // Add random oligo to unordered output file
        unorderedOutFile << ">" << (oligoNumber + 1) << "\n" << errorStr << endl;
    }
    // Sort unordered oligo vector
    sort(ordered.begin(), ordered.end());
    // Add each sorted oligo to ordered output file
    for (int i = 0; i < ordered.size(); i++) {
        orderedOutFile << ">" << ordered[i].first << "\n" << ordered[i].second << endl;
    }
    unorderedOutFile.close();
    orderedOutFile.close();
}
