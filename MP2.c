/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
DIEGO DAVID PEREZ YASON, DLSU ID# 12308978
******************************************************************/

/*
    Description
    Programmed by: Diego David Perez Yason S24B
    Last modified:
    Version:
 */

#include <stdio.h>
#include <stdlib.h>
#include "busManagement.c"

void printMenu(int nTime)
{
    printf("Welcome, Teller!\n");
    printf("It is %d:%02d\n", nTime / 100, nTime % 100);
    printf("1 - Book a Ticket\n");
    printf("2 - Cancel a Ticket\n");
    printf("3 - Display Timetable\n");
    printf("4 - Update Current Time\n");
    printf("5 - Exit\n");
    printf("6 - Change Bus Configuration\n");
    printf("7 - Go to Next Day\n");
    printf("Select your choice: ");
}

/**
 *
 */
int getBusNumber(int nCount)
{
    int nChoice;
    do
    {
        printf("Pick a bus number (1 - %d): ", nCount);
        scanf("%d", &nChoice);
    } while (nChoice < 1 || nChoice > nCount);

    return nChoice;
}

int main()
{
    // all values initialized here are specified via MP specs
    int **pBuses = NULL, // Explicit null necessary to prevent issues
        *pBusSeats = (int *)(malloc(14 * sizeof(int))),
        nBusCount = 14,
        nChoice,
        nCurrentTime = 400,
        nTicketCount = 0,
        nTicketCancellations = 0,
        nDay = 1;

    initializeBuses(14, &pBuses, &pBusSeats, 0);

    do
    {
        printMenu(nCurrentTime);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
        case 1: // Book a ticket
        {
            // TODO: allow different configs
            int nBusNumber = getBusNumber(nBusCount),
                *pBus = *iterateBusPointer(nBusNumber, pBuses),
                *pSeat, nSeatNumber;

            do
            {
                printf("Select seat number (1 - 14): ");
                scanf("%d", &nSeatNumber);
            } while (nSeatNumber < 1 || nSeatNumber > 14);

            pSeat = iterateSeatPointer(nSeatNumber, pBus);

            // Verify if seat is open
            if (*pSeat == 0)
            {
                int nId;
                printf("Please input the ID number of the person reserving: ");
                scanf("%d", &nId);

                *pSeat = nId;
                printf("Successfully reserved seat %d of bus %d for ID %d.\n",
                       *pSeat, nBusNumber, nId);
                nTicketCount++;
            }
            else
            {
                printf("Sorry this seat is occupied by ID %d!\n", *pSeat);
            }

            break;
        }
        case 2: // Cancel a booking
        {
            int nBusNumber = getBusNumber(nBusCount), nSeatNumber;
            // TODO: add printing of seats occupied or whatever

            do
            {
                printf("What seat will you be cancelling? ");
                scanf("%d", &nSeatNumber);
            } while (nSeatNumber < 0 || nSeatNumber > 14);

            int *pSeat = iterateSeatPointer(nSeatNumber,
                                            *iterateBusPointer(nBusNumber, pBuses));

            if (*pSeat == 0)
            {
                printf("You can't cancel an empty seat!");
            }
            else
            {
                *pSeat = 0;
                nTicketCancellations++;

                printf("Canceled ID %d's reservation for seat %d.", *pSeat, nSeatNumber);
            }

            printf("\n");
            break;
        }
        case 3: // Display Schedule
        {
            break;
        }
        case 4: // Update Time
        {
            break;
        }
        case 5: // Close
        {
            nChoice = -1;
            break;
        }
        case 6: // Change bus seats
        {
            break;
        }
        case 7: // Next day (why not)
        {
            break;
        }
        case 8: // add more buses
        {
            initializeBuses(16, &pBuses, &pBusSeats, 1);
            break;
        }
        default:
        {
            printf("Invalid Choice! Please, pick again.\n");
            break;
        }
        }
    } while (nChoice != -1);

    return 0;
}