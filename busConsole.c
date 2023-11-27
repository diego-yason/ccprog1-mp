#include <stdio.h>
#include <stdlib.h>
#include "console.c"
#include "iterator.c"

#ifndef BUS_CONSOLE_C
#define BUS_CONSOLE_C

/**
 * Prints seat inside bus layout, indicates if seat is occupied.
 * Precondition: Formatting is only set for 2 digit numbers (nSeatNumber), but
 * code will still work on 3+ digits, however formatting/style will break.
 * @param nSeatNumber Number of the specific seat
 * @param nIdInSeat If occupied, ID number of occupant. Otherwise 0.
 */
void printSeatInfo(int nSeatNumber, int nIdInSeat)
{
    if (nIdInSeat == 0)
        printf("| %02d |", nSeatNumber);
    else
        printf("|X%02dX|", nSeatNumber);
}

/**
 * Prints booking information for a certain seat
 *
 * @param ppOccupiedSeatsList Pointer pointing to the pointer to the Occupied Seats Cursor
 * @param pSeatsAnchor Pointer to the Seat Anchor
 * @param pOccupiedSeatsCount Pointer to the counter for occupied seats
 * @param bFullPadding True when console line has no bus layout
 */
void printBookingInfo(int **ppOccupiedSeatsList, int *pSeatsAnchor,
                      int *pOccupiedSeatsCount, int bFullPadding)
{
    if (bFullPadding)
        repeatPrint(' ', 22);
    else
        repeatPrint(' ', 9);

    int nSeatNumber = **ppOccupiedSeatsList;
    printf("%2d - %d", nSeatNumber,
           *iteratePointer(pSeatsAnchor, nSeatNumber - 1));
    (*pOccupiedSeatsCount)--;
    (*ppOccupiedSeatsList)++;
}

/**
 * Prints bus information, including layout, seats, and trip information
 *
 * @param pSeatsAnchor Pointer to the list of seats
 * @param nSeatCount Total amount of seats inside bus
 * @param nDepartureTime The departure time of the bus
 */
void printBus(int *pSeatsAnchor, int nSeatCount, int nDepartureTime)
{
    int i,
        *pSeatsCursor = pSeatsAnchor,
        *pOccupiedSeatsListAnchor = calloc(nSeatCount, sizeof(int *)),
        *pOccupiedSeatsListCursor1, *pOccupiedSeatsListCursor2,
        nOccupiedSeatsCount = 0;

    pOccupiedSeatsListCursor1 = pOccupiedSeatsListCursor2 = pOccupiedSeatsListAnchor;

    char *sOrigin, *sDestination, cTimePrefix;

    for (i = 1; i <= nSeatCount; i++)
    {
        if (*pSeatsCursor != 0)
        {
            *pOccupiedSeatsListCursor1 = i;
            nOccupiedSeatsCount++;
            pOccupiedSeatsListCursor1++;
        }
        pSeatsCursor++;
    }
    pOccupiedSeatsListCursor1 = pOccupiedSeatsListAnchor;

    if (nDepartureTime % 200 == 0)
    {
        sOrigin = "MANILA";
        sDestination = "LAGUNA";
    }
    else
    {
        sOrigin = "LAGUNA";
        sDestination = "MANILA";
    }

    if (nDepartureTime >= 1200)
        cTimePrefix = 'p';
    else
        cTimePrefix = 'a';

    repeatPrint(' ', 10);
    printf("INFORMATION BOARD\n");

    printf(" Bus Route");
    repeatPrint(' ', 8);
    printf(": %6s - %6s\n", sOrigin, sDestination);

    printf(" Seats Available");
    repeatPrint(' ', 2);
    printf(": %d\n", nSeatCount - nOccupiedSeatsCount);

    printf(" Departure Time");
    repeatPrint(' ', 3);
    printf(": %04d / %2d:%02d %cm\n", nDepartureTime,
           nDepartureTime / 100, nDepartureTime % 100, cTimePrefix);

    // Special case
    if (nDepartureTime == 1100)
        cTimePrefix = 'p';

    printf(" Arrival Time");
    repeatPrint(' ', 5);
    printf(": %04d / %2d:%02d %cm\n", nDepartureTime + 100,
           (nDepartureTime + 100) / 100, (nDepartureTime + 100) % 100, cTimePrefix);

    repeatPrint('=', 36);
    printf("\n");

    printf("BUS");
    repeatPrint(' ', 4);
    printf("LAYOUT");
    repeatPrint(' ', 9);

    printf("BOOKED  SEATS\n\n");

    printf("/");
    repeatPrint('=', 12);
    if (nOccupiedSeatsCount > 0)
        printBookingInfo(&pOccupiedSeatsListCursor1, pSeatsAnchor,
                         &nOccupiedSeatsCount, 0);
    printf("\n");

    printf("| DR |");
    repeatPrint(' ', 6);
    printf("\\");
    if (nOccupiedSeatsCount > 0)
        printBookingInfo(&pOccupiedSeatsListCursor1, pSeatsAnchor,
                         &nOccupiedSeatsCount, 0);
    printf("\n");

    for (i = 1; i <= nSeatCount; i++)
    {
        int bIsOccupied = *pOccupiedSeatsListCursor2 == i;
        printSeatInfo(i, bIsOccupied);

        if (bIsOccupied)
            pOccupiedSeatsListCursor2++;

        if (i % 2 == 1)
            printf(" ");
        else if (nOccupiedSeatsCount > 0)
            printBookingInfo(&pOccupiedSeatsListCursor1, pSeatsAnchor,
                             &nOccupiedSeatsCount, 0);

        if (i % 2 == 0)
            printf("\n");
    }
    if (nSeatCount % 2 == 1)
    {
        printf("|XXXX|");
        if (nOccupiedSeatsCount > 0)
            printBookingInfo(&pOccupiedSeatsListCursor1, pSeatsAnchor,
                             &nOccupiedSeatsCount, 0);
        printf("\n");
    }

    repeatPrint('=', 14);
    if (nOccupiedSeatsCount > 0)
        printBookingInfo(&pOccupiedSeatsListCursor1, pSeatsAnchor,
                         &nOccupiedSeatsCount, 0);
    printf("\n");

    while (nOccupiedSeatsCount > 0)
    {
        printBookingInfo(&pOccupiedSeatsListCursor1, pSeatsAnchor,
                         &nOccupiedSeatsCount, 1);
        printf("\n");
    }

    free(pOccupiedSeatsListAnchor);
}

/**
 * Prints a divider for the timetable
 */
void printTimetableDivider()
{
    printf("|");
    repeatPrint('=', 32);
    printf("|\n");
}

/**
 * Determines the status of the bus based on the current time
 * and the bus's departure time.
 * @param nCurrentTime Currently set time
 * @param nDepartureTime Departure time of the bus
 * @return char* Status of the bus. String.
 */
char *getBusStatus(int nCurrentTime, int nDepartureTime)
{
    if (nCurrentTime == nDepartureTime)
        return "BOARDING";
    else if (nCurrentTime > nDepartureTime)
        return "DEPARTED";
    else if (nCurrentTime + 100 == nDepartureTime)
        return "NEXT BUS";
    else
        return "SCHEDULED";
}

/**
 * Prints timetable of the bus, including the status based off the time.
 * Precondition: Assumes the currently set schedule of a bus leaving every
 * 2 hours from each campus, from 4am in Manila and from 5am in Laguna.
 * @param nCurrentTime Currently set time
 */
void printTimetable(int nCurrentTime)
{
    int nBusTime, nHour;
    char cTimePrefix;

    printTimetableDivider();
    printf("|  T R I P S  T I M E T A B L E  |\n");
    printf("| CURRENT TIME:");
    repeatPrint(' ', 13);
    printf("%04d |\n", nCurrentTime);
    printf("|");
    repeatPrint(' ', 24);

    if (nCurrentTime >= 1200)
        cTimePrefix = 'p';
    else
        cTimePrefix = 'a';

    // special case
    nHour = nCurrentTime / 100;
    if (nHour > 12)
        nHour -= 12;

    printf("%2d:%02d%cm |\n", nHour, nCurrentTime % 100, cTimePrefix);
    printTimetableDivider();

    // MNL -> LAG
    printf("| M A N I L A  T O");
    repeatPrint(' ', 15);
    printf("|\n");
    printf("| L A G U N A");
    repeatPrint(' ', 20);
    printf("|\n");
    printf("| DEPT. TIME");
    repeatPrint(' ', 14);
    printf("STATUS |\n");

    for (nBusTime = 400; nBusTime < 1900; nBusTime += 200)
    {
        if (nBusTime >= 1200)
            cTimePrefix = 'p';
        else
            cTimePrefix = 'a';

        // special case
        nHour = nBusTime / 100;
        if (nHour > 12)
            nHour -= 12;
        printf("| %04d / %2d:%02d%cm", nBusTime, nHour, nBusTime % 100, cTimePrefix);
        repeatPrint(' ', 7);
        printf("%9s |\n", getBusStatus(nCurrentTime, nBusTime));
    }

    printTimetableDivider();
    // LAG -> MNL
    printf("| L A G U N A  T O");
    repeatPrint(' ', 15);
    printf("|\n");
    printf("| M A N I L A");
    repeatPrint(' ', 20);
    printf("|\n");
    printf("| DEPT. TIME");
    repeatPrint(' ', 14);
    printf("STATUS |\n");

    for (nBusTime = 500; nBusTime < 1900; nBusTime += 200)
    {
        if (nBusTime >= 1200)
            cTimePrefix = 'p';
        else
            cTimePrefix = 'a';

        // special case
        nHour = nBusTime / 100;
        if (nHour > 12)
            nHour -= 12;
        printf("| %04d / %2d:%02d%cm", nBusTime, nHour, nBusTime % 100, cTimePrefix);
        repeatPrint(' ', 7);
        printf("%9s |\n", getBusStatus(nCurrentTime, nBusTime));
    }

    printTimetableDivider();
}

#endif