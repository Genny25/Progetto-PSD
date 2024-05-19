// file sala.c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"

// Definizione della struttura StrucSala che rappresenta una sala
struct StructSala
{
    int id;      // ID della sala
    char *nome;  // Nome della sala
};

// Funzione per creare una nuova sala con il nome e l'ID forniti
sala nuova_sala(char *nome, int id)
{
    // Alloca memoria per una nuova struttura sala
    sala s = my_alloc(1, sizeof(*s));
    // Duplica il nome fornito e assegna l'ID
    s->nome = my_strdup(nome);
    s->id = id;

    // Restituisce la nuova sala creata
    return s;
}

// Funzione per confrontare due sale
bool eq_sale(sala s1, sala s2)
{
    // Se i puntatori sono uguali, le sale sono uguali
    if (s1 == s2)
    {
        return true;
    }
    // Controlla se entrambe le sale non sono NULL e se hanno lo stesso ID
    return s1 != NULL && s2 != NULL && s1->id == s2->id;
}

// Funzione per inserire i dati di una sala dall'input dell'utente
sala input_sala(int id)
{
    char nome[101] = {0};
    // Chiede all'utente di inserire il nome della sala
    while(1){
        char temp[101] = {0};    // Buffer per memorizzare l'input
        printf("Inserisci nome sala [Max 100 caratteri]: ");
        if (leggi_input(temp, 101)) // Legge l'input dall'utente
        {
            printf("Nome troppo lungo");
            continue; //riprova se il nome è troppo lungo
        }
        sscanf(temp,"%[^\n]",nome); //copia l'input in nome escludendo '\n'
        if(strlen(nome) == 0) //controlla se l'input è vuoto
        {
            continue; //riprova se l'input è vuoto
        }
        break; //esce dal ciclo se l'input è valido
    }
    
    // Crea una nuova sala con il nome inserito e l'ID fornito
    sala s = nuova_sala(nome, id);
    return s;
}

// Funzione per ottenere il nome di una sala
char *get_sala_nome(sala s)
{
    return s->nome; // Restituisce il nome della sala
}

// Funzione per ottenere l'ID di una sala
int get_sala_id(sala s)
{
    return s->id; // Restituisce l'ID della sala
}

// Funzione per stampare il nome di una sala
void stampa_sala(sala s)
{
    printf("%s", s->nome); // Stampa il nome della sala
}

// Funzione per liberare la memoria allocata per una sala
void free_sala(sala s)
{
    free(s->nome); // Libera la memoria allocata per il nome
    free(s); // Libera la memoria allocata per la struttura sala
}

// Funzione per salvare una struttura sala su un file
void salva_sala_su_file(sala s, FILE *file)
{
    if (s == NULL || file == NULL)
    {
        return; // Se la sala o il file sono NULL, esce dalla funzione
    }

    // Scrive l'ID e il nome della sala nel file
    fprintf(file, "%d\n", s->id);   // Write room ID
    fprintf(file, "%s\n", s->nome); // Write room name
}

// Funzione per leggere una struttura sala da un file
sala leggi_sala_da_file(FILE *file)
{
    if (file == NULL)
    {
        return NULL; // Se il file è NULL, restituisce NULL
    }

    // Legge l'ID della sala dal file
    int id;
    if (fscanf(file, "%d", &id) != 1)
    {
        pulisci_buffer(file); // Pulisce il buffer del file se la lettura fallisce 
        return NULL;
    }

    pulisci_buffer(file); // Pulisce il buffer del file

    // Legge il nome della sala dal file
    char nome[102];
    if (leggi_input_da_file(nome, 102, file) != 0)
    {
        return NULL; // Restituisce NULL se la lettura del nome fallisce 
    }

    // Crea e restituisce una nuova sala con i valori letti dal file
    return nuova_sala(nome, id);
}
