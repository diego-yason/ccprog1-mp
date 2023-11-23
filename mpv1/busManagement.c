#include <stdio.h>
#include <stdlib.h>
#include "iterators.c"

#ifndef BUS_MANAGEMENT_C
#define BUS_MANAGEMENT_C
/**
 * @brief Allocates memory for the buses. Each bus is assumed to be departing
 *        30 minutes after the previous bus at the current bus's stop.
 * @param nBusCount Number of buses in the new schedule.
 * @param ppCurrentBusesAnchor Pointer to the existing ANCHOR bus cursor.
 * @param ppBusSeatReferenceAnchor Pointer to the bus seat reference.
 */
void initializeBuses(int nBusCount, int ***ppCurrentBusesAnchor,
                     int **ppBusSeatReferenceAnchor)
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

    // Make blank dataset
    for (i = 0; i < nBusCount; i++)
    {
        *pBusCursor = calloc(14, sizeof(int));

        *pSeatReferenceCursor = 14;
        pSeatReferenceCursor++;
        pBusCursor++;
    }

    *ppBusSeatReferenceAnchor = pSeatReferenceAnchor;
    *ppCurrentBusesAnchor = pNewBusMainAnchor;
}

/**
 * @brief
 *
 * @return int* Pointer to seat 1 of the new bus
 */
int *replaceBus(int nBusNumber, int *pSeatAnchor,
                int *pSeatReferenceAnchor, int nNewSeatCount)
{
    int *pNewSeatAnchor = NULL, *pNewSeatCursor = NULL, i,
        nOldSeatCount = *iterateInt1Pointer(nBusNumber, pSeatReferenceAnchor),
        *pOldSeatCursor = pSeatAnchor;
    pNewSeatAnchor = pNewSeatCursor = calloc(nNewSeatCount, sizeof(int));

    for (i = 0; i < nOldSeatCount; i++)
    {
        *pNewSeatCursor = *pOldSeatCursor;
        pOldSeatCursor++;
        pNewSeatCursor++;
    }

    *iterateInt1Pointer(nBusNumber, pSeatReferenceAnchor) = nNewSeatCount;

    free(pSeatAnchor);
    return pNewSeatAnchor;
}

/**
 * @brief Requests for a bus number
 *
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
#endif