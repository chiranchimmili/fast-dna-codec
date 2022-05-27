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
    jsonParser::numberReads = j["simulation"]["oligos"]["numReads"];
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
void jsonParser::numOligos() {
    jsonParser::numberOligos = j["simulation"]["oligos"]["numOligos"];
}
void jsonParser::lenOligos() {
    jsonParser::lengthOligos = j["simulation"]["oligos"]["oligoLength"];
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
}
