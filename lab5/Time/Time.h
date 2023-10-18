#ifndef TIME_TIME_H
#define TIME_TIME_H


class Time {
public:
    Time(unsigned hours, unsigned minutes, unsigned seconds = 0);
    Time(unsigned timestamp = 0);
private:
    static bool Validate(unsigned hours, unsigned minutes, unsigned seconds);

    unsigned m_timestamp;
};


#endif //TIME_TIME_H
