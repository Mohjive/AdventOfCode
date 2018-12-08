#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "datetime.h"

using namespace std;


namespace datetime
{
    Date::Date(int const y, int const m, int const d): year(y), month(m), day(d) {};
    Date::Date(string const &str)
    {
        char s1, s2;
        stringstream ss(str);
        ss >> year >> s1 >> month >> s2 >> day;
    }

    ostream &operator<< (ostream &os, Date const &d)
    {
        return os << setw(4) << right << d.year << "-" << setfill('0') << setw(2) << d.month << "-" << setfill('0') << setw(2) << d.day;
    }

    istream &operator>> (istream &is, Date &d)
    {
        char s1, s2;
        int year, month, day;
        is >> year >> s1 >> month >> s2 >> day;
        if ( s1 == s2 &&
            (s1 == '-' || s1 == '/' || s1 == '\\' || s1 == '.') )
        {
            d.year = year;
            d.month = month;
            d.day = day;
        }
        else // rollback
        {
            string s;
            stringstream ss(s);
            ss << year << s1 << month << s2 << day;
            s = ss.str();
            for_each(s.rbegin(), s.rend(),
                [&is](auto const &c) { is.putback(c); });
        }

        return is;
    }

    bool operator== (Date const &d1, Date const &d2) {
        return (d1.year == d2.year &&
                d1.month == d2.month &&
                d1.day == d2.day);
    }
    bool operator< (Date const &d1, Date const &d2)
    {
        if (d1.year < d2.year) {
            // cout << d1.year << " < " << d2.year << endl;
            return true;
        }
        else if ( (d1.month < d2.month) &&
                  (d1.year == d2.year) )
        {
            // cout << d1.month << " < " << d2.month << endl;
            return true;
        }
        else if ( (d1.day < d2.day) &&
                  (d1.month == d2.month) &&
                  (d1.year == d2.year) )
        {
            // cout << d1.day << " < " << d2.day << endl;
            return true;
        }
        else
        {
            // cout << d1 << " >= " << d2 << endl;
            return false;
        }
    }

    bool operator>(Date const &d1, Date const &d2)
    {
        if (d1.year > d2.year) {
            return true;
        }
        else if ( (d1.month > d2.month) &&
                  (d1.year == d2.year) )
        {
            return true;
        }
        else if ( (d1.day > d2.day) &&
                  (d1.month == d2.month) &&
                  (d1.year == d2.year) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Time::Time(int const h, int const m, int const s): hour(h), minute(m), second(s) {};
    Time::Time(string const &str)
    {
        char s1, s2;
        stringstream ss(str);
        ss >> hour >> s1 >> minute >> s2 >> second;
    }

    std::ostream &operator<< (std::ostream &os, Time const &t)
    {
            return os << setfill('0') << setw(2) << t.hour << ":" << setfill('0') << setw(2) << t.minute << ":" << setfill('0') << setw(2) << t.second;
    }
    std::istream &operator>> (std::istream &is, Time &t)
    {
        char s1, s2;
        return is >> t.hour >> s1 >> t.minute >> s2 >> t.second;
    }

    bool operator<(Time const &t1, Time const &t2)
    {
        if (t1.hour < t2.hour) {
            return true;
        }
        else if ( (t1.minute < t2.minute) &&
                  (t1.hour == t2.hour) )
        {
            return true;
        }
        else if ( (t1.second < t2.second) &&
                  (t1.minute == t2.minute) &&
                  (t1.hour == t2.hour) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(Time const &t1, Time const &t2)
    {
        if (t1.hour > t2.hour) {
            return true;
        }
        else if ( (t1.minute > t2.minute) &&
                  (t1.hour == t2.hour) )
        {
            return true;
        }
        else if ( (t1.second > t2.second) &&
                  (t1.minute == t2.minute) &&
                  (t1.hour == t2.hour) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Timestamp::Timestamp() {};

    Timestamp::Timestamp(string const &str)
    {
        _setTimestamp(str);
    }

    void Timestamp::operator() (string const &str)
    {
        _setTimestamp(str);
    }

    Date Timestamp::getDate(void)
    {
        return Date(this->date);
    }

    void Timestamp::setDate(Date &d)
    {
        this->date = d;
    }

    Time Timestamp::getTime()
    {
        return Time(this->time);
    }

    void Timestamp::_setTimestamp(string const &str)
    {
        stringstream ss(str);
        ss >> date >> time;
    }

    std::ostream &operator<< (std::ostream &os, Timestamp const &ts)
    {
            return os << ts.date << " " << ts.time;
    }

    std::istream &operator>> (std::istream &is, Timestamp &ts)
    {
        return is >> ts.date >> ts.time;
    }

    bool operator<(Timestamp const &ts1, Timestamp const &ts2)
    {
        if (ts1.date < ts2.date) {
            // cout << ts1 << " < " << ts2 << " on date" << endl;
            return true;
        }
        else if ( (ts1.time < ts2.time) &&
                  (ts1.date == ts2.date) )
        {
            // cout << ts1 << " < " << ts2 << " on time" << endl;
            return true;
        }
        else
        {
            // cout << ts1 << " >= " << ts2 << endl;
            return false;
        }
    }

    bool operator>(Timestamp const &ts1, Timestamp const &ts2)
    {
        if (ts1.date > ts2.date) {
            return true;
        }
        else if (ts1.time > ts2.time)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
} // time
