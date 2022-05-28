#ifndef TIMEPICKER_HPP
#define TIMEPICKER_HPP
#include<Windows.h>
//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

class TimePicker
{
    public:
        TimePicker();
        double getSeconds() const;

    private:
        LARGE_INTEGER frequency;
        bool isFrequencyOfThePerformanceCounterPickedUp;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
