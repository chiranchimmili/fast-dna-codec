#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include <fstream>
#include "../lib/json.hpp"

using namespace std;
using json = nlohmann::json;

class jsonParser {

private:
    json j;

public:
    string input;
    string unorderedOutput;
    string orderedOutput;
    double insertErrorRate;
    double deleteErrorRate;
    double substitutionErrorRate;
    int numberReads;
    int numberOligos;
    int lengthOligos;

    void parseJSONFile(string file);
    void insertError();
    void deleteError();
    void substitutionError();
    void numReads();
    void numOligos();
    void lenOligos();
    void inputFile();
    void unorderedOutputFile();
    void orderedOutputFile();
    void setParameters();
};

#endif

