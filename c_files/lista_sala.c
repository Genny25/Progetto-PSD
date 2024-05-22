// file lista_sala.c

#include <stdio.h>
#include <stdlib.h>
#include "lista_sala.h"

#define CAPACITA_INIZIALE 16 // Capacità iniziale dell'array dinamico
#define FATTOR_DI_CRESCITA 2 // Fattore di crescita dell'array dinamico

// Struct che rappresenta una lista di sale (ListaSalaStruct)
struct ListaSalaStruct
{
    Sala *array;    // Puntatore ad un array di sale
    int capacita;   // Capacità corrente della lista
    int dimensione; // Numero corrente di sale nella lista
};

// Funzione per creare una nuova lista di sale vuota
ListaSala nuova_lista_sala(void)
{
    ListaSala nuova_lista = my_alloc(1, sizeof(*nuova_lista));      // Alloca memoria per una nuova lista di sale (nuova_lista)
    nuova_lista->array = my_alloc(CAPACITA_INIZIALE, sizeof(Sala)); // Alloca memoria per l'array iniziale di sale
    nuova_lista->capacita = CAPACITA_INIZIALE;
    nuova_lista->dimensione = 0;
    return nuova_lista;
}

// Funzione per aumentare la capacità di una lista di sale
void aumenta_capacita_lista_sala(ListaSala lista)
{
    lista->capacita *= FATTOR_DI_CRESCITA;                                  // Raddoppia la capacità corrente della lista
    lista->array = my_realloc(lista->array, lista->capacita, sizeof(Sala)); // Rialloca memoria per l'array di sale con la nuova capacità
}

// Funzione per verificare se una lista di sale è vuota
bool lista_sala_vuota(ListaSala lista)
{
    // Restituisce true se la lista è NULL, non ha sale o il suo array è NULL
    return lista == NULL || lista->dimensione == 0 || lista->array == NULL;
}

// Funzione per aggiungere una sala ad una lista di sale
void aggiungi_sala_lista(ListaSala lista, Sala s)
{
    // Se la capacità della lista è uguale al numero corrente di sale
    if (lista->capacita == lista->dimensione)
    {
        aumenta_capacita_lista_sala(lista); // Aumenta la capacità della lista
    }
    lista->array[lista->dimensione] = s; // Aggiunge la sala all'array di sale alla posizione corrente della dimensione
    lista->dimensione += 1;              // Incrementa il numero di sale nella lista
}

// Funzione per ottenere l'ultima sala di una lista di sale
Sala sala_fine_lista(ListaSala lista)
{
    if (lista_sala_vuota(lista))
    {
        return NULL;
    }
    lista->dimensione -= 1;                 // Decrementa il numero di sale nella lista
    return lista->array[lista->dimensione]; // Restituisce l'ultima sala nell'array di sale
}

// Funzione per ottenere la prima sala nella lista
Sala prendi_prima_sala_lista(ListaSala lista)
{
    return sala_in_posizione_lista(lista, 0);
}

// Funzione per ottenere la dimensione della lista di sale
int prendi_dimensione_lista_sala(ListaSala lista)
{
    return lista->dimensione;
}

// Funzione per ottenere la posizione di una sala in una lista di sale
int prendi_posizione_sala_lista(ListaSala lista, Sala da_cercare)
{
    for (int i = 0; i < lista->dimensione; i++)
    {
        // Se la sala corrente è uguale alla sala cercata
        if (sale_uguali(lista->array[i], da_cercare))
        {
            return i; // Restituisce la posizione della sala nell'array
        }
    }
    return -1;
}

// Funzione per ottenere una sala in una posizione specifica nella lista
Sala sala_in_posizione_lista(ListaSala lista, int posizione)
{
    // Verifica se la posizione è valida
    if (posizione >= lista->dimensione || posizione < 0)
    {
        return NULL;
    }
    // Restituisce la sala alla posizione specificata
    return lista->array[posizione];
}

// Funzione per ottenere una sala dalla lista per ID
Sala sala_per_id_lista(ListaSala lista, int id_sala)
{
    if (lista == NULL)
    {
        return NULL;
    }
    // Cerca la sala nella lista confrontando gli ID
    for (int i = 0; i < lista->dimensione; i++)
    {
        Sala sala_corrente = lista->array[i];
        if (prendi_sala_id(sala_corrente) == id_sala)
        {
            return sala_corrente;
        }
    }
    return NULL; // Restituisce NULL se la sala non è trovata
}

// Funzione per stampare tutte le sale nella lista
void stampa_lista_sala(ListaSala lista)
{
    for (int i = 0; i < lista->dimensione; i++)
    {
        printf("[Sala %d]\n"
               "Nome:> ",
               i + 1);
        stampa_sala(lista->array[i]);
        puts(""); // Aggiunge una nuova riga
    }
}

// Funzione per salvare la lista di sale su un file
void salva_lista_sala_su_file(ListaSala lista, FILE *file)
{
    if (file == NULL)
    {
        perror("Puntatore al file è NULL");
        return;
    }

    // Scrive la dimensione della lista nel file
    fprintf(file, "%d\n", lista->dimensione);

    // Salva ogni sala nella lista sul file
    for (int i = 0; i < lista->dimensione; i++)
    {
        salva_sala_su_file(lista->array[i], file);
    }
}

// Funzione per leggere una lista di sale da un file
ListaSala leggi_lista_sala_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("Puntatore al file è NULL");
        return NULL; // restituisce NULL se il puntatore al file è NULL
    }

    int numero_sale = 0;

    // Legge il numero di sale nel file
    if (fscanf(file, "%d", &numero_sale) != 1)
    {
        pulisci_buffer(file); // Pulisce il buffer del file se la lettura fallisce
        return NULL;          // Restituisce NULL se la lettura fallisce
    }

    ListaSala lista = nuova_lista_sala();
    if (lista == NULL)
    {
        return NULL;
    }

    // Legge ogni sala dal file e la aggiunge alla lista
    for (int i = 0; i < numero_sale; i++)
    {
        Sala s = leggi_sala_da_file(file);
        if (s == NULL)
        {
            libera_lista_sala(lista);
            return NULL;
        }
        aggiungi_sala_lista(lista, s);
    }

    return lista;
}

// Funzione per liberare la memoria allocata per la lista di sale
void libera_lista_sala(ListaSala lista)
{
    // Libera la memoria allocata per ogni sala nella lista
    for (int i = 0; i < lista->dimensione; i++)
    {
        libera_sala(lista->array[i]);
    }
    // Libera la memoria allocata per l'array di sale e la struttura ListaSala
    free(lista->array);
    free(lista);
}
