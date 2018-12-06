#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<bool,bool> count_characters(string const str) {
    int twoes = 0, threes = 0;
    char chars[26] = {0};
    for(unsigned char c: str) {
        switch (++chars[c - 'a']) {
        case 2:
            twoes++;
            break;
        case 3:
            twoes--;
            threes++;
            break;
        case 4:
            threes--;
            break;
        }
    }
    return make_pair((twoes > 0), (threes > 0));
}

int first(vector<string> idstrings) {
    int twoes = 0, threes = 0;
    for (auto idstring: idstrings) {
        auto [two, three] = count_characters(idstring);
        if (two)
            twoes++;
        if (three)
            threes++;
    }
    return twoes*threes;
}

int second(vector<string> idstrings) {
    int pos = 0;

	for (vector<string>::iterator i = idstrings.begin(); i != idstrings.end(); ++i) {		
		for (vector<string>::iterator j = i; j != idstrings.end(); ++j) {
            auto ita = (*i).begin();
            auto itb = (*j).begin();
            for(; ita != (*i).end() || itb != (*j).end(); ++ita, ++itb) {
                if (*ita != *itb) cout << *ita << " != " << *itb << endl;
            }
			
		}
	}
	
	return 0;
}

int main() {
    string str;
    vector<string> idstrings = {"abcd", "abcf", "aacf"};
    /*ifstream infile("input.txt");
    while (getline(infile, str)) {
        idstrings.push_back(str);
    }*/
    
    //cout << "First: " << first(idstrings) << endl;
    second(idstrings);
    return 0;
}