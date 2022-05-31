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
    string inputFileName;
    string unorderedOutput;
    string orderedOutput;
    double insertErrorRate;
    double deleteErrorRate;
    double substitutionErrorRate;
    int numberReads;
    int numberOligos;
    int lengthOligos;
    
    bool randomInput;
    int numberSamples;

    void parseJSONFile(string file);
    void insertError();
    void deleteError();
    void substitutionError();
    void numReads();
    void numOligos();
    void lenOligos();
    void inputFile();
    void randInput();
    void numSamples();
    void unorderedOutputFile();
    void orderedOutputFile();
    void setParameters();
};

#endif

