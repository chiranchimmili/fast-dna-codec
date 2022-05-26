#include "../include/json.hpp"
#include "../include/jsonParser.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

void jsonParser::parseFile(string file) {
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
    jsonParser::numberReads = j["simulation"]["numReads"];
}
void jsonParser::inputFile() {
    jsonParser::input = j["simulation"]["files"]["input"];
}
void jsonParser::unorderedOutputFile() {
    jsonParser::unorderedOutput = j["simulation"]["files"]["unorderedOutput"];
}
void jsonParser::orderedOutputFile() {
    jsonParser::orderedOutput = j["simulation"]["files"]["orderedOutput"];
}
void jsonParser::setParameters() {
    insertError();
    deleteError();
    substitutionError();
    numReads();
    inputFile();
    unorderedOutputFile();
    orderedOutputFile();
}
