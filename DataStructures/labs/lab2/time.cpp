#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "time.h"

Time::Time()
{
    hour = 0;
    min = 0;
    sec = 0;
};

Time::Time(int theHour, int theMin, int theSec)
{
    hour = theHour;
    min = theMin;
    sec = theSec;
};

int Time::getHour() const
{
    return hour;
};

int Time::getMinute() const
{
    return min;
};

int Time::getSecond() const
{
    return sec;
};

void Time::setHour(int hr)
{
    hour = hr;
};

void Time::setMinute(int mn)
{
    min = mn;
};

void Time::setSecond(int sc)
{
    sec = sc;
};

std::string Time::PrintAMPM()
{
    if (hour == 0)
    {
        std::cout << "12:" << getMinute() << ":" << getSecond() << " AM" << std::endl;
        return "AM";
    }
    else if (hour < 12)
    {
        std::cout << getHour() << ":" << getMinute() << ":" << getSecond() << " AM" << std::endl;
        return "AM";
    }
    else if (hour == 12)
    {
        std::cout << getHour() << ":" << getMinute() << ":" << getSecond() << " PM" << std::endl;
        return "PM";
    }
    else
    {
        std::cout << (getHour() - 12) << ":" << getMinute() << ":" << getSecond() << " PM" << std::endl;
        return "PM";
    }
};

bool IsEarlierThan(const Time &t1, const Time &t2)
{
    if (t1.getHour() < t2.getHour())
    {
        return true;
    }
    else if ((t1.getHour() == t2.getHour()) && t1.getMinute() < t2.getMinute())
    {
        return true;
    }
    else if (((t1.getHour() == t2.getHour()) && t1.getMinute() == t2.getMinute()) && t1.getSecond() < t2.getSecond())
    {
        return true;
    }
    else
    {
        return false;
    }
};
