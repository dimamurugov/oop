#ifndef TIME_TIME_H
#define TIME_TIME_H
#include <ostream>

class Time {
public:
    Time(unsigned hours, unsigned minutes, unsigned seconds = 0);
    Time(unsigned timestamp = 0);
    unsigned GetHours() const; // Константные методы служат для определения того, что можно сделать с классом без побочного действия на его состояние,
    unsigned GetMinutes() const;
    unsigned GetSeconds() const;

    // Теперь вы знаете, как компилятор различает префиксные и постфиксные версии декремента и инкремента.
    // В случае, когда он видит выражение ++i, то вызывается функция operator++(a).
    // Если же он видит i++, то вызывается operator++(a, int).
    // То есть вызывается перегруженная функция operator++, и именно для этого используется фиктивный параметр int в постфиксной версии.
    Time& operator++(); // Time& - ссылка на инстанс объект, что бы сделать инкремент
    Time operator++(int);
    Time& operator--();
    Time operator--(int);

    Time operator+=(Time);
    Time operator-=(Time);
    Time operator*=(int);
    Time operator/=(int);

    friend Time operator+(Time, Time);
    friend Time operator-(Time, Time);
    friend Time operator*(Time, int);
    friend Time operator*(int, Time);
    friend Time operator/(Time, int);
    friend unsigned operator/(Time, Time);

    bool operator==(const Time&) const;
    bool operator<(const Time&) const;
    bool operator>(const Time&) const;
    bool operator<=(const Time&) const;
    bool operator>=(const Time&) const;

    // что такое friend функция
    // что такое const метод класса
    // что такое static функция
    friend std::ostream& operator<<(std::ostream&, const Time&);
    friend std::istream& operator>>(std::istream&, Time&);
private:
    unsigned GetHoursTimestamp() const;
    unsigned GetMinutesTimestamp() const;
    static Time CalculateTimestampForAdd(Time, unsigned);
    static Time CalculateTimestampForSub(Time, unsigned);
    static Time CalculateTimestampForMul(Time, int);
    static bool Validate(unsigned hours, unsigned minutes, unsigned seconds);
    unsigned m_timestamp;
};


#endif //TIME_TIME_H
