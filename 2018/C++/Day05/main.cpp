#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_set>

using namespace std;

string react_polymer(string str)
{
    for (auto strit = str.begin(); strit < str.end();)
    {
        if (*strit == (*(strit + 1) - 32) ||
            *strit == (*(strit + 1) +32) )
        {
            str.erase(strit-str.begin(),2);
            strit--;
        }
        else
        {
            strit++;
        }
    }
    return str;
}

int first(string &polymer)
{
    string reacted_polymer = react_polymer(polymer);
    return reacted_polymer.length();
}

string clean_polymer(string polymer, char c)
{
    for (auto strit = polymer.begin(); strit < polymer.end();)
    {
        if (tolower(*strit) == c)
        {
            int pos = strit-polymer.begin();
            polymer.erase(pos,1);
        }
        else
        {
            strit++;
        }
    }
    return polymer;
}

int second(string &polymer)
{
    unordered_set<char> unique_units;
    int best_polymer_len = polymer.length();
    for (auto const &c: polymer)
    {
        unique_units.insert(tolower(c));
    }

    for (auto const &c: unique_units) {
        string cleaned_polymer = clean_polymer(polymer, c);
        string reacted_polymer = react_polymer(cleaned_polymer);
        if (reacted_polymer.length() < best_polymer_len)
        {
            best_polymer_len = reacted_polymer.length();
        }
    }
    return best_polymer_len;
}

int main() {
    string polymer;
    ifstream infile("input.txt");

    infile >> polymer;
    int first_res = first(polymer),
        second_res = second(polymer);

    cout << "first: " << first_res << endl;
    cout << "second: " << second_res << endl;

    return 0;
}