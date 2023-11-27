#include <stdlib.h>
#include "console.c"
#include "iterator.c"

#ifndef BUS_MANAGEMENT_C
#define BUS_MANAGEMENT_C

/**
 * Transfers seat data from the former bus to the new bus.
 * Warning: Data from indexes above nHighestOccupiedSeat will be discarded.
 * @param pSeatsAnchor Double pointer, pointing to index 0 of the Seat list
 * @param nHighestOccupiedSeat Highest index of the former bus to transfer to the new bus.
 * @param nNewSeatCount Seats inside updated bus configuration
 */
void transferSeatData(int **pSeatsAnchor, int nHighestOccupiedSeat, int nNewSeatCount)
{
    int *pNewSeatsAnchor = calloc(nNewSeatCount, sizeof(int)),
        *pNewSeatsCursor = pNewSeatsAnchor,
        *pSeatsCursor = *pSeatsAnchor,
        i;

    for (i = 0; i < nHighestOccupiedSeat; i++)
    {
        *pNewSeatsCursor = *pSeatsCursor;

        pSeatsCursor++;
        pNewSeatsCursor++;
    }

    free(*pSeatsAnchor);

    *pSeatsAnchor = pNewSeatsAnchor;
}

#endif