#include <map>
#include <string>
#include "../include/jsonParser.hpp"
#pragma once
using namespace std;



random_device rand_dev;
mt19937 generator(rand_dev());
uniform_int_distribution<int> randomIds(1, 100);

/* Macro that returns a random base from bases array */
#define RANDOMBASE (bases[rand() % 4]);

/*
Insertion = 0, with default error occurence of 0%
Deletion = 1
Substitution = 2
No error = 3
*/

char bases[4] = {'A', 'T', 'C', 'G'};

int generateIdsType();
char randomBase();
vector<string> generateOligosVector(ifstream &inFile);
void generateOutputFiles(ofstream &unorderedOutFile, ofstream &orderedOutFile, vector<string> oligos);
string performIds(string str);