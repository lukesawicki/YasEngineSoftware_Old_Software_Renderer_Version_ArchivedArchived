#ifndef TIMEPICKER_HPP
#define TIMEPICKER_HPP
//#include<iostream>
#include<Windows.h>
//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

class TimePicker
{
    public:
        TimePicker();
        double getSeconds();

    private:
        LARGE_INTEGER frequency;
        bool isFrequencyOfThePerformanceCounterPickedUp;
};

#endif

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
