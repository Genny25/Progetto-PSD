// file bst_evento.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_evento.h"

// Definizione del tipo nodo per l'albero binario di ricerca
typedef struct eventoBstNodoStruct *eventoBstNodo;

// Struttura del nodo dell'albero binario di ricerca
struct eventoBstNodoStruct
{
    Evento valore;
    eventoBstNodo genitore;
    eventoBstNodo sinistra;
    eventoBstNodo destra;
};

// Definisce la struttura dell'albero di ricerca binaria degli eventi
struct eventoBstStruct
{
    eventoBstNodo radice;
    int dimensione;
};

// Funzione per creare un nuovo albero di ricerca binario di eventi vuoto
eventoBst nuovo_evento_bst()
{
    eventoBst nuovo = my_alloc(1, sizeof(*nuovo));
    nuovo->radice = NULL;
    nuovo->dimensione = 0;
    return nuovo;
}

// Funzione per inserire un evento nell'albero binario di ricerca degli eventi
int inserisci_evento_bst(eventoBst bst, Evento evento)
{
    // Verifica che l'albero esista
    if (bst == NULL)
    {
        printf("Errore");
        return -1;
    }

    // Crea un nuovo nodo per l'evento da inserire
    eventoBstNodo nuovo = my_alloc(1, sizeof(struct eventoBstNodoStruct));

    nuovo->valore = evento;

    // Percorri l'albero per trovare la posizione corretta per inserire il nuovo evento
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

    // Inserisci il nuovo nodo nell'albero
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
    // Aggiorna la dimensione del BST
    bst->dimensione += 1;
    return 0;
}

// Funzione per cercare un nodo contenente un evento specifico
eventoBstNodo bst_cerca_evento(eventoBst bst, Evento evento)
{
    // Inizia dalla radice dell'albero
    eventoBstNodo result = bst->radice;
    // Continua a cercare finché non trova il nodo o raggiunge una foglia
    while (result != NULL && !id_uguale(evento, result->valore))
    {
        if (confronta_eventi(evento, result->valore) < 0)
        {
            result = result->sinistra; // Cerca nel sottoalbero sinistro
        }
        else
        {
            result = result->destra; // Cerca nel sottoalbero destro
        }
    }
    return result;
}

// Funzione ausiliaria per cercare nodi contenenti un evento con un ID specifico (ricorsiva)
eventoBstNodo bst_cerca_nodi_evento_by_id(eventoBstNodo nodo, int id)
{
    if (nodo == NULL)
    {
        return NULL; // Caso base: nodo nullo
    }
    // Se l'ID del nodo corrente corrisponde, restituisce il nodo
    if (prendi_id(nodo->valore) == id)
    {
        return nodo;
    }
    // Cerca ricorsivamente nei sottoalberi sinistro e destro
    eventoBstNodo temp = NULL;
    temp = bst_cerca_nodi_evento_by_id(nodo->sinistra, id);
    if (temp != NULL)
    {
        return temp;
    }
    return bst_cerca_nodi_evento_by_id(nodo->destra, id);
}

// Funzione di supporto per cercare un evento per ID nell'albero binario di ricerca degli eventi
eventoBstNodo bst_cerca_evento_by_id(eventoBst bst, int id)
{
    return bst_cerca_nodi_evento_by_id(bst->radice, id);
}

// Funzione per spostare i nodi durante la rimozione di un nodo nell'albero binario di ricerca degli eventi
void bst_shift_nodi(eventoBst bst, eventoBstNodo nodo1, eventoBstNodo nodo2)
{
    if (nodo1->genitore == NULL)
    {
        bst->radice = nodo2; // Se il nodo da spostare è la radice, aggiorna la radice
    }
    else if (nodo1 == nodo1->genitore->sinistra)
    {
        nodo1->genitore->sinistra = nodo2; // Aggiorna il figlio sinistro del genitore del nodo1
    }
    else
    {
        nodo1->genitore->destra = nodo2; // Aggiorna il figlio destro del genitore del nodo1
    }
    if (nodo2 != NULL)
    {
        nodo2->genitore = nodo1->genitore; // Aggiorna il genitore del nodo2
    }
}

// Funzione per trovare il nodo con il valore massimo in un sottoalbero
eventoBstNodo bst_massimo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    // Scorre il sottoalbero destro fino a trovare il nodo con il valore massimo
    while (nodo->destra != NULL)
    {
        nodo = nodo->destra;
    }
    return nodo;
}

// Funzione per trovare il nodo con il valore minimo in un sottoalbero
eventoBstNodo bst_minimo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }
    // Scorre il sottoalbero sinistro fino a trovare il nodo con il valore minimo
    while (nodo->sinistra != NULL)
    {
        nodo = nodo->sinistra;
    }
    return nodo;
}

// Funzione per trovare il nodo predecessore di un nodo dato
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

// Funzione per trovare il nodo successore di un nodo dato
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

// Funzione per rimuovere un nodo dall'albero
Evento bst_rimuovi_nodo(eventoBst bst, eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL; // Caso base: nodo nullo
    }

    // Caso 1: Il nodo non ha figlio sinistro
    if (nodo->sinistra == NULL)
    {
        bst_shift_nodi(bst, nodo, nodo->destra); // Sostituisci il nodo con il suo figlio destro
    }
    // Caso 2: Il nodo non ha figlio destro
    else if (nodo->destra == NULL)
    {
        bst_shift_nodi(bst, nodo, nodo->sinistra); // Sostituisci il nodo con il suo figlio sinistro
    }
    // Caso 3: Il nodo ha entrambi i figli
    else
    {
        eventoBstNodo temp = bst_successivo(nodo); // Trova il successore del nodo
        // Se il successore non è il figlio destro del nodo
        if (temp->genitore != nodo)
        {
            bst_shift_nodi(bst, temp, temp->destra); // Sostituisci il successore con il suo figlio destro
            temp->destra = nodo->destra;             // Collega il figlio destro del nodo al successore
            temp->destra->genitore = temp;           // Imposta il genitore del figlio destro
        }
        bst_shift_nodi(bst, nodo, temp); // Sostituisci il nodo con il successore
        temp->sinistra = nodo->sinistra; // Collega il figlio sinistro del nodo al successore
        temp->sinistra->genitore = temp; // Imposta il genitore del figlio sinistro
    }
    Evento valore = nodo->valore; // Salva il valore del nodo
    free(nodo);                   // Libera la memoria del nodo
    bst->dimensione--;            // Decrementa la dimensione dell'albero
    return valore;                // Restituisce il valore del nodo rimosso
}

// Funzione per rimuovere un evento specifico dall'albero
Evento bst_rimuovi_evento(eventoBst bst, Evento evento)
{
    eventoBstNodo nodo = bst_cerca_evento(bst, evento);
    return bst_rimuovi_nodo(bst, nodo);
}

// Funzione per rimuovere un evento specifico dall'albero usando l'ID
Evento bst_rimuovi_evento_by_id(eventoBst bst, int id)
{
    eventoBstNodo nodo = bst_cerca_evento_by_id(bst, id);
    return bst_rimuovi_nodo(bst, nodo);
}

// Funzione per stampare i nodi dell'albero in ordine
void stampa_evento_bst_nodi(eventoBstNodo nodo, ListaSala sala_lista)
{
    if (nodo == NULL)
    {
        return;
    }
    // Stampa ricorsivamente i sottoalberi sinistro, nodo e destro
    stampa_evento_bst_nodi(nodo->sinistra, sala_lista);
    stampa_evento(nodo->valore, sala_per_id_lista(sala_lista, prendi_evento_sala_id(nodo->valore)));
    printf("\n\n");
    stampa_evento_bst_nodi(nodo->destra, sala_lista);
}

// Funzione per stampare tutti gli eventi nell'albero binario di ricerca degli eventi
void stampa_evento_bst(eventoBst bst, ListaSala sala_lista)
{
    stampa_evento_bst_nodi(bst->radice, sala_lista);
}

// Funzione per ottenere la dimensione dell'albero (numero di nodi)
int prendi_bst_dimensione(eventoBst bst)
{
    return bst->dimensione;
}

// Funzione per ottenere un evento dall'albero usando l'ID
Evento bst_prendi_evento_by_id(eventoBst bst, int id)
{
    eventoBstNodo e = bst_cerca_evento_by_id(bst, id); // Cerca il nodo contenente l'evento con l'ID specificato
    if (e == NULL)
    {
        return NULL; // Se il nodo non è stato trovato, restituisce NULL
    }
    return e->valore; // Restituisce l'evento contenuto nel nodo trovato
}

// Funzione per salvare i nodi dell'albero su un file (ricorsiva)
void salva_evento_bst_nodi(eventoBstNodo nodo, FILE *file)
{
    if (nodo == NULL)
    {
        return; // Caso base: nodo nullo
    }

    // Salva l'evento del nodo su file
    salva_evento_su_file(nodo->valore, file);

    // Salva ricorsivamente i sottoalberi sinistro e destro
    salva_evento_bst_nodi(nodo->sinistra, file);
    salva_evento_bst_nodi(nodo->destra, file);
}

// Funzione per salvare l'intero albero su un file
void salva_evento_bst_su_file(eventoBst bst, FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL"); // Verifica che il puntatore al file non sia NULL
        return;
    }

    fprintf(file, "%zd\n", bst->dimensione); // Salva la dimensione dell'albero su file
    // Salva i nodi dell'albero su file
    salva_evento_bst_nodi(bst->radice, file);
}

// Funzione per leggere un albero da un file
eventoBst leggi_evento_bst_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL"); // Verifica che il puntatore al file non sia NULL
        return NULL;
    }

    size_t dimensione = 0;
    if (fscanf(file, "%zu\n", &dimensione) != 1) // Legge la dimensione dell'albero dal file
    {
        perror("Error reading BST dimensione");
        return NULL;
    }

    eventoBst bst = nuovo_evento_bst(); // Crea un nuovo albero vuoto

    // Legge i dati degli eventi dal file e li inserisce nell'albero
    for (size_t i = 0; i < dimensione; i++)
    {
        Evento evento = leggi_evento_da_file(file); // Legge un evento dal file
        if (evento == NULL)                         // Verifica se la lettura dell'evento ha avuto successo
        {
            perror("Error reading event data");
            libera_evento_bst(bst); // Libera la memoria dell'albero in caso di errore
            return NULL;
        }
        inserisci_evento_bst(bst, evento); // Inserisce l'evento nell'albero
    }

    return bst; // Restituisce l'albero letto dal file
}

// Funzione per liberare la memoria dei nodi dell'albero (ricorsiva)
void libera_evento_bst_nodi(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return;
    }

    // Libera ricorsivamente i sottoalberi sinistro e destro
    libera_evento_bst_nodi(nodo->sinistra);
    libera_evento_bst_nodi(nodo->destra);

    libera_evento(nodo->valore);
    free(nodo);
}

// Funzione per liberare la memoria dell'intero albero
void libera_evento_bst(eventoBst bst)
{
    if (bst == NULL)
    {
        return;
    }
    libera_evento_bst_nodi(bst->radice);
    free(bst);
}
