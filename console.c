#include <stdio.h>

#ifndef MENU_C
#define MENU_C

/**
 * Prints the main menu of the program
 * @param nCurrentTime Currently set time
 */
void printMenu(int nCurrentTime)
{
    printf("Welcome, teller!\nCurrent Time:    %04d\n", nCurrentTime);
    printf("==========================================\n");
    printf("1 - Book a Ticket\n");
    printf("2 - Cancel a Ticket\n");
    printf("3 - Display Timetable\n");
    printf("4 - Update Departure Time\n");
    printf("5 - Exit\n");
    printf("6 - Change Bus Configuration\n");
    printf("Select Option: ");
}

/**
 * Clears console. Compatible with UNIX-like systems and Windows.
 */
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Repeats a specific character multiple times
 * @param character Character to repeat
 * @param amount Total times to repeat character
 */
void repeatPrint(char character, int amount)
{
    int i;

    for (i = 0; i < amount; i++)
    {
        printf("%c", character);
    }
}

/**
 * Requests user for seat number
 * @param pSeatStore Pointer to the variable to store the selected seat number
 * @param nSeats Total amount of seats inside bus
 */
void collectSeatNumber(int *pSeatStore, int nSeats)
{
    int bIsInvalid;
    do
    {
        printf("Enter seat number: ");
        scanf("%d", pSeatStore);

        bIsInvalid = *pSeatStore < 1 || *pSeatStore > nSeats;

        if (bIsInvalid)
            printf("Please enter a valid seat number, from 1 to %d.\n", nSeats);
    } while (bIsInvalid);
}

#endif