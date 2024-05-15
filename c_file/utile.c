// file utile.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> //contiene definizioni di macro per la gestione delle situazioni di errore
#include "utile.h"

#define MAXINTSIZE 13

// funzione che pulisce il buffer di input fino a quando non incontra un carattere di nuova riga o raggiunge la fine del file
void pulisci_buffer(FILE *file)
{
    int temp;
    while ((temp = getc(file)) != '\n' && temp != EOF)
        ;
}

int leggi_input_da_file(char *line, int size, FILE *file)
{
    if (fgets(line, size, file) == NULL)
    {
        pulisci_buffer(file);
        return -1; // Errore durante la lettura della riga
    }

    if (line[strlen(line) - 1] != '\n')
    {
        pulisci_buffer(file);
        return -2;
    }

    line[strcspn(line, "\n")] = '\0';

    return 0;
}

int leggi_input(char *line, int size)
{
    return leggi_input_da_file(line, size, stdin);
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

void *my_alloc(unsigned long nmemb, unsigned long size)
{
    void *p = calloc(nmemb, size);
    if (p == NULL)
    {
        perror("Allocazione fallita\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

void *my_realloc(void *p, unsigned long nmemb, unsigned long size)
{
    void *temp = realloc(p, nmemb * size);
    if (temp == NULL)
    {
        perror("Allocazione fallita\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}

char *my_strdup(char *stringa)
{
    char *temp = strdup(stringa);
    if (temp == NULL)
    {
        perror("Allocazione fallita\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}