#include <stdio.h>
#include <stdlib.h>
#include "menu.c"

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
        printMenu();
        scanf("%d", &nChoice);

        switch (nChoice)
        {
        case 1:
        {

            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            int nProposedTime;

            printf("Enter new departure time: ");
            scanf("%d", &nProposedTime);

            if (nProposedTime % 100 == 0 &&
                nProposedTime < nCurrentTime &&
                nProposedTime > 1900) // NOTE: 1900 is the final bus
            {
                printf("WARNING: Existing booking data for current bus will be deleted upon confirmation.\n");
                printf("Confirm? (y) ");
                scanf("%c", &cBuffer);

                if (cBuffer == 'y')
                {
                    printf("Updated time.\n");
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
                printf("Please check timetable and use any of the scheduled departure times.\n");

            break;
        }
        case 5:
        {
            printf("WARNING: All data will be deleted upon confirmation.\n Continue to exit program? (y) ");
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

            printf("NOTE: This will update the seat configuration of bus %d.\nContinue? (y) ", nBus);
            scanf("%c", &cBuffer);

            if (cBuffer == 'y')
            {
                int nNewSeatCount, nMinimumCount;
                // TODO: Obtain highest seat taken

                printf("Minimum seats required: %d\n\n", nMinimumCount);

                printf("Enter new seat configuration: ");
                scanf("%d", &nNewSeatCount);

                if (nMinimumCount < nNewSeatCount)
                {
                    printf("Updated seat count from %d to %d.\n", nSeats, nNewSeatCount);

                    pSeatsAnchor = transferSeatData(pSeatsAnchor, nSeats, nNewSeatCount);
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

        printf("Press enter to continue.");
        fflush(stdin);
        getchar();
    } while (nChoice != 5);
}