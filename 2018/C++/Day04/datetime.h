#if !defined(__DATETIME_H__)
#define __DATETIME_H__

#include <string>
#include <iostream>


template <typename T>
struct reverse_wrapper {
    T& iterable;
};

template <typename T>
auto begin (reverse_wrapper<T> w)
{
    return std::rbegin(w.iterable);
}

template <typename T>
auto end (reverse_wrapper<T> w)
{
    return std::rend(w.iterable);
}

template <typename T>
reverse_wrapper<T> reverse(T&& i)
{
    return {i};
}

namespace datetime
{
    class Date {
    public:
        Date (int const y = 1970, int const m = 1, int const d = 1);
        Date (std::string const &str);

        friend std::istream &operator>> (std::istream &is, Date &d);
        friend std::ostream &operator<< (std::ostream &os, Date const &d);
        friend bool operator< (Date const &d1, Date const &d2);
        friend bool operator> (Date const &d1, Date const &d2);
        friend bool operator== (Date const &d1, Date const &d2);

        int year;
        int month;
        int day;
    private:
    };

    class Time {
    public:
        Time(int const h = 0, int const m = 0, int const s = 0);
        Time(std::string const &str);

        friend std::ostream &operator<< (std::ostream &os, Time const &t);
        friend std::istream &operator>> (std::istream &is, Time &t);
        friend bool operator< (Time const &t1, Time const &t2);
        friend bool operator> (Time const &t1, Time const &t2);

        int hour;
        int minute;
        int second;
    private:
    };

    class Timestamp {
    public:
        Timestamp();
        Timestamp(std::string const &str);
        Date getDate();
        void setDate(Date &d);
        Time getTime();
        void operator() (std::string const &str);

        friend std::ostream &operator<< (std::ostream &os, Timestamp const &ts);
        friend std::istream &operator>> (std::istream &is, Timestamp &ts);
        friend bool operator< (Timestamp const &ts1, Timestamp const &ts2);
        friend bool operator> (Timestamp const &ts1, Timestamp const &ts2);
        void _setTimestamp(std::string const &str);
        Date date;
        Time time;
    private:
    };
} // date

#endif // __DATETIME_H__
