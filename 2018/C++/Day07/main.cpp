#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Instruction
{
    unordered_map<char,Instruction> next_instruction;
};

int main()
{
    string str;
    ifstream infile("input.txt");
    string u;
    char prereq, follow;
    unordered_set<char> done_instructions;
    unordered_map<char,int> instructions_following_prereq;
    set<char> next_instruction_candidates;
    unordered_map<char,set<char>> prerequisites;

    while (infile >> u >> prereq >> u >> u >> u >> u >> u >> follow >> u >> u)
    {
        // cout << "pre: " << prereq << " next_instruction_candidates: " << follow << endl;
        auto found_follower = instructions_following_prereq.find(follow);
        if (found_follower == instructions_following_prereq.end())
        {
            instructions_following_prereq.insert(make_pair(follow,1));
        }
        else
        {
            found_follower->second++;
        }
        auto prereq_follower = instructions_following_prereq.find(prereq);
        if (prereq_follower == instructions_following_prereq.end())
        {
            next_instruction_candidates.insert(prereq);
        }
        auto follower_in_next = next_instruction_candidates.find(follow);
        if (follower_in_next != next_instruction_candidates.end())
        {
            next_instruction_candidates.erase(follower_in_next);
        }
        auto found = prerequisites.find(prereq);
        if (found == prerequisites.end())
        {
            set<char> fs;
            fs.insert(follow);
            prerequisites.insert(make_pair(prereq,fs));
        }
        else
        {
            found->second.insert(follow);
        }
        // prerequisites.insert(make_pair(prereq,))
    }
    /* for (auto const &p: found_prereq)
    {
        cout << "p: " << p << endl;
    }
    for (auto const &f: instructions_following_prereq)
    {
        cout << "f: " << f.first << ":" << f.second << endl;
    }
    for (auto const &i: prerequisites)
    {
        cout << "i: " << i.first;
        for (auto const &f: i.second)
        {
            cout << "->" << f;
        }
        cout << endl;
    } */
    string solution;
    while (next_instruction_candidates.size() > 0)
    {
        char current_instruction = *(next_instruction_candidates.begin());

        solution += current_instruction;
        // cout << "c: " << current_instruction << endl;
        done_instructions.insert(current_instruction);
        next_instruction_candidates.erase(current_instruction);

        auto found_instruction = prerequisites.find(current_instruction);
        if (found_instruction != prerequisites.end())
        {
            for (auto const &candidate_instruction: found_instruction->second)
            {
                auto const &done = done_instructions.find(candidate_instruction);
                if (done == done_instructions.end())
                {
                    auto const &follower = instructions_following_prereq.find(candidate_instruction);
                    if (follower != instructions_following_prereq.end())
                    {
                        follower->second--;
                        if (follower->second == 0)
                        {
                            // cout << "r: " << follower->first;
                            instructions_following_prereq.erase(follower->first);
                            next_instruction_candidates.insert(candidate_instruction);
                        }
                    }
                    else
                    {
                        next_instruction_candidates.insert(candidate_instruction);
                    }
                }
            }
        }
        else
        {
            cout << "No more prerequisites" << endl;
        }
/*         cout << "n: ";
        for (auto const &nic: next_instruction_candidates)
        {
            cout << nic << ",";
        }
        cout << endl; */
    }
    cout << solution << endl;
    return 0;
}