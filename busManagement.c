#include <stdlib.h>
#include "menu.c"
#include "iterator.c"

#ifndef BUS_MANAGEMENT_C
#define BUS_MANAGEMENT_C

int *transferSeatData(int *pSeatsAnchor, int nPreviousCount, int nNewSeatCount)
{
    int *pNewSeatsAnchor = calloc(nNewSeatCount, sizeof(int)),
        *pNewSeatsCursor = pNewSeatsAnchor,
        *pSeatsCursor = pSeatsAnchor,
        i;

    for (i = 0; i < nPreviousCount; i++)
    {
        *pNewSeatsCursor = *pSeatsCursor;

        pSeatsCursor++;
        pNewSeatsCursor++;
    }

    free(pSeatsAnchor);

    return pNewSeatsAnchor;
}

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
 * @param pOccupiedSeatsList Pointer to the Occupied Seats List
 * @param pSeatsAnchor Pointer to the Seat Anchor
 * @param pOccupiedSeatsCount Pointer to the counter for occupied seats
 * @param bFullPadding True when console line has no bus layout
 */
void printBookingInfo(int *pOccupiedSeatsList, int *pSeatsAnchor,
                      int *pOccupiedSeatsCount, int bFullPadding)
{
    if (bFullPadding)
        repeatPrint(' ', 22);
    else
        repeatPrint(' ', 9);

    int nSeatNumber = *pOccupiedSeatsList;
    printf("%02d - %d", nSeatNumber + 1,
           *iteratePointer(pSeatsAnchor, nSeatNumber));
    (*pOccupiedSeatsCount)--;
    pOccupiedSeatsList++;
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
        *pOccupiedSeatsListCursor = pOccupiedSeatsListAnchor,
        nOccupiedSeatsCount = 0;

    char *sOrigin, *sDestination, cTimePrefix;

    for (i = 0; i < nSeatCount; i++)
    {
        if (*pSeatsCursor != 0)
        {
            *pOccupiedSeatsListCursor = i;
            nOccupiedSeatsCount++;
            pOccupiedSeatsListCursor++;
        }
    }
    pOccupiedSeatsListCursor = pOccupiedSeatsListAnchor;

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

    repeatPrint(' ', 13);
    printf("INFORMATION\n");

    printf(" Bus Route");
    repeatPrint(' ', 8);
    printf(": %6s - %6s\n", sOrigin, sDestination);

    printf(" Seats Available");
    repeatPrint(' ', 2);
    printf(": %d\n", nSeatCount - nOccupiedSeatsCount);

    printf(" Departure Time");
    repeatPrint(' ', 3);
    printf(": %04d / %02d:%02d %cm\n", nDepartureTime,
           nDepartureTime % 100, nDepartureTime / 100, cTimePrefix);

    // Special case
    if (nDepartureTime == 1100)
        cTimePrefix = 'p';

    printf(" Arrival Time");
    repeatPrint(' ', 5);
    printf(": %04d / %02d:%02d %cm\n", nDepartureTime + 100,
           (nDepartureTime + 100) % 100, (nDepartureTime + 100) / 100, cTimePrefix);

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
        printBookingInfo(pOccupiedSeatsListCursor, pSeatsAnchor,
                         &nOccupiedSeatsCount, 0);
    printf("\n");

    printf("| DR |");
    repeatPrint(' ', 6);
    printf("\\");
    if (nOccupiedSeatsCount > 0)
        printBookingInfo(pOccupiedSeatsListCursor, pSeatsAnchor,
                         &nOccupiedSeatsCount, 0);
    printf("\n");

    for (i = 0; i < nSeatCount; i++)
    {
        int bIsOccupied = *pOccupiedSeatsListCursor == i;
        printSeatInfo(i + 1, bIsOccupied);

        if (bIsOccupied)
            pOccupiedSeatsListCursor++;

        if (i % 2 == 1)
            printf(" ");
        else if (nOccupiedSeatsCount > 0)
            printBookingInfo(pOccupiedSeatsListCursor, pSeatsAnchor,
                             &nOccupiedSeatsCount, 0);

        if (i % 2 == 0)
            printf("\n");
    }

    free(pOccupiedSeatsListAnchor);
}

#endif