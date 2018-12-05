#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_set>

using namespace std;

int first(vector<int> deltas) {
    int sum = 0;

    for (auto i: deltas) {
        sum += i;
    }
    return sum;
}

int second(vector<int> deltas) {
    int sum = 0;
    bool inserted = false;
    unordered_set<int> frequencies;
    while(true) {
        for (auto i: deltas) {
            sum += i;
            tie(std::ignore, inserted) = frequencies.insert(sum);
            if (!inserted) return sum;
        }
    }
}

int main() {
    int i;
    vector<int> deltas;
    ifstream infile("input.txt");
    while (infile >> i) {
        deltas.push_back(i);
    }
    cout << "first: " << first(deltas) << endl;
    cout << "second: " << second(deltas) << endl;

    return 0;
}
