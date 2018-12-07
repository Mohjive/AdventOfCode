#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "fabric.h"

using namespace std;

int first(const vector<fabric::Claim>& claims) {
    unordered_map<fabric::Coordinate,int> fabric;
    int max_x = 0, max_y = 0;
    for (auto claim: claims) {
        for (int x = claim.coord.x; x < claim.coord.x + claim.size.width; x++) {
            max_x = max(x, max_x);
            for (int y = claim.coord.y; y < claim.coord.y + claim.size.height; y++) {
                max_y = max(y, max_y);
                fabric::Coordinate mark(x,y);
                auto found = fabric.find(mark);
                if (found != fabric.end()) {
                    found->second++;
                } else {
                    fabric.insert(make_pair(mark,1));
                }
            }
        }
        //cout << "claim: " << claim << endl;
    }
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < max_y; y++) {
            
        }
    }
    int multiclaim = 0;
    for (auto f: fabric) {
        if (f.second > 1) multiclaim++;
    }
    return multiclaim;
}

int main() {
    string str;
    vector<fabric::Claim> claims;
    ifstream infile("input.txt");
    fabric::Claim c;
    //format #1 @ 1,3: 4x4
    char s1, s2, s3, s4, s5;
    while (infile >> s1 >> c.id >> s2 >> c.coord.x >> s3 >> c.coord.y >> s4 >> c.size.width >> s5 >> c.size.height) {
        if (s1 != '#' && s2 != '@' && s3 != ',' && s4 != ':' && s5 != 'x')
            std::terminate();

        claims.push_back(c);
    }
    
    cout << "First: " << first(claims) << endl;
    return 0;
}
