/**
 * @brief Prints the menu
 *
 * @param nTime Current time (24hr format)
 */
void printMenu(int nTime)
{
    printf("Welcome, Teller!\n");
    printf("It is %d:%02d\n", nTime / 100, nTime % 100);
    printf("1 - Book a Ticket\n");
    printf("2 - Cancel a Ticket\n");
    printf("3 - Display Timetable\n");
    printf("4 - Update Current Time\n");
    printf("5 - Exit\n");
    printf("6 - Change Bus Configuration\n");
    printf("7 - Print all seats\n");
    printf("Select your choice: ");
}

/**
 * @brief Clears the console
 */
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}