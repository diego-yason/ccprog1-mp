char *getBusState(int nTime, int nSchedule)
{
    int nTimeDifference = nSchedule - nTime;

    if (nTimeDifference < 0)
    {
        return "DEPARTED";
    }
    else if (nTimeDifference == 0)
    {
        return "DEPARTING";
    }
    else if (nTimeDifference <= 100)
    {
        return "NEXT BUS";
    }
    else
    {
        return "SCHEDULED";
    }
}

char getTimePrefix(int nTime)
{
    if (nTime >= 1200)
        return 'p';
    else
        return 'a';
}

int convert24To12(int nTime)
{
    if (nTime != 1200)
        return nTime % 1200;
    else
        return nTime;
}