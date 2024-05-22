// file bst_evento.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_evento.h"

typedef struct eventoBstNodoStruct *eventoBstNodo;

struct eventoBstNodoStruct
{
    Evento valore;
    eventoBstNodo genitore;
    eventoBstNodo sinistra;
    eventoBstNodo destra;
};

struct eventoBstStruct
{
    eventoBstNodo radice;
    int dimensione;
};

eventoBst nuovo_evento_bst()
{
    eventoBst nuovo = malloc(sizeof(*nuovo));
    if (nuovo == NULL)
    {
        return NULL;
    }
    nuovo->radice = NULL;
    nuovo->dimensione = 0;
    return nuovo;
}

int inserisci_evento_bst(eventoBst bst, Evento evento)
{
    if (bst == NULL)
    {
        printf("Errore");
        return -1;
    }

    eventoBstNodo nuovo = calloc(1, sizeof(struct eventoBstNodoStruct));
    if (nuovo == NULL)
    {
        printf("Errore");
        return -1;
    }

    nuovo->valore = evento;

    eventoBstNodo genitore = NULL;

    eventoBstNodo temp = bst->radice;
    while (temp != NULL)
    {
        genitore = temp;
        if (confronta_eventi(nuovo->valore, genitore->valore) < 0)
        {
            temp = temp->sinistra;
        }
        else
        {
            temp = temp->destra;
        }
    }

    nuovo->genitore = genitore;

    if (genitore == NULL)
    {
        bst->radice = nuovo;
    }
    else if (confronta_eventi(nuovo->valore, genitore->valore) < 0)
    {
        genitore->sinistra = nuovo;
    }
    else
    {
        genitore->destra = nuovo;
    }
    bst->dimensione += 1;
    return 0;
}

eventoBstNodo bst_cerca_evento(eventoBst bst, Evento evento)
{
    eventoBstNodo result = bst->radice;
    while (result != NULL && !id_uguale(evento, result->valore))
    {
        if (confronta_eventi(evento, result->valore) < 0)
        {
            result = result->sinistra;
        }
        else
        {
            result = result->destra;
        }
    }
    return result;
}

eventoBstNodo bst_cerca_nodi_evento_by_id(eventoBstNodo nodo, int id)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    if (prendi_id(nodo->valore) == id)
    {
        return nodo;
    }
    eventoBstNodo temp = NULL;
    temp = bst_cerca_nodi_evento_by_id(nodo->sinistra, id);
    if (temp != NULL)
    {
        return temp;
    }
    return bst_cerca_nodi_evento_by_id(nodo->destra, id);
}

eventoBstNodo bst_cerca_evento_by_id(eventoBst bst, int id)
{
    return bst_cerca_nodi_evento_by_id(bst->radice, id);
}

void bst_shift_nodi(eventoBst bst, eventoBstNodo nodo1, eventoBstNodo nodo2)
{
    if (nodo1->genitore == NULL)
    {
        bst->radice = nodo2;
    }
    else if (nodo1 == nodo1->genitore->sinistra)
    {
        nodo1->genitore->sinistra = nodo2;
    }
    else
    {
        nodo1->genitore->destra = nodo2;
    }
    if (nodo2 != NULL)
    {
        nodo2->genitore = nodo1->genitore;
    }
}

eventoBstNodo bst_massimo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    while (nodo->destra != NULL)
    {
        nodo = nodo->destra;
    }
    return nodo;
}

eventoBstNodo bst_minimo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    while (nodo->sinistra != NULL)
    {
        nodo = nodo->sinistra;
    }
    return nodo;
}

eventoBstNodo bst_precedente(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    if (nodo->sinistra != NULL)
    {
        return bst_massimo(nodo->sinistra);
    }
    eventoBstNodo res = nodo->genitore;
    while (res != NULL && nodo == res->sinistra)
    {
        nodo = res;
        res = res->genitore;
    }
    return res;
}

eventoBstNodo bst_successivo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    if (nodo->destra != NULL)
    {
        return bst_minimo(nodo->destra);
    }
    eventoBstNodo res = nodo->genitore;
    while (res != NULL && nodo == res->destra)
    {
        nodo = res;
        res = res->genitore;
    }
    return res;
}

Evento bst_rimuovi_nodo(eventoBst bst, eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }

    if (nodo->sinistra == NULL)
    {
        bst_shift_nodi(bst, nodo, nodo->destra);
    }
    else if (nodo->destra == NULL)
    {
        bst_shift_nodi(bst, nodo, nodo->sinistra);
    }
    else
    {
        eventoBstNodo temp = bst_successivo(nodo);
        if (temp->genitore != nodo)
        {
            bst_shift_nodi(bst, temp, temp->destra);
            temp->destra = nodo->destra;
            temp->destra->genitore = temp;
        }
        bst_shift_nodi(bst, nodo, temp);
        temp->sinistra = nodo->sinistra;
        temp->sinistra->genitore = temp;
    }
    Evento valore = nodo->valore;
    free(nodo);
    bst->dimensione--;
    return valore;
}

Evento bst_rimuovi_evento(eventoBst bst, Evento evento)
{
    eventoBstNodo nodo = bst_cerca_evento(bst, evento);
    return bst_rimuovi_nodo(bst, nodo);
}

Evento bst_rimuovi_evento_by_id(eventoBst bst, int id)
{
    eventoBstNodo nodo = bst_cerca_evento_by_id(bst, id);
    return bst_rimuovi_nodo(bst, nodo);
}

void stampa_evento_bst_nodi(eventoBstNodo nodo, ListaSala sala_lista)
{
    if (nodo == NULL)
    {
        return;
    }
    stampa_evento_bst_nodi(nodo->sinistra, sala_lista);
    stampa_evento(nodo->valore, sala_per_id_lista(sala_lista, prendi_evento_sala_id(nodo->valore)));
    printf("\n\n");
    stampa_evento_bst_nodi(nodo->destra, sala_lista);
}

void stampa_evento_bst(eventoBst bst, ListaSala sala_lista)
{
    stampa_evento_bst_nodi(bst->radice, sala_lista);
}

int prendi_bst_dimensione(eventoBst bst)
{
    return bst->dimensione;
}

Evento bst_prendi_evento_by_id(eventoBst bst, int id)
{
    eventoBstNodo e = bst_cerca_evento_by_id(bst, id);
    if (e == NULL)
    {
        return NULL;
    }
    return e->valore;
}

void libera_evento_bst_nodi(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return;
    }

    libera_evento_bst_nodi(nodo->sinistra);
    libera_evento_bst_nodi(nodo->destra);

    libera_evento(nodo->valore);
    free(nodo);
}

void libera_evento_bst(eventoBst bst)
{
    if (bst == NULL)
    {
        return;
    }
    libera_evento_bst_nodi(bst->radice);
    free(bst);
}

void salva_evento_bst_nodi(eventoBstNodo nodo, FILE *file)
{
    if (nodo == NULL)
    {
        return;
    }

    // Save current nodo's event to the file
    salva_evento_su_file(nodo->valore, file);

    salva_evento_bst_nodi(nodo->sinistra, file);
    salva_evento_bst_nodi(nodo->destra, file);
}

void salva_evento_bst_su_file(eventoBst bst, FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return;
    }

    fprintf(file, "%zd\n", bst->dimensione);
    // Traverse the BST and save each event to the file
    salva_evento_bst_nodi(bst->radice, file);
}

// Function to read an event BST from a file
eventoBst leggi_evento_bst_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return NULL;
    }

    size_t dimensione = 0;
    if (fscanf(file, "%zu\n", &dimensione) != 1)
    {
        perror("Error reading BST dimensione");
        return NULL;
    }

    eventoBst bst = nuovo_evento_bst(); // Create a nuovo empty BST

    // Read event data from the file and insert into the BST
    for (size_t i = 0; i < dimensione; i++)
    {
        Evento evento = leggi_evento_da_file(file);
        if (evento == NULL)
        {
            perror("Error reading event data");
            libera_evento_bst(bst);
            return NULL;
        }
        inserisci_evento_bst(bst, evento);
    }

    return bst;
}