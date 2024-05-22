#include "evento.h"
#include "lista_sala.h"

// file bst_evento.h

typedef struct eventoBstStruct *eventoBst;

eventoBst nuovo_evento_bst();
int inserisci_evento_bst(eventoBst bst, Evento evento);
Evento bst_rimuovi_evento(eventoBst bst, Evento evento);
Evento bst_rimuovi_evento_by_id(eventoBst bst, int id);
int prendi_bst_dimensione(eventoBst bst);
void stampa_evento_bst(eventoBst bst, ListaSala sala_lista);
Evento bst_prendi_evento_by_id(eventoBst bst, int id);
void libera_evento_bst(eventoBst bst);
void salva_evento_bst_su_file(eventoBst bst, FILE *file);
eventoBst leggi_evento_bst_da_file(FILE *file);
