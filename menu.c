#include <stdio.h>

#ifndef MENU_C
#define MENU_C

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

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void repeatPrint(char character, int amount)
{
    int i;

    for (i = 0; i < amount; i++)
    {
        printf("%c", character);
    }
}

#endif