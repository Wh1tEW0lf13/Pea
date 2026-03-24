//
// Created by Wh1tEW0lf13 on 21.03.2026.
//

#include "Timer.h"
#include <chrono>

Timer::Timer() = default;
Timer::~Timer() = default;


long long Timer::getTime() {
    return _time;
}

void Timer::start() {
    _start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
}
void Timer::stop() {
    std::chrono::microseconds stop = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::microseconds result = stop - _start;
    _time = result.count();
}

void Timer::reset() {
    _start = std::chrono::microseconds(0);
}
