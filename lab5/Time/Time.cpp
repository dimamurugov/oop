#include "Time.h"
#include <iostream>

constexpr unsigned SECONDS_PER_HOUR = 60 * 60;
constexpr unsigned SECONDS_PER_MINUTE = 60;
constexpr unsigned MAX_TIMESTAMP = 23 * SECONDS_PER_HOUR + 59 * SECONDS_PER_MINUTE + 60;

Time::Time(unsigned hours, unsigned minutes, unsigned seconds)
        : Time(hours * SECONDS_PER_HOUR + minutes * SECONDS_PER_MINUTE + seconds)
{
    if (Time::Validate(hours, minutes, seconds))
    {
        throw std::invalid_argument("Invalid input arguments");
    }
}

Time::Time(unsigned timestamp)
        : m_timestamp(timestamp)
{
    if (timestamp > MAX_TIMESTAMP || timestamp < 0)
    {
        throw std::invalid_argument("Invalid timestamp value");
    }
}

bool Time::Validate(unsigned hours, unsigned minutes, unsigned seconds)
{
    return hours > 23 || minutes > 59 || seconds > 59 || hours < 0 || minutes < 0 || seconds < 0;
}