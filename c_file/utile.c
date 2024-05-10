// file utile.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "utile.h"

#define MAXINTSIZE 13

void pulisci_buffer()
{
    int temp;
    while ((temp = getchar()) != '\n' && temp != EOF)
        ;
}

int leggi_input(char *line, int size)
{
    if (fgets(line, size, stdin) == NULL)
    {
        pulisci_buffer();
        return -1;
    }

    if (line[strlen(line) - 1] != '\n')
    {
        pulisci_buffer();
        return -2;
    }

    line[strcspn(line, "\n")] = '\0';

    return 0;
}

int leggi_intero()
{
    int choice = 0;
    char temp[MAXINTSIZE] = {0};

    if (leggi_input(temp, MAXINTSIZE))
    {
        // Error reading line
        return -1;
    }

    char *endptr = NULL;
    errno = 0;
    choice = strtol(temp, &endptr, 10);

    if ((errno == ERANGE) || (errno != 0 && choice == 0))
    {
        perror("strtol");
        // Error converting to long
        return -2;
    }

    if (endptr == temp)
    {
        // No digits found
        return -3;
    }

    return choice;
}
