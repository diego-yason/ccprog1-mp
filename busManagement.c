#include <stdlib.h>
#include "console.c"
#include "iterator.c"

#ifndef BUS_MANAGEMENT_C
#define BUS_MANAGEMENT_C

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