#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

typedef map<char,set<char>> Prerequisites;

constexpr int num_workers = 5;
constexpr int additional_time = 60;

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

constexpr int get_completion_time(char instruction = 'Z')
{
    return additional_time + instruction - 'A' + 1;
}

string first(Prerequisites prereqs)
{
    string instruction_sequence;
    while (!prereqs.empty())
    {
        char instruction = get_first_available_instruction(prereqs);
        instruction_sequence += instruction;
        prereqs.erase(instruction);
        remove_done_instruction(prereqs, instruction);
    }
    return instruction_sequence;
}

int second(Prerequisites prereqs)
{

    int accumulated_time = 0;
    unordered_map<char,int> workers;

    int next_completion_time = get_completion_time('Z');
    char next_complete_instruction = '\0';
    while (!prereqs.empty())
    {
        while (workers.size() < num_workers)
        {
            char instruction;
            try
            {
                instruction = get_first_available_instruction(prereqs);
            }
            catch (runtime_error e)
            {
                break;
            }
            prereqs.erase(instruction);

            int completion_time = get_completion_time(instruction);
            workers[instruction] = completion_time;
            if (completion_time < next_completion_time)
            {
                next_completion_time = completion_time;
                next_complete_instruction = instruction;
            }
        }

        remove_done_instruction(prereqs, next_complete_instruction);
        int completion_time = next_completion_time;
        workers.erase(next_complete_instruction);
        accumulated_time += completion_time;

        next_completion_time = get_completion_time('Z');
        for (auto &w: workers)
        {
            w.second -= completion_time;
            if (w.second < next_completion_time)
            {
                next_completion_time = w.second;
                next_complete_instruction = w.first;
            }
        }
    }
    return accumulated_time;
}

int main()
{
    string str;
    ifstream infile("input.txt");

    Prerequisites prereqs = get_prereqs(infile);
    string first_solution = first(prereqs);
    int second_solution = second(prereqs);
    cout << "first: " << first_solution << endl;
    cout << "second: " << second_solution << endl;
    return 0;
}