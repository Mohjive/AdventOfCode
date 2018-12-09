#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Instructions
{
    unordered_set<char> done;
    unordered_map<char,int> following_prereq;
    set<char> next_candidates;
    unordered_map<char,set<char>> prerequisites;
};

Instructions get_instructions(ifstream &infile)
{
    char prereq, follow;
    Instructions instructions;
    string u;

    while (infile >> u >> prereq >> u >> u >> u >> u >> u >> follow >> u >> u)
    {
        auto found_follower = instructions.following_prereq.find(follow);
        if (found_follower == instructions.following_prereq.end())
        {
            instructions.following_prereq.insert(make_pair(follow,1));
        }
        else
        {
            found_follower->second++;
        }

        auto follower_in_next = instructions.next_candidates.find(follow);
        if (follower_in_next != instructions.next_candidates.end())
        {
            instructions.next_candidates.erase(follower_in_next);
        }

        auto prereq_follower = instructions.following_prereq.find(prereq);
        if (prereq_follower == instructions.following_prereq.end())
        {
            instructions.next_candidates.insert(prereq);
        }

        auto found = instructions.prerequisites.find(prereq);
        if (found == instructions.prerequisites.end())
        {
            set<char> fs;
            fs.insert(follow);
            instructions.prerequisites.insert(make_pair(prereq,fs));
        }
        else
        {
            found->second.insert(follow);
        }
    }
    return instructions;
}

string first(Instructions instructions)
{
    string solution;
    while (instructions.next_candidates.size() > 0)
    {
        char current_instruction = *(instructions.next_candidates.begin());

        solution += current_instruction;
        instructions.done.insert(current_instruction);
        instructions.next_candidates.erase(current_instruction);

        auto found_instruction = instructions.prerequisites.find(current_instruction);
        if (found_instruction != instructions.prerequisites.end())
        {
            for (auto const &candidate_instruction: found_instruction->second)
            {
                auto const &done = instructions.done.find(candidate_instruction);
                if (done == instructions.done.end())
                {
                    auto const &follower = instructions.following_prereq.find(candidate_instruction);
                    if (follower != instructions.following_prereq.end())
                    {
                        follower->second--;
                        if (follower->second == 0)
                        {
                            instructions.following_prereq.erase(follower->first);
                            instructions.next_candidates.insert(candidate_instruction);
                        }
                    }
                    else
                    {
                        instructions.next_candidates.insert(candidate_instruction);
                    }
                }
            }
        }
        else
        {
            // cout << "No more prerequisites" << endl;
        }
    }
    return solution;
}

int main()
{
    string str;
    ifstream infile("input.txt");

    Instructions instructions = get_instructions(infile);

    string first_solution = first(instructions);
    cout << "first: " << first_solution << endl;
    return 0;
}