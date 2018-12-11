#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef list<int> MarbleCircle;

const int num_players = 458;
const int marble_value = 71307;

void print_round(MarbleCircle marble_circle, MarbleCircle::iterator current_marble, int current_player)
{
    cout << "[" << current_player +1 << "]";
    for (MarbleCircle::iterator mit = marble_circle.begin(); mit != marble_circle.end(); mit++)
    {
        stringstream ss;
        if (mit == current_marble)
        {
            ss << setw(3) << "(" << *mit << ")";
        }
        else
        {
            ss << setw(4) << *mit;
        }
        cout << setw(5) << left << ss.str();
    }
    cout << endl;
}

MarbleCircle::iterator move_position(MarbleCircle &marble_circle, MarbleCircle::iterator &current_position, int steps)
{
    if (steps > 0)
    {
        while (steps > 0)
        {
            if (current_position == marble_circle.end())
            {
                current_position = marble_circle.begin();
            }
            current_position++;
            steps--;
        }
    }
    else
    {
        while (steps < 0)
        {
            if (current_position == marble_circle.begin())
            {
                current_position = marble_circle.end();
            }
            current_position--;
            steps++;
        }
    }
    return current_position;
}

uint64_t play_marble(int const num_players, int const marble_value)
{
    MarbleCircle marble_circle;
    vector<uint64_t> players(num_players,0);
    marble_circle.push_back(0);
    auto current_marble = marble_circle.begin();
    int current_player = 0;

    for (int current_value = 1; current_value <= marble_value; current_value++, current_player = (current_player+1)%num_players)
    {
        if (current_value % 23 == 0)
        {
            players[current_player] += current_value;
            current_marble = move_position(marble_circle, current_marble, -7);
            players[current_player] += *current_marble;
            current_marble = marble_circle.erase(current_marble);
        }
        else
        {
            current_marble = move_position(marble_circle, current_marble, 2);
            current_marble = marble_circle.insert(current_marble, current_value);
        }
        // print_round(marble_circle, current_marble, current_player);
    }
    uint64_t highscore = 0;
    for ( auto const &p: players) {
        if (p > highscore)
        {
            highscore = p;
        }
    }
    return highscore;
}

int main()
{

/*
    cout << "10 players; last marble is worth 1618 points: high score is 8317 (" << play_marble(9, 25) << ")" << endl;
    cout << "10 players; last marble is worth 1618 points: high score is 8317 (" << play_marble(10,1618) << ")" << endl;
    cout << "13 players; last marble is worth 7999 points: high score is 146373 (" << play_marble(13,7999) << ")" << endl;
    cout << "17 players; last marble is worth 1104 points: high score is 2764 (" << play_marble(17,1104) << ")" << endl;
    cout << "21 players; last marble is worth 6111 points: high score is 54718 (" << play_marble(21,6111) << ")" << endl;
    cout << "30 players; last marble is worth 5807 points: high score is 37305 (" << play_marble(30,5807) << ")" << endl;
 */
    auto first_answer = play_marble(num_players, marble_value);
    cout << "first: " << first_answer << endl;
    auto second_answer = play_marble(num_players, marble_value*100);
    cout << "second: " << second_answer << endl;
    return 0;
}
