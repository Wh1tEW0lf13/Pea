//
// Created by Wh1tEW0lf13 on 21.03.2026.
//

#ifndef TIMER_H
#define TIMER_H
#include <chrono>


class Timer {
    long long _time;
    std::chrono::microseconds _start;
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    long long getTime();
    void reset();
    long long getCurrentTime();
};



#endif //TIMER_H
