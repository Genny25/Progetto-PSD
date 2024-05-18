// file utile.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // Contiene definizioni di macro per la gestione delle situazioni di errore
#include "utile.h"

#define MAXINTSIZE 13

// Funzione che pulisce il buffer di input fino a quando non incontra un carattere di nuova riga o raggiunge la fine del file
void pulisci_buffer(FILE *file)
{
    int temp;
    while ((temp = getc(file)) != '\n' && temp != EOF);
}

// Funzione per leggere una riga da file
int leggi_input_da_file(char *line, int size, FILE *file)
{
    if (fgets(line, size, file) == NULL)
    {
        pulisci_buffer(file); // Se ftgets fallisce pulisce il buffer per evitare problemi di input successivi
        return -1; // Errore durante la lettura della riga
    }

    if (line[strlen(line) - 1] != '\n')
    {
        pulisci_buffer(file); // Se la riga è troppo lunga, pulisce il buffer per evitare problemi di input successivi
        return -2; // Errore, la riga è troppo lunga per il buffer fornito
    }

    line[strcspn(line, "\n")] = '\0'; // Rimuove il carattere di nuova riga dalla fine della riga letta e lo sostituisce con '\0'

    return 0; // Lettura della riga avvenuta con successo
}
}

// Funzione per leggere una riga da stdin
int leggi_input(char *line, int size)
{
    return leggi_input_da_file(line, size, stdin);
}

// Funzione per leggere un intero da stdin
int leggi_intero()
{
    int choice = 0;
    char temp[MAXINTSIZE] = {0};

    if (leggi_input(temp, MAXINTSIZE))
    {
        // Errore durante la lettura della riga
        return -1;
    }

    char *endptr = NULL;
    errno = 0;
    choice = strtol(temp, &endptr, 10); // Converte la stringa in un intero

    if ((errno == ERANGE) || (errno != 0 && choice == 0))
    {
        perror("strtol");
        // Errore nella conversione della stringa in un intero
        return -2;
    }

    if (endptr == temp)
    {
        // Nessun numero trovato nella stringa
        return -3;
    }

    return choice; // Restituisce l'intero letto con successo
}

// Funzione per l'allocazione di memoria
void *my_alloc(unsigned long nmemb, unsigned long size)
{
    void *p = calloc(nmemb, size); // Alloca la memoria
    if (p == NULL)
    {
        perror("Allocazione fallita\n"); // Stampa un messaggio di errore in caso di fallimento
        exit(EXIT_FAILURE); // Termina il programma in caso di fallimento
    }
    return p; // Restituisce il puntatore alla memoria allocata
}

// Funzione per la  reallocazione di memoria
void *my_realloc(void *p, unsigned long nmemb, unsigned long size)
{
    void *temp = realloc(p, nmemb * size); // Rialloca la memoria
    if (temp == NULL)
    {
        // direi dimodificare con reallocazione fallita
        perror("Allocazione fallita\n"); // Stampa un messaggio di errore in caso di fallimento
        exit(EXIT_FAILURE); // Termina il programma in caso di fallimento
    }
    return temp; // Restituisce il puntatore alla memoria riallocata
}
}

// Funzione per duplicare una stringa
char *my_strdup(char *stringa)
{
    char *temp = strdup(stringa); // Duplica la stringa
    if (temp == NULL)
    {
        perror("Allocazione fallita\n"); // Stampa un messaggio di errore in caso di fallimento
        exit(EXIT_FAILURE); // Termina il programma in caso di fallimento
    }
    return temp; // Restituisce il puntatore alla stringa duplicata
}
