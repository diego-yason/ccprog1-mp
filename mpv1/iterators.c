#ifndef ITERATORS_C
#define ITERATORS_C
/**
 * @brief Returns the desired slot in an interator.
 *
 * @param nIdNumber ID/Slot to obtain (1-indexed)
 * @param pIterator Anchor pointer of the iterator. Must be capable to be
 *                  iterated via pointer arithmetic.
 * @return Desired slot (still referenced).
 */
int **iterateInt2Pointer(int nIdNumber, int **pIterator)
{
    return pIterator + (nIdNumber - 1);
}

/**
 * @brief Returns the desired slot in an interator.
 *
 * @param nIdNumber ID/Slot to obtain (1-indexed)
 * @param pIterator Anchor pointer of the iterator. Must be capable to be
 *                  iterated via pointer arithmetic.
 * @return Desired slot (still referenced).
 */
int *iterateInt1Pointer(int nIdNumber, int *pIterator)
{
    return pIterator + (nIdNumber - 1);
}
#endif