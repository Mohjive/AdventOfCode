#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_set>

using namespace std;

int first(ifstream& infile) {
    int i, sum = 0;
    infile.clear();
    infile.seekg(0, ios::beg);
    while (infile >> i) {
        sum += i;
    }
    return sum;
}

int second(ifstream& infile) {
    int i, sum = 0;
    bool inserted = false;
    unordered_set<int> freq;
    while(true) {
        infile.clear();
        infile.seekg(0);
        while (infile >> i) {
            sum += i;
            tie(std::ignore, inserted) = freq.insert(sum);
            if (!inserted) return sum;
        }
    }
}

int main() {
    ifstream infile("input.txt");
    cout << "first: " << first(infile) << endl;
    cout << "second: " << second(infile) << endl;

    return 0;
}