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