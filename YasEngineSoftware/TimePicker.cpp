#include"TimePicker.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

    TimePicker::TimePicker()
    {
        isFrequencyOfThePerformanceCounterPickedUp = (QueryPerformanceFrequency(&frequency) != 0);
        //isFrequencyOfThePerformanceCounterPickedUp = (QueryPerformanceFrequency((LARGE_INTEGER*)&frequency) != 0);
    }

    double TimePicker::getSeconds()
    {
        if(isFrequencyOfThePerformanceCounterPickedUp)
        {
            LARGE_INTEGER ticks;
            QueryPerformanceCounter(&ticks);
            return (double)(ticks.QuadPart / (double)frequency.QuadPart);
        }
        else
        {
            return GetTickCount64() / 1000.0;
        }
    }

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
