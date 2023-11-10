#include <stdlib.h>

/**
 * Returns the appropriate bus in the buses interator.
 * Precondition: pIterator can be iterated via pointer arithmetic.
 * @param nIdNumber ID/Slot to obtain (1-indexed)
 * @param pIterator Pointer to the bus
 * @return Desired bus
 */
int **iterateBusPointer(int nIdNumber, int **pIterator)
{
    return (pIterator + (nIdNumber - 1));
}

/**
 * Returns the appropriate seat in the bus interator.
 * Precondition: pIterator can be iterated via pointer arithmetic.
 * @param nIdNumber ID/Slot to obtain (1-indexed)
 * @param pIterator Pointer to the bus
 * @return Desired seat
 */
int *iterateSeatPointer(int nIdNumber, int *pIterator)
{
    return (pIterator + (nIdNumber - 1));
}

/**
 * Allocate memory for the buses. Each bus is assumed to be departing
 * 30 minutes after the previous bus at the current bus's stop.
 * Precondition: When bTransferData is true: # of existing buses <= nBusCount.
 * @param nBusCount Number of buses in the new schedule.
 * @param pCurrentBuses Pointer to the existing bus reference.
 * @param pBusSeats Pointer to the existing seat reference.
 * @param bTransferData Flag to indicate whether to transfer existing data.
 * @warning If transferring data, nBusCount cannot be lesser than the existing bus count.
 */
void initializeBuses(int nBusCount, int ***pCurrentBuses, int **pBusSeats, int bTransferData)
{
    int i, j, nPreviousSetSize,
        **pNewBusMain = malloc(nBusCount * sizeof(int *)),
        *pSeatReference = *pBusSeats,
        **pBusPointer;

    if (bTransferData == 1)
    {
        // nPreviousSetSize = sizeof(*pCurrentBuses) * 14 / sizeof(int **); // TODO: replace 14 with bus count variable

        // // allocate memory first
        // pBusPointer = pNewBusMain;
        // for (i = 0; i < nPreviousSetSize; i++)
        // {
        //     int nNumberOfSeats = *(pSeatReference + i);
        //     *pBusPointer = calloc(nNumberOfSeats, sizeof(int));
        //     pBusPointer++;
        // }

        // // set the rest to default size
        // if (nPreviousSetSize < nBusCount)
        // {
        //     for (i = 0; i < nBusCount - nPreviousSetSize; i++)
        //     {
        //         *pBusPointer = calloc(14, sizeof(int));
        //         pBusPointer++;
        //     }
        // }

        // // Start deleting the old set
        // pBusPointer = pNewBusMain;
        // for (i = 0; i < nPreviousSetSize; i++)
        // {
        //     int *pOldBus = *(*pCurrentBuses + i),
        //         *pNewBus = *(pBusPointer + i);
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
        // free(*pCurrentBuses);
    }
    else
    {
        int *pSeatRef = *pBusSeats;
        pBusPointer = pNewBusMain;
        for (i = 0; i < nBusCount; i++)
        {
            *pBusPointer = calloc(14, sizeof(int));
            pBusPointer++;

            // seat count
            *pSeatRef = 14;
            pSeatRef++;
        }
    }
    *pCurrentBuses = pNewBusMain;
}