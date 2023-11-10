#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Allocates memory for the buses. Each bus is assumed to be departing
 *        30 minutes after the previous bus at the current bus's stop.
 * @param nBusCount Number of buses in the new schedule.
 * @param ppCurrentBusesAnchor Pointer to the existing ANCHOR bus cursor.
 * @param ppBusSeatReferenceAnchor Pointer to the bus seat reference.
 * @param bTransferData Flag to indicate whether to transfer existing data.
 * @warning If transferring data, nBusCount cannot be lesser than the existing bus count.
 */
void initializeBuses(int nBusCount, int ***ppCurrentBusesAnchor,
                     int **ppBusSeatReferenceAnchor, int bTransferData)
{
    int
        /**
         * @brief Anchor pointer to the first new bus (seat 1 of bus 1).
         * @details Data stored: Pointer to the first seat of each bus.
         */
        **pNewBusMainAnchor = calloc(nBusCount, sizeof(int *)),
        /**
         * @brief Anchor pointer to the seat reference (starting at bus 1).
         * @details Data stored: Pointer to an integer, defines the seat
         *          count for the respective bus.
         */
        *pSeatReferenceAnchor = calloc(nBusCount, sizeof(int)),
        /**
         * @brief Cursor to the seat reference (starting at bus 1).
         * @note Separated from pSeatReferenceAnchor to ensure anchor status.
         */
            *pSeatReferenceCursor = pSeatReferenceAnchor,
        /**
         * @brief Pointer to the new current bus
         * @note Separated from pNewBusMainAnchor to ensure anchor status.
         */
                **pBusCursor = pNewBusMainAnchor,
        i;
    // nPreviousSetSize,

    if (bTransferData == 1)
    {
        // nPreviousSetSize = sizeof(*ppCurrentBusesAnchor) * 14 / sizeof(int **); // TODO: replace 14 with bus count variable

        // // allocate memory first
        // pBusCursor = pNewBusMain;
        // for (i = 0; i < nPreviousSetSize; i++)
        // {
        //     int nNumberOfSeats = *(pSeatReference + i);
        //     *pBusCursor = calloc(nNumberOfSeats, sizeof(int));
        //     pBusCursor++;
        // }

        // // set the rest to default size
        // if (nPreviousSetSize < nBusCount)
        // {
        //     for (i = 0; i < nBusCount - nPreviousSetSize; i++)
        //     {
        //         *pBusCursor = calloc(14, sizeof(int));
        //         pBusCursor++;
        //     }
        // }

        // // Start deleting the old set
        // pBusCursor = pNewBusMain;
        // for (i = 0; i < nPreviousSetSize; i++)
        // {
        //     int *pOldBus = *(*ppCurrentBusesAnchor + i),
        //         *pNewBus = *(pBusCursor + i);
        //     for (j = 0; j < *(pSeatReference + i); j++)
        //     {
        //         // Variables are required due to
        //         // the free() at the end of loop
        //         int *pOldSeat = pOldBus + j,
        //             *pNewSeat = pNewBus + j;

        //         // Transfer seat data
        //         // New bus seat = Old bus seat
        //         *pNewBus = *pOldBus;

        //         free(pOldSeat);
        //     }
        //     free(pOldBus);
        // }
        // free(*ppCurrentBusesAnchor);
    }
    else
    {
        // Make blank dataset
        for (i = 0; i < nBusCount; i++)
        {
            *pBusCursor = calloc(14, sizeof(int));

            *pSeatReferenceCursor = 14;
            pSeatReferenceCursor++;
            pBusCursor++;
        }
    }

    // TODO: set free() for old buses and cursors

    *ppBusSeatReferenceAnchor = pSeatReferenceCursor;
    *ppCurrentBusesAnchor = pNewBusMainAnchor;
}

/**
 * @brief Requests for a bus number
 * @param nCount Number of buses in the schedule
 * @return Bus number
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