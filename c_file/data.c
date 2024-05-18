// file data.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Definizione della struttura DateTime che rappresenta una data e un'ora
struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
};

// Funzione per creare una nuova data con i valori forniti
Date nuova_data(int year, int month, int day, int hour, int minutes)
{
    // Alloca memoria per una nuova struttura DateTime
    Date date = malloc(sizeof(struct DateTime));
    if (date == NULL)
    {
        // Se l'allocazione fallisce, stampa un messaggio di errore e restituisce NULL
        perror("Allocazione oggetto 'Date' fallita.");
        return NULL;
    }
    // Inizializza i campi della struttura con i valori forniti
    date->minutes = minutes;
    date->hour = hour;
    date->day = day;
    date->month = month;
    date->year = year;

    // Controlla se la data è valida
    if (!controllo_data(date))
    {
        // Se la data non è valida, stampa un messaggio, libera la memoria e restituisce NULL
        printf("Tentativo di creazione date non valida\n");
        free(date);
        return NULL;
    }
    // Restituisce la nuova data creata 
    return date;
}

/7 Funzione per controllare se una data è valida
int controllo_data(Date date)
{
    if (date == NULL)
    {
        // Se il puntatore alla data è NULL, stampa  un errore e restituisce -1
        printf("Errore");
        return -1;
    }
    // Controlla la validità del mese e del giorno
    if (date->month < 1 || date->month > 12 || date->day < 1 || date->day > 31)
        return 0;

    // Controlla la combinazione mese-giorno
    if ((date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) && date->day > 30)
        return 0;

    if (date->month == 2)
    {
        // Controlla se l'anno è bisestile
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0))
        {
            // Anno bisestile, febbraio ha al massimo 29 giorni
            if (date->day > 29)
                return 0;
        }
        else
        {
            // Non bisestile, febbraio ha al massimo 28 giorni
            if (date->day > 28)
                return 0;
        }
    }

    // Controlla la validità dell'ora e dei minuti
    if (date->hour < 0 || date->hour > 23 || date->minutes < 0 || date->minutes > 59)
        return 0;
    // Se tutte le verifiche sono passate, la data è valida
    return 1;
}

int utile_data(int d1, int d2)
{
    if (d1 < d2)
    {
        return -1;
    }
    if (d1 == d2)
    {
        return 0;
    }
    return 1;
}

int confronta_date(Date data1, Date data2)
{
    // Compare 'year'
    int result = utile_data(data1->year, data2->year);
    if (result != 0)
    {
        return result;
    }
    // Compare 'month'
    result = utile_data(data1->month, data2->month);
    if (result != 0)
    {
        return result;
    }
    // Compare 'day'
    result = utile_data(data1->day, data2->day);
    if (result != 0)
    {
        return result;
    }
    // Compare 'hour'
    result = utile_data(data1->hour, data2->hour);
    if (result != 0)
    {
        return result;
    }
    // Compare 'minutes'
    return utile_data(data1->minutes, data2->minutes);
}

Date input_data(void)
{
    char temp[101] = {0};
    if (leggi_input(temp, 101))
    {
        return NULL;
    }

    int day = 0;
    int month = 0;
    int year = 0;
    int hour = 0;
    int minutes = 0;

    if (sscanf(temp, "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes) != 5)
    {
        return NULL;
    }

    Date date = nuova_data(year, month, day, hour, minutes);
    return date;
}

void stampa_data(Date date)
{
    printf("%d/%d/%d, %02d:%02d", date->day, date->month, date->year, date->hour, date->minutes);
}

void free_date(Date date)
{
    free(date);
}

void salva_data_su_file(Date data, FILE *file)
{
    if (data == NULL)
    {
        perror("Errore");
        return;
    }

    if (file == NULL)
    {
        perror("Errore");
        return;
    }

    fprintf(file, "%d %d %d %d %d\n", data->day, data->month, data->year, data->hour, data->minutes);
}

Date leggi_data_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("Errore");
        return NULL;
    }

    int day = 0;
    int month = 0;
    int year = 0;
    int hour = 0;
    int minutes = 0;

    if (fscanf(file, "%d %d %d %d %d", &day, &month, &year, &hour, &minutes) != 5)
    {
        pulisci_buffer(file);
        return NULL;
    }

    pulisci_buffer(file);

    Date data = nuova_data(year, month, day, hour, minutes);

    return data;
}
