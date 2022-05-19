#include <string>
#include <unordered_map>

using namespace std;

string encode(string str);
string decode(string binary);
string binaryToBase(string binary);
string baseToBinary(string str);

unordered_map<string, string> baseBinary = {
        {"A", "00"}, {"T", "01"}, {"G", "10"}, {"C", "11"}
    };

unordered_map<string, string> binaryBase = {
        {"00", "A"}, {"01", "T"}, {"10", "G"}, {"11", "C"}
    };
