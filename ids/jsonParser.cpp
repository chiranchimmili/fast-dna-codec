#include "../lib/json.hpp"
#include "../include/jsonParser.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

void jsonParser::parseJSONFile(string file) {
    ifstream jsonFile(file);
    j = json::parse(jsonFile);
    setParameters();
}
void jsonParser::insertError() {
    jsonParser::insertErrorRate = (double)j["simulation"]["error"]["insert"];
}
void jsonParser::deleteError() {
    jsonParser::deleteErrorRate = (double)j["simulation"]["error"]["delete"];
}
void jsonParser::substitutionError() {
    jsonParser::substitutionErrorRate = (double)j["simulation"]["error"]["substitution"];
}
void jsonParser::numReads() {
    jsonParser::numberReads = (int)j["simulation"]["oligos"]["numReads"];
}
void jsonParser::numOligos() {
    jsonParser::numberOligos = (int)j["simulation"]["oligos"]["numOligos"];
}
void jsonParser::lenOligos() {
    jsonParser::lengthOligos = (int)j["simulation"]["oligos"]["oligoLength"];
}
void jsonParser::inputFile() {
    jsonParser::inputFileName = j["simulation"]["input"]["inputFileName"];
}
void jsonParser::randInput() {
    jsonParser::randomInput = j["simulation"]["input"]["randomInput"];
}
void jsonParser::unorderedOutputFile() {
    jsonParser::unorderedOutput = j["simulation"]["output"]["unorderedOutputFileName"];
}
void jsonParser::orderedOutputFile() {
    jsonParser::orderedOutput = j["simulation"]["output"]["orderedOutputFileName"];
}
void jsonParser::numSamples() {
    jsonParser::numberSamples = (int)j["simulation"]["output"]["numSamples"];
}
void jsonParser::setParameters() {
    insertError();
    deleteError();
    substitutionError();
    numReads();
    numOligos();
    lenOligos();
    inputFile();
    unorderedOutputFile();
    orderedOutputFile();
    randInput();
    numSamples();
}
