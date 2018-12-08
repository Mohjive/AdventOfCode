#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

#include "fabric.h"

using namespace std;

pair<fabric::Fabric,unordered_set<int>> weave_fabric(const fabric::Claims& claims) {
    fabric::Fabric fabric;
    unordered_set<int> overlapped;
    for (auto claim: claims) {
        for (int x = claim.coord.x; x < claim.coord.x + claim.size.width; x++) {
            for (int y = claim.coord.y; y < claim.coord.y + claim.size.height; y++) {
                fabric::Coordinate mark(x,y);
                auto found = fabric.find(mark);
                if (found != fabric.end()) {
                    overlapped.insert(found->second.id);
                    overlapped.insert(claim.id);
                    found->second.count++;
                    found->second.id=0;
                } else {
                    fabric::Data d(claim.id, 1);
                    fabric.insert(make_pair(mark,d));
                }
            }
        }
    }
    return make_pair(fabric, overlapped);
}

int first(fabric::Fabric const &fabric) {
    int multiclaim = 0;
    for (auto f: fabric) {
        if (f.second.count > 1) multiclaim++;
    }
    return multiclaim;
}

int second( unordered_set<int> const &overlapped,  fabric::Claims const &claims) {
    for (auto claim: claims) {
        if (overlapped.find(claim.id) == overlapped.end())
            return claim.id;
    }
    return 0;
}

int main() {
    string str;
    fabric::Claims claims;
    ifstream infile("input.txt");
    fabric::Claim c;
    
    //format #1 @ 1,3: 4x4
    char s1, s2, s3, s4, s5;
    while (infile >> s1 >> c.id >> s2 >> c.coord.x >> s3 >> c.coord.y >> s4 >> c.size.width >> s5 >> c.size.height) {
        if (s1 != '#' && s2 != '@' && s3 != ',' && s4 != ':' && s5 != 'x')
            std::terminate();
        claims.push_back(c);
    }
    auto [fabric,overlapped] = weave_fabric(claims);
    cout << "First: " << first(fabric) << endl;
    cout << "Second: " << second(overlapped, claims) << endl;
    return 0;
}
