#include <map>
#include <string>

using namespace std;

/*
Insertion = 0 with 1% error occurence
Deletion = 1
Substitution = 2
No error = 3
*/
map<int, float> errorWeights = {
    {0, 0.01}, {1, 0.02}, {2, 0.02}, {3, 0.95}
};


char bases[4] = {'A', 'T', 'C', 'G'};

int generateIdsType();

char randomBase();

string performIds(string str);