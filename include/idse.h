#include <map>
#include <string>
#include "../include/jsonParser.hpp"
#pragma once
using namespace std;

/*
Macro that returns a random base from bases array
*/
#define RANDOMBASE (bases[rand() % 4]);
/*
Insertion = 0, with default error occurence of 1%
Deletion = 1
Substitution = 2
No error = 3
*/
map<int, float> errorWeights = {
    {0, 0.00}, {1, 0.00}, {2, 0.00}, {3, 0.00}
};

char bases[4] = {'A', 'T', 'C', 'G'};

int generateIdsType();
char randomBase();
vector<string> generateOligosVector(ifstream &inFile);
void generateOutputFile(ofstream &outFile, vector<string> oligos);
string performIds(string str);