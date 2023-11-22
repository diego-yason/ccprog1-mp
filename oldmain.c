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
    Description: A program that manages 14 buses, 7 of each going to Manila
                 or Laguna. The amount of seats in each time slot is configurable.
    Programmed by: Diego David Perez Yason S24B
    Last modified:
    Version: RC1
 */

/**
 * EXPLANATORY NOTE FOR NAMING SCHEME OF CERTAIN VARIABLES
 *
 * In this project, the way I implemented my data storage via calloc(). This requires me to
 * keep track of the first entry (the pointer given to me when calloc() is called).
 * These pointers are stored in a variable that has the -Anchor suffix, stating that the pointer
 * address inside this variable is the first entry of a set made by calloc().
 */

#include <stdio.h>
#include <stdlib.h>
#include "busManagement.c"
#include "timetable.c"
#include "consoleManagement.c"
#include "iterators.c"
#include "busDisplay.c"

int main()
{
    int
        /**
         * @brief Anchor pointer of buses
         * @details Data stored: Pointer to the first seat of the 1st bus.
         * @note Explicit null necessary to prevent issues
         */
        **pBusesAnchor = NULL,
        /**
         * @brief Anchor pointer of bus layout
         * @details Data stored: Pointer to the seat count of the 1st bus.
         * @note Explicit null necessary to prevent issues
         */
        *pBusLayoutAnchor = NULL,
        /**
         * @brief Cursor to the bus layout
         * @note Separated from pBusesAnchor to ensure anchor status
         */
            **pBusCursor = NULL,
        /**
         * @brief Number of buses in the system
         */
        nBusCount = 14,
        nChoice,
        nCurrentTime = 400,
        nTicketCount = 0,
        nTicketCancellations = 0;

    initializeBuses(14, &pBusesAnchor, &pBusLayoutAnchor);

    do
    {
        printMenu(nCurrentTime);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
        case 1: // Book a ticket
        {
            int nBusNumber = getBusNumber(nBusCount),
                *pSeatCursor, nSeatNumber;

            pBusCursor = iterateInt2Pointer(nBusNumber, pBusesAnchor);

            do
            {
                printf("Select seat number (1 - 14): ");
                scanf("%d", &nSeatNumber);
            } while (nSeatNumber < 1 || nSeatNumber > 14);

            pSeatCursor = iterateInt1Pointer(nSeatNumber, *pBusCursor);

            // Verify if seat is open
            if (*pSeatCursor == 0)
            {
                int nIdNumber;
                printf("Please input the ID number of the person reserving: ");
                scanf("%d", &nIdNumber);

                *pSeatCursor = nIdNumber;
                printf("Successfully reserved seat %d of bus %d for ID %d.\n",
                       nSeatNumber, nBusNumber, nIdNumber);
                nTicketCount++;
            }
            else
            {
                printf("Sorry this seat is occupied by ID %d!\n", *pSeatCursor);
            }

            break;
        }
        case 2: // Cancel a booking
        {
            int nBusNumber = getBusNumber(nBusCount), nSeatNumber;
            // TODO: add printing of seats occupied or whatever

            pBusCursor = iterateInt2Pointer(nBusNumber, pBusesAnchor);

            // TODO: allow seat changes
            printBus(nBusNumber, *iterateInt1Pointer(nBusNumber, pBusLayoutAnchor),
                     *pBusCursor);

            do
            {
                printf("What seat will you be cancelling? ");
                scanf("%d", &nSeatNumber);
            } while (nSeatNumber < 0 || nSeatNumber > 14);

            int *pSeatCursor = iterateInt1Pointer(nSeatNumber, *pBusCursor);

            if (*pSeatCursor == 0)
            {
                printf("You can't cancel an empty seat!");
            }
            else
            {
                printf("Canceled ID %d's reservation for seat %d.", *pSeatCursor, nSeatNumber);
                nTicketCancellations++;
                *pSeatCursor = 0;
            }

            printf("\n");
            break;
        }
        case 3: // Display Schedule
        {

            printf("/-----------------------------\\\n");
            printf("|  B U S   T I M E T A B L E  |\n");
            printf("|  CURRENT TIME:        %04d  |\n", nCurrentTime);
            printf("|-----------------------------|\n");
            printf("| M A N I L A             T O |\n");
            printf("| L A G U N A                 |\n");
            printf("| DEPT. TIME          STATUS  |\n");
            printf("|                             |\n");

            for (int i = 0; i < 8; i++)
            {
                int nTime = 400 + (i * 200),
                    n12HourTime = convert24To12(nTime);
                char c12HourPrefix = getTimePrefix(nTime);

                printf("| %04d  %04d%cm      %9s |\n", nTime, n12HourTime,
                       c12HourPrefix, getBusState(nCurrentTime, nTime));
            }

            printf("|-----------------------------|\n");
            printf("| L A G U N A             T O |\n");
            printf("| M A N I L A                 |\n");
            printf("| DEPT. TIME          STATUS  |\n");
            printf("|                             |\n");

            for (int i = 0; i < 8; i++)
            {
                int nTime = 500 + (i * 200),
                    n12HourTime = convert24To12(nTime);
                char c12HourPrefix = getTimePrefix(nTime);

                printf("| %04d  %04d%cm      %9s |\n", nTime, n12HourTime,
                       c12HourPrefix, getBusState(nCurrentTime, nTime));
            }

            printf("\\-----------------------------/\n");
            break;
        }
        case 4: // Update Time
        {
            int nProposedTime;
            printf("Input new time: ");
            scanf("%d", &nProposedTime);

            if (nProposedTime > nCurrentTime)
            {
                printf("Time updated.\n");
                nCurrentTime = nProposedTime;
            }
            else if (nProposedTime == nCurrentTime)
                printf("It is already %04d!\n", nCurrentTime);
            else
                printf("Cannot reverse time! Please enter a future time.\n");
            break;
        }
        case 5: // Close
        {
            char cConfirm;
            printf("Please confirm your exit by typing \"y\".\nNOTE: ALL DATA WILL BE DELETED UPON EXIT. (y) ");
            fflush(stdin);
            scanf("%c", &cConfirm);

            if (cConfirm == 'y')
            {
                nChoice = -1;

                printf("Thank you for using this system!\n\nS T A T I S T I C S\n");
                printf("Tickets issued     : %d\n", nTicketCount);
                printf("Tickets canceled   : %d\n", nTicketCancellations);
                printf("Net Tickets Issued : %d\n", nTicketCount - nTicketCancellations);
            }
            else
                printf("Returning to main menu.\n");

            break;
        }
        case 6: // Change bus seats
        {
            int nBusNumber = getBusNumber(14),
                bIssuesFound = 0,
                nNewSeatCount, nCurrentSeatCount, i;

            printf("How many seats will bus %d have now? ", nBusNumber);
            scanf("%d", &nNewSeatCount);

            pBusCursor = iterateInt2Pointer(nBusNumber, pBusesAnchor);
            nCurrentSeatCount = *iterateInt1Pointer(nBusNumber, pBusLayoutAnchor);

            if (nCurrentSeatCount > nNewSeatCount)
            {
                // check if doomed seats are already occupied
                for (i = nNewSeatCount; i <= nCurrentSeatCount; i++)
                {
                    if (*iterateInt1Pointer(i, *pBusCursor) != 0)
                        bIssuesFound = 1 || bIssuesFound;
                }
            }

            if (bIssuesFound)
                printf("There are bookings after seat %d! Cancel them before proceeding.\n",
                       nNewSeatCount);
            else
            {
                *pBusCursor = replaceBus(nBusNumber, *pBusCursor,
                                         pBusLayoutAnchor, nNewSeatCount);

                printf("Updated bus configuration!\n");
            }
            break;
        }
        default:
        {
            printf("Invalid Choice! Please, pick again.\n");
            break;
        }
        }
        printf("Press enter to continue. ");
        fflush(stdin);
        getchar();

        clearConsole();
    } while (nChoice != -1);

    return 0;
}