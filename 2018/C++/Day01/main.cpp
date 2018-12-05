#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_set>

using namespace std;

constexpr int safe_add(int const lhs, int const rhs) {
    if ( (rhs > 0 && lhs > numeric_limits<int>::max() - rhs) || (rhs < 0 && lhs < numeric_limits<int>::min() - rhs) )
        throw overflow_error("Integer overflow when adding frequency deltas");
    return lhs + rhs;
}

int first(vector<int> deltas) {
    int sum = 0;

    for (auto i: deltas) {
        sum = safe_add(sum, i);
    }
    return sum;
}

int second(vector<int> deltas) {
    int sum = 0;
    bool inserted = false;
    unordered_set<int> frequencies;
    while(true) {
        for (auto i: deltas) {
            sum = safe_add(sum, i);
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
    try {
        cout << "first: " << first(deltas) << endl;
        cout << "second: " << second(deltas) << endl;
    } catch(exception& e) {
        cout << "Exception: " << e.what() << endl;
        exit(1);
    }

    return 0;
}
