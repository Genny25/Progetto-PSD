// file lista_sala.c

#include <stdio.h>
#include <stdlib.h>
#include "lista_sala.h"

// Definizione della capacità iniziale e del fattore di crescita della lita
#define INIZIALE_CAPACITA 16
#define FATTOR_DI_CRESCITA 2

// Struttura ListaSalaStruct che rappresenta una lista di sale
struct ListaSalaStruct
{
    sala *array;     // Puntatore all'array di sale
    int capacita;    // Capacità attuale dell'array
    int dimensione;  // Numero di sale presenti nella lista
};

// Funzione per aumentare la capacità della lista di sale
void aumenta_capacita_lista_sala(listaSala lista)
{
    // Raddoppia la capacità attuale della lista
    lista->capacita *= FATTOR_DI_CRESCITA;
    // Rialloca memoria per l'array con la nuova capacità
    lista->array = my_realloc(lista->array, lista->capacita, sizeof(sala));
}

// Funzione per creare uan nuova lista di sale
listaSala nuova_lista_sala(void)
{
    // Alloca meoria per una nuova struttura listaSale
    listaSala nuova_lista = my_alloc(1, sizeof(*nuova_lista));
    // Alloca memoria per l'array di sale con la capacità iniziale
    nuova_lista->array = my_alloc(INIZIALE_CAPACITA, sizeof(sala));
    nuova_lista->capacita = INIZIALE_CAPACITA;
    nuova_lista->dimensione = 0;
    return nuova_lista;
}

// Funzione per verificare se la lista di sale è vuota
bool lista_sala_vuota(listaSala lista)
{
    return lista == NULL || lista->dimensione == 0 || lista->array == NULL;
}

// Funzione per aggiungere una sala alla lista
void aggiungi_sala_lista(listaSala lista, sala s)
{
    // Se la lista ha raggiunto la capacità massima, aumenta la capacità
    if (lista->capacita == lista->dimensione)
    {
        aumenta_capacita_lista_sala(lista);
    }
    // Aggiunge la sala alla fine della lista
    lista->array[lista->dimensione] = s;
    lista->dimensione += 1;
}

// Funzione per ottenere l'ultima sala della lista
sala sala_fine_lista(listaSala lista)
{
    if (lista_sala_vuota(lista))
    {
        return NULL;
    }
    // Riduce la dimensione della lista e restituisce l'ultima sala
    lista->dimensione -= 1;
    return lista->array[lista->dimensione];
}

// Funzione per ottenere la prima sala nella lista
sala get_prima_sala_lista(listaSala lista)
{
    return sala_in_posizione_lista(lista, 0);
}

// Funzione per ottenere la dimensione della lista di sale
int get_dimensione_lista_sala(listaSala lista)
{
    return lista->dimensione;
}

// Funzione per ottenere la posizione di una sala specifica nella lista 
int get_posizione_sala_lista(listaSala lista, sala da_cercare)
{
    // Cerca la sala nella lista confrontando gli ID
    for (int i = 0; i < lista->dimensione; i++)
    {
        if (eq_sale(lista->array[i], da_cercare))
        {
            return i;
        }
    }
    return -1; // Restituisce -1 se la sala non é stata trovata
}

// Funzione per ottenere una sala in una posizione specifica nella lista
sala sala_in_posizione_lista(listaSala lista, int posizione)
{
    // Verifica se la posizione è valida
    if (posizione >= lista->dimensione || posizione < 0)
    {
        return NULL;
    }
    // Restituisce la sala alla posizione specificata
    return lista->array[posizione];
}

void stampa_lista_sala(listaSala lista)
{
    for (int i = 0; i < lista->dimensione; i++)
    {
        printf("[Sala %d]\n"
               "Nome: ",
               i + 1);
        stampa_sala(lista->array[i]);
        puts("");
    }
}

void free_lista_sala(listaSala lista)
{
    for (int i = 0; i < lista->dimensione; i++)
    {
        free_sala(lista->array[i]);
    }
    free(lista->array);
    free(lista);
}

void salva_lista_sala_su_file(listaSala lista, FILE *file)
{
    if (file == NULL)
    {
        perror("Puntatore al file è NULL");
        return;
    }

    fprintf(file, "%d\n", lista->dimensione);

    for (int i = 0; i < lista->dimensione; i++)
    {
        salva_sala_su_file(lista->array[i], file);
    }
}

listaSala leggi_lista_sala_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("Puntatore al file è NULL");
        return NULL;
    }

    int numero_sale = 0;

    if (fscanf(file, "%d", &numero_sale) != 1)
    {
        pulisci_buffer(file);
        return NULL;
    }

    listaSala lista = nuova_lista_sala();
    if (lista == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < numero_sale; i++)
    {
        sala s = leggi_sala_da_file(file);
        if (s == NULL)
        {
            free_lista_sala(lista);
            return NULL;
        }
        aggiungi_sala_lista(lista, s);
    }

    return lista;
}

sala sala_per_id_lista(listaSala lista, int id_sala)
{
    if (lista == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < lista->dimensione; i++)
    {
        sala sala_corrente = lista->array[i];
        if (get_sala_id(sala_corrente) == id_sala)
        {
            return sala_corrente;
        }
    }
    return NULL;
}
