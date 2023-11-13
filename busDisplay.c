#include <stdio.h>
#include <stdlib.h>
#include "busManagement.c"

void printABooking(int nSeatNumber, int nIdNumber)
{
    printf("SEAT %02d : %d\n", nSeatNumber, nIdNumber);
}

void bookingPrintWithVarChanges(int **pTakenSeatsCursor, int *pSeatAnchor, int *pTakenSeatsCounter)
{
    if (*pTakenSeatsCounter > 0)
    {
        printf("   ");
        printABooking(**pTakenSeatsCursor,
                      *iterateInt1Pointer(**pTakenSeatsCursor, pSeatAnchor));

        // Dev note: warnings were raised when using ++/--
        *pTakenSeatsCounter -= 1;
        *pTakenSeatsCursor += 1;
    }
}

void printBus(int nBusNumber, int nCapacity, int *pSeatAnchor)
{
    int *pTakenSeatsAnchor = calloc(nCapacity, sizeof(int)),
        *pTakenSeatsCursor = pTakenSeatsAnchor,
        nTakenSeatsCounter = 0,
        *pSeatCursor = pSeatAnchor, i;

    // identify taken seats
    for (i = 0; i < nCapacity; i++)
    {
        if (*pSeatCursor != 0)
        {
            *pTakenSeatsCursor = i + 1;
            pTakenSeatsCursor++;
            nTakenSeatsCounter++;
        }

        pSeatCursor++;
    }
    pSeatCursor -= nCapacity;
    pTakenSeatsCursor = pTakenSeatsAnchor;

    printf("  BUS #%02d LAYOUT\n", nBusNumber);
    printf("  ================     BOOKINGS\n");
    printf(" / DR  |         |\\   INSIDE BUS:\n");

    for (i = 1; i <= nCapacity; i++)
    {
        char cTakenIndicator;

        if (*iterateInt1Pointer(i, pSeatAnchor) != 0)
            cTakenIndicator = 'X';
        else
            cTakenIndicator = ' ';

        printf("| %c%02d%c |   | ", cTakenIndicator, i, cTakenIndicator);
        if (nCapacity - i >= 1)
        {
            i++;
            if (*iterateInt1Pointer(i, pSeatAnchor) != 0)
                cTakenIndicator = 'X';
            else
                cTakenIndicator = ' ';
            printf("%c%02d%c |", cTakenIndicator, i, cTakenIndicator);
        }
        else
            printf(" XX  |");

        if (nTakenSeatsCounter > 0)
        {
            printf("   ");
            printABooking(*pTakenSeatsCursor,
                          *iterateInt1Pointer(*pTakenSeatsCursor, pSeatAnchor));
            nTakenSeatsCounter--;
            pTakenSeatsCursor++;
        }
        else
            printf("\n");
    }

    printf("===================");
    if (nTakenSeatsCounter > 0)
        bookingPrintWithVarChanges(&pTakenSeatsCursor, pSeatAnchor,
                                   &nTakenSeatsCounter);
    else
        printf("\n");
    printf("DEST.    : %-6s", "MNL");
    if (nTakenSeatsCounter > 0)
        bookingPrintWithVarChanges(&pTakenSeatsCursor, pSeatAnchor,
                                   &nTakenSeatsCounter);
    else
        printf("\n");
    printf("DEPT.TIME: %04d  ", 400);
    if (nTakenSeatsCounter > 0)
        bookingPrintWithVarChanges(&pTakenSeatsCursor, pSeatAnchor,
                                   &nTakenSeatsCounter);
    else
        printf("\n");
    printf("CAPACITY : %-6d ", nCapacity);
    if (nTakenSeatsCounter > 0)
        bookingPrintWithVarChanges(&pTakenSeatsCursor, pSeatAnchor,
                                   &nTakenSeatsCounter);
    else
        printf("\n");

    for (i = nTakenSeatsCounter; i > 0; i--)
    {
        printf("                    ");
        printABooking(*pTakenSeatsCursor,
                      *iterateInt1Pointer(*pTakenSeatsCursor, pSeatAnchor));
    }

    free(pTakenSeatsAnchor);
}