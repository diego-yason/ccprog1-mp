#ifndef TIME_C
#define TIME_C

/**
 * Verifies if time in integer format is valid
 * @param nTime Time in question
 * @return int Boolean if time is valid
 */
int verifyTime(int nTime)
{
    int nHours = nTime / 100,
        nMinutes = nTime % 100;

    return nHours <= 23 && nMinutes <= 59;
}

#endif