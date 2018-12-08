#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int first(string &str)
{
    for (auto strit = str.begin(); strit < str.end();)
    {
        cout << *strit;
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
    return str.length();
}

int main() {
    string str;
    ifstream infile("input.txt");

    infile >> str;
    int first_res = first(str);
    cout << "first: " << first_res << endl;

    return 0;
}