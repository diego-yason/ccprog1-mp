#include <stdlib.h>

#ifndef ITERATOR_C
#define ITERATOR_C

/**
 * Returns pointer to the intended element number.
 * Precondition: Pointer is an integer pointer.
 * @param pointer Desired pointer to iterate. Will be treated as index 0.
 * @param nElementNumber (0-indexed) Select which element to select.
 * @return int* Pointer to desired element.
 */
int *iteratePointer(int *pointer, int nElementNumber)
{
    return pointer += nElementNumber;
}

#endif