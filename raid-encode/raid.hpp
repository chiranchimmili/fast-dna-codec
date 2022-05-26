#include <string>
#include <vector>
#include <iostream>
#include <cstddef>

using namespace std;

vector<vector<unsigned char>> encode(vector<unsigned char> bytes, int columns);
string decode(vector<vector<unsigned char>> encoded, int removed);
string rand_str (size_t length);
int rand_int(int max);
