#include "Time.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    std::vector<std::string> ParseStream(std::string const& input)
    {
        std::vector<std::string> result;
        size_t position = 0;
        size_t separatorPosition = input.find(':', position);
        if (separatorPosition == std::string::npos)
        {
            result.push_back(input);
            return result;
        }

        while (position < input.length())
        {
            separatorPosition = input.find(':', position);
            if (separatorPosition == std::string::npos)
            {
                result.push_back(input.substr(position));
                break;
            }
            result.push_back(input.substr(position, separatorPosition - position));
            position = separatorPosition + 1;
        }
        return result;
    }
}

unsigned SECONDS_PER_HOUR = 3600;
unsigned SECONDS_PER_MINUTE = 60;
unsigned MAX_TIMESTAMP = 23 * SECONDS_PER_HOUR + 59 * SECONDS_PER_MINUTE + 60;

Time::Time(unsigned hours, unsigned minutes, unsigned seconds)
        : Time(hours * SECONDS_PER_HOUR + minutes * SECONDS_PER_MINUTE + seconds)
{
    if (Time::Validate(hours, minutes, seconds))
    {
        throw std::invalid_argument("Invalid input arguments"); // Определяет тип объекта, который будет выброшен как исключение. Он сообщает об ошибках, возникающих из-за того, что значение аргумента не было принято.
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

unsigned Time::GetHours() const
{
    return m_timestamp / SECONDS_PER_HOUR;
}

unsigned Time::GetMinutes() const
{
    return (m_timestamp - GetHoursTimestamp()) / SECONDS_PER_MINUTE;
}

unsigned Time::GetSeconds() const
{
    return m_timestamp - GetHoursTimestamp() - GetMinutesTimestamp();
}

unsigned Time::GetHoursTimestamp() const
{
    return GetHours() * SECONDS_PER_HOUR;
}

unsigned Time::GetMinutesTimestamp() const
{
    return GetMinutes() * SECONDS_PER_MINUTE;
}

bool Time::Validate(unsigned hours, unsigned minutes, unsigned seconds)
{
    return hours > 23 || minutes > 59 || seconds > 59 || hours < 0 || minutes < 0 || seconds < 0;
}

Time& Time::operator++() // todo: Time& - ссылка на инстанс объект, что бы сделать инкремент
{
    auto t = CalculateTimestampForAdd(*this, 1); // this - указатель, *this - сам объект
    this->m_timestamp = t.m_timestamp;
    return *this;
}

Time Time::operator++(int)
{
    const Time old = *this;
    operator++();
    return old;
}

Time& Time::operator--()
{
    auto t = CalculateTimestampForSub(*this, 1);
    this->m_timestamp = t.m_timestamp;
    return *this; // todo: а зачем вовзращать - возвращаю ссылку на измененный объёект
}

Time Time::operator--(int)
{
    const Time old = *this; // мы сохранили ссылку или указатель
    operator--(); // todo: уже мутировали обект
    return old;
}

Time operator+(Time left, Time right)
{
    return Time::CalculateTimestampForAdd(left, right.m_timestamp);
}

Time operator-(Time left, Time right)
{
    return Time::CalculateTimestampForSub(left, right.m_timestamp);
}

Time operator*(Time time, int mul)
{
    return Time::CalculateTimestampForMul(time, mul);
}

Time operator*(int i, Time time)
{
    return time * i;
}

Time operator/(Time time, int div)
{
    if (div == 0)
    {
        throw std::invalid_argument("devision by zero"); // todo: invalid_argument можно не в конструкторе?...
    }
    auto h = time.GetHours() / div;
    auto m = time.GetMinutes() / div;
    auto s = time.GetSeconds() / div;
    time.m_timestamp = h * SECONDS_PER_HOUR + m * SECONDS_PER_MINUTE + s;
    return time;
}

Time Time::operator+=(Time right)
{
    // вызывается оператор + текущего объекта и следующего
    this->m_timestamp = operator+(*this, right).m_timestamp;
    return *this;
}

Time Time::operator-=(Time right)
{
    this->m_timestamp = operator-(*this, right).m_timestamp;
    return *this;
}

Time Time::operator*=(int mul)
{
    this->m_timestamp = operator*(*this, mul).m_timestamp;
    return *this;
}

Time Time::operator/=(int div)
{
    this->m_timestamp = operator/(*this, div).m_timestamp;
    return *this;
}

unsigned operator/(Time time, Time div)
{
    if (div.m_timestamp == 0)
    {
        throw std::invalid_argument("devision by zero");
    }

    return time.m_timestamp / div.m_timestamp;
}

bool Time::operator==(const Time& right) const
{
    return m_timestamp == right.m_timestamp; // todo: как я имею доступ к приватной константе?
}

bool Time::operator<(const Time& right) const
{
    return m_timestamp < right.m_timestamp;
}

bool Time::operator>(const Time& right) const
{
    return m_timestamp > right.m_timestamp;
}

bool Time::operator<=(const Time& right) const
{
    return m_timestamp <= right.m_timestamp;
}

bool Time::operator>=(const Time& right) const
{
    return m_timestamp >= right.m_timestamp;
}

std::ostream& operator<<(std::ostream& stream, const Time& time)
{
    stream << std::setw(2) << std::setfill('0') << time.GetHours();
    stream << ":";
    stream << std::setw(2) << std::setfill('0') << time.GetMinutes();
    stream << ":";
    stream << std::setw(2) << std::setfill('0') << time.GetSeconds();
    return stream;
}

std::istream& operator>>(std::istream& stream, Time& time)
{
    std::string str;
    stream >> str;
    auto args = ParseStream(str);
    if (args.size() != 3)
    {
        throw std::invalid_argument("Incorrect time string");
    }
    auto h = std::stoi(args[0]);
    auto m = std::stoi(args[1]);
    auto s = std::stoi(args[2]);
    if (Time::Validate(h, m, s))
    {
        throw std::invalid_argument("Invalid input arguments");
    }
    time.m_timestamp = h * SECONDS_PER_HOUR + m * SECONDS_PER_MINUTE + s;
    return stream;
}

Time Time::CalculateTimestampForAdd(Time time, unsigned diffTimestamp)
{
    time.m_timestamp += diffTimestamp;
    if (time.m_timestamp >= MAX_TIMESTAMP)
    {
        auto excess = time.m_timestamp / MAX_TIMESTAMP; // todo: сколько раз по максимуму в полученном числе
        time.m_timestamp -= excess * MAX_TIMESTAMP;
    }
    return time;
}

Time Time::CalculateTimestampForSub(Time time, unsigned diffTimestamp)
{
    auto temp = time.m_timestamp;
    time.m_timestamp -= diffTimestamp;
    if (time.m_timestamp > MAX_TIMESTAMP) // todo: если вычисть из из 0, то для unsigned получится большое число
    {
        time.m_timestamp = MAX_TIMESTAMP;
        time.m_timestamp -= diffTimestamp;
        time.m_timestamp += temp;
    }
    return time;
}

Time Time::CalculateTimestampForMul(Time time, int mul)
{
    // getHours - возвращает 2 часа, а нам нужно timestamp, поэтому умножаем на константу
    auto newTimestamp = time.GetHours() * mul * SECONDS_PER_HOUR + time.GetMinutes() * mul * SECONDS_PER_MINUTE + time.GetSeconds() * mul;
    if (newTimestamp >= MAX_TIMESTAMP)
    {
        auto excess = newTimestamp / MAX_TIMESTAMP;
        newTimestamp -= excess * MAX_TIMESTAMP;
    }
    time.m_timestamp = newTimestamp;
    return time;
}

Time operator+(const Time &, const Time &) {
    return Time();
}
