// file data.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Definizione della struttura DataOra che rappresenta una data e un'ora
struct DataOra
{
    int anno;
    int mese;
    int giorno;
    int ora;
    int minuti;
};

// Funzione per creare una nuova data con i valori forniti
Data nuova_data(int anno, int mese, int giorno, int ora, int minuti)
{
    // Alloca memoria per una nuova struttura DataOra
    Data data = malloc(sizeof(struct DataOra));
    if (data == NULL)
    {
        // Se l'allocazione fallisce, stampa un messaggio di errore e restituisce NULL
        perror("Allocazione oggetto 'Data' fallita.");
        return NULL;
    }
    // Inizializza i campi della struttura con i valori forniti
    data->minuti = minuti;
    data->ora = ora;
    data->giorno = giorno;
    data->mese = mese;
    data->anno = anno;

    // Controlla se la data è valida
    if (!controllo_data(data))
    {
        // Se la data non è valida, stampa un messaggio, libera la memoria e restituisce NULL
        printf("Tentativo di creazione Data non valida\n");
        free(data);
        return NULL;
    }
    // Restituisce la nuova data creata
    return data;
}

// Funzione per controllare se una data è valida
int controllo_data(Data data)
{
    if (data == NULL)
    {
        // Se il puntatore alla data è NULL, stampa  un errore e restituisce -1
        printf("Errore");
        return -1;
    }
    // Controlla la validità del mese, del giorno e che l'anno non sia negativo
    if (data->mese < 1 || data->mese > 12 || data->giorno < 1 || data->giorno > 31 || data->anno < 0)
        return 0;

    // Controlla la combinazione mese-giorno
    if ((data->mese == 4 || data->mese == 6 || data->mese == 9 || data->mese == 11) && data->giorno > 30)
        return 0;

    if (data->mese == 2)
    {
        // Controlla se l'anno è bisestile
        if ((data->anno % 4 == 0 && data->anno % 100 != 0) || (data->anno % 400 == 0))
        {
            // Anno bisestile, febbraio ha al massimo 29 giorni
            if (data->giorno > 29)
                return 0;
        }
        else
        {
            // Non bisestile, febbraio ha al massimo 28 giorni
            if (data->giorno > 28)
                return 0;
        }
    }

    // Controlla la validità dell'ora e dei minuti
    if (data->ora < 0 || data->ora > 23 || data->minuti < 0 || data->minuti > 59)
        return 0;
    // Se tutte le verifiche sono passate, la data è valida
    return 1;
}

// Funzione utile per confrontare due interi
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

// Funzione per confrontare due Data
int confronta_date(Data data1, Data data2)
{
    // Confronta l'anno
    int result = utile_data(data1->anno, data2->anno);
    if (result != 0)
    {
        return result;
    }
    // Confronta il mese
    result = utile_data(data1->mese, data2->mese);
    if (result != 0)
    {
        return result;
    }
    // Confronta il giorno
    result = utile_data(data1->giorno, data2->giorno);
    if (result != 0)
    {
        return result;
    }
    // Confronta l'ora
    result = utile_data(data1->ora, data2->ora);
    if (result != 0)
    {
        return result;
    }
    // Confronta i minuti
    return utile_data(data1->minuti, data2->minuti);
}

// Funzione per leggere una data dall'input dell'utente
Data input_data(void)
{
    char temp[101] = {0};       // Buffer per memorizzare l'input
    if (leggi_input(temp, 101)) // Legge l'input
    {
        return NULL; // Restituisce NULL se la lettura fallisce
    }

    int giorno = 0;
    int mese = 0;
    int anno = 0;
    int ora = 0;
    int minuti = 0;

    // Analizza l'input per estrarre giorno, mese, anno, ora e minuti
    if (sscanf(temp, "%d/%d/%d %d:%d", &giorno, &mese, &anno, &ora, &minuti) != 5)
    {
        return NULL; // restitusce NULL se l'input non è nel formato corretto
    }

    // Crea una nuova data con i valori estratti
    Data data = nuova_data(anno, mese, giorno, ora, minuti);
    return data;
}

// Funzione per stampare una data
void stampa_data(Data Data)
{
    // Stampa la data nel formato giorno/mese/anno, ora:minuti
    printf("%d/%d/%d, %02d:%02d", Data->giorno, Data->mese, Data->anno, Data->ora, Data->minuti);
}

// Funzione per salvare una data su file
void salva_data_su_file(Data data, FILE *file)
{
    if (data == NULL)
    {
        perror("Errore"); // Se il pintatore alla data è NULL, stampa un errore
        return;
    }

    if (file == NULL)
    {
        perror("Errore"); // Se il file è NULL; stampa un errore
        return;
    }

    // Scrive la data nel file nel formato giorno mese anno ora minuti
    fprintf(file, "%d %d %d %d %d\n", data->minuti, data->ora, data->giorno, data->mese, data->anno);
}

// Funzione per leggere una data da un file
Data leggi_data_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("Errore"); // Se il file è NULL, stampa un errore
        return NULL;
    }

    int giorno = 0;
    int mese = 0;
    int anno = 0;
    int ora = 0;
    int minuti = 0;
    // legge i valori della data dal file
    if (fscanf(file, "%d %d %d %d %d", &minuti, &ora, &giorno, &mese, &anno) != 5)
    {
        return NULL;
    }
    // Crea una nuova data con i valori letti dal file
    Data data = nuova_data(anno, mese, giorno, ora, minuti);

    return data;
}

// Funzione per liberare la memoria allocata per una data
void libera_data(Data Data)
{
    free(Data);
}
