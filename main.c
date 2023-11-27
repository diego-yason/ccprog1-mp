/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
Diego David Perez Yason, DLSU ID# 12308978
******************************************************************/

/*
    Description: Ticketing system, tracking a singular bus at a time.
    Programmed by: Diego David Perez Yason S24B
    Last modified: 28 November 2023
    Version: Release Candidate 3
    Acknowledgements:
    C documentation via DevDocs -- https://devdocs.io/c/
*/

#include <stdio.h>
#include <stdlib.h>
#include "busConsole.c"
#include "busManagement.c"
#include "console.c"
#include "time.c"

int main()
{
    char cBuffer;
    int nChoice,
        nTicketCount = 0,
        nBus = 1,
        nCurrentTime = 400,
        nSeats = 14,
        nTakenSeats = 0,
        *pSeatsAnchor = calloc(nSeats, sizeof(int));

    do
    {
        // Menu select
        printMenu(nCurrentTime);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
        case 1:
        {
            // Booking a ticket
            int nSeatNumber,
                nId,
                *pSeat;

            printBus(pSeatsAnchor, nSeats, nCurrentTime);

            collectSeatNumber(&nSeatNumber, nSeats);
            pSeat = iteratePointer(pSeatsAnchor, nSeatNumber - 1);

            if (*pSeat == 0)
            {
                int bValidId;
                // Obtain valid ID
                do
                {
                    printf("Enter ID number of the person booking: ");
                    scanf("%d", &nId);

                    // ID 90s are permitted to use the system
                    bValidId = nId < 9000000 || nId > 99999999;

                    if (!bValidId)
                        printf("Please enter a valid DLSU ID number.\n");
                } while (!bValidId);

                printf("The booking of ID %d for seat %d is successful.\n", nId, nSeatNumber);

                // Set ID number to seat, increment counters
                *pSeat = nId;
                nTakenSeats++;
                nTicketCount++;
            }
            else
                printf("Seat is occupied. Returning to menu.\n");
            break;
        }
        case 2:
        {
            // Cancelling a seat
            int nSeatNumber, *pSeat;
            char cConfirm;
            printBus(pSeatsAnchor, nSeats, nCurrentTime);

            collectSeatNumber(&nSeatNumber, nSeats);
            pSeat = iteratePointer(pSeatsAnchor, nSeatNumber - 1);

            // Verify if seat is taken
            if (*pSeat != 0)
            {
                // confirmation required
                printf("Please confirm to cancel seat %d. Currently held by ID %d.\n(y) ", nSeatNumber, *pSeat);
                fflush(stdin);
                scanf("%c", &cConfirm);

                if (cConfirm == 'y')
                {
                    printf("Cancelled ID %d's reservation for seat %d.\n", *pSeat, nSeatNumber);

                    // Clear booking, decrement counters
                    *pSeat = 0;
                    nTakenSeats--;
                    nTicketCount--;
                }
                else
                    printf("Cancelled cancellation. Returning to menu.\n");
            }
            else
                printf("This seat is not occupied. Returning to menu.\n");
            break;
        }
        case 3:
        {
            // Print timetable
            printTimetable(nCurrentTime);
            break;
        }
        case 4:
        {
            // Change time
            int nProposedTime, bValidTime;

            do
            {
                printf("Enter the departure time of the next desired bus: ");
                scanf("%d", &nProposedTime);
                bValidTime = verifyTime(nProposedTime);

                if (!bValidTime)
                    printf("Please enter a valid time.\n");
            } while (!bValidTime);

            // Verify if time is: (1) Valid departure time, (2) is not in the past, (3) Is within the timetable [partially #1]
            if (nProposedTime % 100 == 0 &&
                nProposedTime > nCurrentTime &&
                nProposedTime < 1900) // NOTE: 1900 is the final bus time
            {
                // Request for confirmation due to deletion of records, and irreversible change
                printf("WARNING: Existing booking data for current bus will be deleted upon confirmation.\n");
                printf("Confirm? (y) ");
                fflush(stdin);
                scanf("%c", &cBuffer);

                if (cBuffer == 'y')
                {
                    printf("Updated time.\n");

                    // update time
                    nCurrentTime = nProposedTime;

                    // reset bus data
                    free(pSeatsAnchor);
                    pSeatsAnchor = calloc(14, sizeof(int));
                    nSeats = 14;
                    nTakenSeats = 0;

                    nBus = (nCurrentTime - 400) / 100 + 1;
                }
                else
                {
                    printf("Returning to menu...\n");
                }
            }
            else
                printf("Please check timetable and use any of the *scheduled* departure times.\n");

            break;
        }
        case 5:
        {
            // Close app
            printf("WARNING: All data will be deleted upon confirmation.\n Continue to exit program? (y) ");
            fflush(stdin);
            scanf("%c", &cBuffer);

            if (cBuffer == 'y')
            {
                printf("Exiting program. Thank you for using this application!\n");
                printf("\n\n== S T A T I S T I C S ==\n\n");
                printf("   TICKETS BOOKED: %3d\n", nTicketCount);
            }
            else
            {
                printf("Returning to menu...\n");
                nChoice = 0;
            }
            break;
        }
        case 6:
        {
            // Change seat configuration of bus
            printf("NOTE: This will update the seat configuration of bus %d.\nContinue? (y) ", nBus);
            fflush(stdin);
            scanf("%c", &cBuffer);

            if (cBuffer == 'y')
            {
                int i, nNewSeatCount, nMinimumCount = 1;
                // Find highest occupied seat
                for (i = 0; i < nSeats; i++)
                {
                    if (*iteratePointer(pSeatsAnchor, i) != 0)
                        nMinimumCount = i + 1;
                }

                printf("Minimum seats required: %d\n\n", nMinimumCount);

                printf("Enter new seat configuration: ");
                scanf("%d", &nNewSeatCount);

                // Only allow seat configuration higher than or equal to the highest occupied seat
                if (nMinimumCount <= nNewSeatCount)
                {
                    printf("Updated seat count from %d to %d.\n", nSeats, nNewSeatCount);

                    transferSeatData(&pSeatsAnchor, nMinimumCount, nNewSeatCount);
                    nSeats = nNewSeatCount;
                }
                else
                {
                    printf("ERROR: New seat count is lower than permitted!\n");
                }
            }
            else
            {
                printf("Returning to menu...\n");
            }
            break;
        }
        default:
        {
            printf("Invalid choice!\n");
            break;
        }
        }
        // Require confirmation before clearing console
        printf("Press enter to continue.");
        fflush(stdin);
        getchar();
        clearConsole();

    } while (nChoice != 5);
}