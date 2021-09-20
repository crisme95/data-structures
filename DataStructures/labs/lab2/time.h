#include <string>
#include <vector>

class Time
{
public:
    Time();
    Time(int theHour, int theMin, int theSec);

    // Accessors
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Modifiers
    void setHour(int theHour);
    void setMinute(int theMin);
    void setSecond(int theSec);
    std::string PrintAMPM();

private:
    int hour;
    int min;
    int sec;
};

bool IsEarlierThan(const Time &t1, const Time &t2);