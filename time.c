#ifndef TIME_C
#define TIME_C

int verifyTime(int nTime)
{
    int nHours = nTime / 100,
        nMinutes = nTime % 100;

    return nHours <= 23 && nMinutes <= 59;
}

#endif