#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

typedef map<char,set<char>> Prerequisites;

Prerequisites get_prereqs(ifstream &infile)
{
    char prereq, follow;
    Prerequisites prerequisites;
    string u;

    while (infile >> u >> prereq >> u >> u >> u >> u >> u >> follow >> u >> u)
    {
        if (!prerequisites.count(prereq)) prerequisites[prereq] = set<char>();
        prerequisites[follow].insert(prereq);
    }
    return prerequisites;
}

char get_first_available_instruction(Prerequisites prereqs)
{
    for (const auto & p : prereqs) {
        if (p.second.empty()) {
            return p.first;
        }
    }
    throw runtime_error("Unreachable instructions");
}

void remove_done_instruction(Prerequisites &prereqs, char instruction)
{
    for (auto &p : prereqs) {
        p.second.erase(instruction);
    }
}

string first(Prerequisites prereqs)
{
    string solution;
    while (!prereqs.empty())
    {
        char instruction = get_first_available_instruction(prereqs);
        solution += instruction;
        prereqs.erase(instruction);
        remove_done_instruction(prereqs, instruction);
    }
    return solution;
}

int main()
{
    string str;
    ifstream infile("input.txt");

    Prerequisites prereqs = get_prereqs(infile);
    string first_solution = first(prereqs);
    cout << "first: " << first_solution << endl;
    return 0;
}