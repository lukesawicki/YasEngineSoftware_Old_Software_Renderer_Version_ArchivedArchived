// Original code from github: 99x
// https://github.com/99x
// Changes made according to:
// https://www.fluentcpp.com/2018/12/28/timer-cpp/
#ifndef TIMER_HPP
#define TIMER_HPP
#include <thread>
#include <chrono>

class Timer {
    bool clear = false;

public:
    template<typename Function>
    void setTimeout(Function function, int delay) {
        this->clear = false;
        std::thread t([=]() {
            if (this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            if (this->clear) return;
            function();
            });
        t.detach();
    }

    template<typename Function>
    void setInterval(Function function, int interval);

    void stop();

};

//template<typename Function>
void Timer::setTimeout(Function function, int delay) {
    this->clear = false;
    std::thread t([=]() {
        if (this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (this->clear) return;
        function();
        });
    t.detach();
}

template<typename Function>
void Timer::setInterval(Function function, int interval) {
    this->clear = false;
    std::thread t([=]() {
        while (true) {
            if (this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (this->clear) return;
            function();
        }
        });
    t.detach();
}

void Timer::stop() {
    this->clear = true;
}

#endif