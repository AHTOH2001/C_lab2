#include <stdio.h>
#include <conio.h>
#include "header.h"

int main()
{
    char c = '*';
    printf("Choose problem(0 to exit):\n");
    printf("1. problem 1 variant 18\n");
    printf("2. problem 2 variant 18\n");
    while (c <= '0' || c >= '3')
    {
        c = getch();
        if (c == '1')
            problem1();
        else if (c == '2')
            problem2();
        else if (c == '0')
        {
            printf("Successfully exit\n");
            break;
        }
        else
            printf("Error, try again\n");
    }
    getch();
    return 0;
}