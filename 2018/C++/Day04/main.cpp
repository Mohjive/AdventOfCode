#include <string>
#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "datetime.h"

using namespace std;
namespace dt = datetime;

typedef map<datetime::Timestamp,string> ActionList;

struct SleepInfo
{
    int asleep_for;
    unordered_map<int,int> minutemap;
};

struct GuardSleepInfo
{
    int guard_id;
    struct SleepInfo sleep_data;
};

typedef unordered_map<int,SleepInfo> SleepData;

void update_sleepdata(SleepData *sleepdata, int guard_id, int falls_asleep, int wakes)
{
    int asleep = wakes-falls_asleep;
    auto sd = sleepdata->find(guard_id);
    if (sd == sleepdata->end())
    {
        SleepInfo si;
        si.asleep_for = asleep;
        for (int i = falls_asleep; i < wakes; i++)
        {
            si.minutemap.insert(make_pair(i,1));
        }
        sleepdata->insert(make_pair(guard_id,si));
    }
    else
    {
        SleepInfo *si = &sd->second;
        for (int i = falls_asleep; i < wakes; i++) {
            auto minute = si->minutemap.find(i);
            if (minute == si->minutemap.end())
            {
                si->minutemap.insert(make_pair(i,1));
            }
            else
            {
                minute->second++;
            }
        }
        si->asleep_for += wakes - falls_asleep;
    }
}

SleepData calculate_sleeptimes(ActionList const &actions)
{
    SleepData sleepdata;
    int guard_id = 0, falls_asleep = 0;

    for (auto const &action: actions) {
        string str;
        stringstream ss(action.second);

        ss >> str;
        if (str == "Guard")
        {
            ss >> str;
            str.erase(0,1);
            guard_id = atoi(str.c_str());
        }
        else if (str == "falls")
        {
            falls_asleep = action.first.time.minute;
        }
        else if (str == "wakes")
        {
            int wakes = action.first.time.minute;
            update_sleepdata(&sleepdata, guard_id, falls_asleep, wakes);
        }
        else
        {
            SleepData esd;
            return esd;
        }
    }
    return sleepdata;
}

int first(SleepData const &sleepdata)
{
    auto guard_it= max_element(sleepdata.begin(), sleepdata.end(),
            [](auto const &lhs, auto const &rhs){ return lhs.second.asleep_for < rhs.second.asleep_for; });

    int guard_id = guard_it->first;

    auto mIt = max_element(sleepdata.at(guard_id).minutemap.begin(), sleepdata.at(guard_id).minutemap.end(),
                            [](auto const &lhs, auto const &rhs) { return lhs.second < rhs.second; });
    int selected_minute = mIt->first;

    return guard_id * selected_minute;
}

int main() {
    string str;
    ifstream infile("input.txt");
    ActionList actions;
    set<datetime::Timestamp> timestamps;


    /* Format:
    [1518-11-01 00:00] Guard #10 begins shift
    [1518-11-01 00:05] falls asleep
    [1518-11-01 00:25] wakes up
    */
    while (getline(infile, str)) {
        auto pos = str.find_first_of(']');
        string datestr = str.substr(1,pos);
        datetime::Timestamp ts(datestr);
        str.erase(0,pos+1);
        actions.insert(make_pair(ts, str));
    }
    SleepData sleepdata = calculate_sleeptimes(actions);
    cout << "first: " << first(sleepdata) << endl;

    return 0;
}