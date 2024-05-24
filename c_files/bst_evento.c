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
    Evento valore;           // L'evento memorizzato nel nodo
    eventoBstNodo genitore;  // Puntatore al nodo genitore
    eventoBstNodo sinistra;  // Puntatore al figlio sinistro
    eventoBstNodo destra;    // Puntatore al figlio destro
};

// Struttura dell'albero binario di ricerca
struct eventoBstStruct
{
    eventoBstNodo radice;   // Puntatore alla radice dell'albero
    int dimensione;         // Numero di nodi nell'albero
};

// Funzione per creare un nuovo albero binario di ricerca
eventoBst nuovo_evento_bst()
{
    // Alloca memoria per una nuova struttura eventoBst
    eventoBst nuovo = malloc(sizeof(*nuovo));
    if (nuovo == NULL)
    {
        return NULL; 
    } 
     // Inizializza i campi della struttura eventoBst
    // Imposta la radice dell'albero a NULL, poiché l'albero è inizialmente vuoto
    nuovo->radice = NULL;
    // Imposta la dimensione dell'albero a 0, poiché non contiene ancora nodi
    nuovo->dimensione = 0;

    // Restituisce un puntatore alla nuova struttura eventoBst inizializzata
    return nuovo;
}

// Funzione per inserire un evento nell'albero
int inserisci_evento_bst(eventoBst bst, Evento evento)
{
    // Verifica che l'albero esista
    if (bst == NULL)
    {
        printf("Errore");
        return -1;
    }

    // Alloca e azzera memoria per il nuovo nodo
    eventoBstNodo nuovo = calloc(1, sizeof(struct eventoBstNodoStruct));
    // Verifica che la memoria sia stata allocata correttamente
    if (nuovo == NULL)
    {
        printf("Errore");
        return -1;
    }

    nuovo->valore = evento; // Assegna l'evento al nuovo nodo

    eventoBstNodo genitore = NULL; // Puntatore al nodo genitore

    eventoBstNodo temp = bst->radice; // Inizia dalla radice dell'albero
    while (temp != NULL)
    {
        genitore = temp; // Aggiorna il genitore
        // Confronta l'evento con il valore del nodo corrente per decidere la direzione
        if (confronta_eventi(nuovo->valore, genitore->valore) < 0)
        {
            temp = temp->sinistra; // Scendi a sinistra
        }
        else
        {
            temp = temp->destra; // Scendi a destra
        }
    }

    nuovo->genitore = genitore; // Imposta il genitore del nuovo nodo

    // Se il genitore è NULL, l'albero era vuoto e il nuovo nodo diventa la radice
    if (genitore == NULL)
    {
        bst->radice = nuovo;
    }
    // Inserisce il nuovo nodo come figlio sinistro o destro del genitore
    else if (confronta_eventi(nuovo->valore, genitore->valore) < 0)
    {
        genitore->sinistra = nuovo;
    }
    else
    {
        genitore->destra = nuovo;
    }
    bst->dimensione += 1;  // Incrementa la dimensione dell'albero
    return 0;  // Inserimento riuscito
}

// Funzione per cercare un nodo contenente un evento specifico
eventoBstNodo bst_cerca_evento(eventoBst bst, Evento evento)
{
    eventoBstNodo result = bst->radice;  // Inizia dalla radice dell'albero
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
    return result; // Restituisce il nodo trovato o NULL
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

// Funzione per cercare un nodo contenente un evento con un ID specifico
eventoBstNodo bst_cerca_evento_by_id(eventoBst bst, int id)
{
    return bst_cerca_nodi_evento_by_id(bst->radice, id); // Inizia dalla radice dell'albero
}

// Funzione per spostare i nodi all'interno dell'albero
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
        return NULL; // Caso base: nodo nullo
    }
    // Scorre il sottoalbero destro fino a trovare il nodo con il valore massimo
    while (nodo->destra != NULL)
    {
        nodo = nodo->destra;
    }
    return nodo; // Restituisce il nodo con il valore massimo
}

// Funzione per trovare il nodo con il valore minimo in un sottoalbero
eventoBstNodo bst_minimo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL; // Caso base: nodo nullo
    }
    // Scorre il sottoalbero sinistro fino a trovare il nodo con il valore minimo
    while (nodo->sinistra != NULL)
    {
        nodo = nodo->sinistra;
    }
    return nodo; // Restituisce il nodo con il valore minimo
}

// Funzione per trovare il nodo predecessore di un nodo dato
eventoBstNodo bst_precedente(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL; // Caso base: nodo nullo
    }
    if (nodo->sinistra != NULL)
    {
        return bst_massimo(nodo->sinistra); // Restituisce il massimo nel sottoalbero sinistro
    }
    eventoBstNodo res = nodo->genitore; // Altrimenti, risale l'albero per trovare il predecessore
    while (res != NULL && nodo == res->sinistra)
    {
        nodo = res;
        res = res->genitore;
    }
    return res; // Restituisce il predecessore trovato
}

// Funzione per trovare il nodo successore di un nodo dato
eventoBstNodo bst_successivo(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return NULL; // Caso base: nodo nullo
    }
    if (nodo->destra != NULL)
    {
        return bst_minimo(nodo->destra); // Restituisce il minimo nel sottoalbero destro
    }
    eventoBstNodo res = nodo->genitore; // Altrimenti, risale l'albero per trovare il successore
    while (res != NULL && nodo == res->destra)
    {
        nodo = res;
        res = res->genitore;
    }
    return res; // Restituisce il successore trovato
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
            temp->destra = nodo->destra; // Collega il figlio destro del nodo al successore
            temp->destra->genitore = temp; // Imposta il genitore del figlio destro
        }
        bst_shift_nodi(bst, nodo, temp);  // Sostituisci il nodo con il successore
        temp->sinistra = nodo->sinistra;  // Collega il figlio sinistro del nodo al successore
        temp->sinistra->genitore = temp;  // Imposta il genitore del figlio sinistro
    }
    Evento valore = nodo->valore; // Salva il valore del nodo
    free(nodo); // Libera la memoria del nodo
    bst->dimensione--; // Decrementa la dimensione dell'albero
    return valore; // Restituisce il valore del nodo rimosso
}

// Funzione per rimuovere un evento specifico dall'albero
Evento bst_rimuovi_evento(eventoBst bst, Evento evento)
{
    eventoBstNodo nodo = bst_cerca_evento(bst, evento); // Cerca il nodo contenente l'evento
    return bst_rimuovi_nodo(bst, nodo); // Rimuove il nodo e restituisce il valore
}

// Funzione per rimuovere un evento specifico dall'albero usando l'ID
Evento bst_rimuovi_evento_by_id(eventoBst bst, int id)
{
    eventoBstNodo nodo = bst_cerca_evento_by_id(bst, id); // Cerca il nodo contenente l'evento
    return bst_rimuovi_nodo(bst, nodo); // Rimuove il nodo e restituisce il valore
}

// Funzione per stampare i nodi dell'albero in ordine
void stampa_evento_bst_nodi(eventoBstNodo nodo, ListaSala sala_lista)
{
    if (nodo == NULL)
    {
        return; // Caso base: nodo nullo
    }
    // Stampa ricorsivamente i sottoalberi sinistro, nodo e destro
    stampa_evento_bst_nodi(nodo->sinistra, sala_lista);
    stampa_evento(nodo->valore, sala_per_id_lista(sala_lista, prendi_evento_sala_id(nodo->valore)));
    printf("\n\n");
    stampa_evento_bst_nodi(nodo->destra, sala_lista);
}

// Funzione per stampare l'intero albero
void stampa_evento_bst(eventoBst bst, ListaSala sala_lista)
{
    stampa_evento_bst_nodi(bst->radice, sala_lista); // Parte dalla radice dell'albero
}

// Funzione per ottenere la dimensione dell'albero (numero di nodi)
int prendi_bst_dimensione(eventoBst bst)
{
    return bst->dimensione; // Restituisce la dimensione dell'albero
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

// Funzione per liberare la memoria dei nodi dell'albero (ricorsiva)
void libera_evento_bst_nodi(eventoBstNodo nodo)
{
    if (nodo == NULL)
    {
        return; // Caso base: nodo nullo
    }

    // Libera ricorsivamente i sottoalberi sinistro e destro
    libera_evento_bst_nodi(nodo->sinistra);
    libera_evento_bst_nodi(nodo->destra);

    // Libera la memoria dell'evento contenuto nel nodo e del nodo stesso
    libera_evento(nodo->valore);
    free(nodo);
}

// Funzione per liberare la memoria dell'intero albero
void libera_evento_bst(eventoBst bst)
{
    if (bst == NULL)
    {
        return; // Caso base: albero nullo
    }
    libera_evento_bst_nodi(bst->radice); // Libera la memoria dei nodi dell'albero
    free(bst); // Libera la memoria della struttura albero
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
        if (evento == NULL) // Verifica se la lettura dell'evento ha avuto successo
        {
            perror("Error reading event data"); 
            libera_evento_bst(bst); // Libera la memoria dell'albero in caso di errore
            return NULL;
        }
        inserisci_evento_bst(bst, evento); // Inserisce l'evento nell'albero
    }

    return bst; // Restituisce l'albero letto dal file
}
