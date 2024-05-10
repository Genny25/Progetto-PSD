// file data.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utile.h"
#include "data.h"  // Include dichiarazioni per questo modulo

// Definizione della struttura DateTime per rappresentare date e orari
struct DateTime 
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
};

// Funzione per creare una nuova data
Date nuova_data(int year, int month, int day, int hour, int minutes)
{
    // Alloca memoria per la struttura DateTime
    Date date = malloc(sizeof(struct DateTime));
    // Controlla se l'allocazione ha avuto successo
    if (date == NULL)
    {
        perror("Allocazione oggetto 'Date' fallita.");
        return NULL;
    }
    // Inizializza i campi della data con i valori forniti
    date->minutes = minutes;
    date->hour = hour;
    date->day = day;
    date->month = month;
    date->year = year;

    // Controlla se la data è valida
    if (!controllo_data(date))
    {
        printf("Tentativo di creazione date non valida\n");
        free(date);
        return NULL;
    }
    return date;
}

// Funzione per controllare la validità di una data ritorna -1 in caso di errore, 0 se la data non è valida e 1 se la data è valida
int controllo_data(Date date)
{
    if (date == NULL)
    {
        printf("Errore");
        return -1;
    }
    // controllo per mesi e gionri
    if (date->month < 1 || date->month > 12 || date->day < 1 || date->day > 31)
        return 0;

    // controllo per i mesi di 30 giorni 
    if ((date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) && date->day > 30)
        return 0;
    
    // controllo per anno bisestile 
    if (date->month == 2)
    {
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0))
        { 
            if (date->day > 29)
                return 0;
        }
        else
        {
            if (date->day > 28)
                return 0;
        }
    }

    // controllo ora e minuti
    if (date->hour < 0 || date->hour > 23 || date->minutes < 0 || date->minutes > 59)
        return 0;

    return 1;
}

// Funzione di utilità per confrontare due date
int utile_data(int d1, int d2)
{
    if (d1 < d2)
    {
        return -1; // d1 precede d2
    }
    if (d1 == d2)
    {
        return 0; // d1 è uguale a d2
    }
    return 1; // d1 segue d2
}

// Funzione per confrontare due date
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

// Funzioni getter per ottenere le componenti di una data
int get_hour(Date date)
{
    if (date == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'get_hour'.");
        return -1; // Ritorna -1 in caso di errore
    }
    return date->hour; // Ritorna l'ora della data
}

int get_minutes(Date date)
{
    if (date == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'get_minutes'.");
        return -1;  // Ritorna -1 in caso di errore
    }
    return date->minutes; // Ritorna i minuti della data
} 

int get_day(Date date)
{
    if (date == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'get_day'.");
        return -1;  // Ritorna -1 in caso di errore
    }
    return date->day; // Ritorna il giorno della data
}

int get_month(Date date)
{
    if (date == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'get_month'.");
        return -1;  // Ritorna -1 in caso di errore
    }
    return date->month; // Ritorna il mese della data
}

int get_year(Date date)
{
    if (date == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'get_year'.");
        return -1;  // Ritorna -1 in caso di errore
    }
    return date->year; // Ritorna l'anno della data
}

// Funzione per inserire una data da input
Date input_data(void)
{
    char temp[101] = {0}; // Legge l'input dall'utente
    if (leggi_input(temp, 101))
    {
        return NULL; // Ritorna NULL se c'è un errore nell'input
    }

    int day = 0;
    int month = 0;
    int year = 0;
    int hour = 0;
    int minutes = 0;

    //Trasforma l'input nel formato "giorno/mese/anno ora:minuti"
    if (sscanf(temp, "%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes) != 5)
    {
        return NULL;
    }

    // Crea una nuova data con i valori trasformati
    Date date = nuova_data(year, month, day, hour, minutes);
    return date; // Ritorna la nuova data
}

// Funzione per stampare una data
void stampa_data(Date date)
{
    printf("%d/%d/%d, %02d:%02d", date->day, date->month, date->year, date->hour, date->minutes);
}

// Funzione per liberare la memoria allocata per una data
void free_date(Date date)
{
    free(date);
}
