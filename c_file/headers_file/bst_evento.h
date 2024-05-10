// file bst_evento.h

#include "evento.h"

typedef struct eventBstStruct *eventBst;

eventBst nuovo_evento_bst();
int inserisci_evento_bst(eventBst bst, event evento);
event bst_rimuovi_evento(eventBst bst, event evento);
event bst_rimuovi_evento_by_id(eventBst bst, int id);
int get_bst_size(eventBst bst);
void stampa_evento_bst(eventBst bst);
void free_event_bst(eventBst bst);
