#include "evento.h"
#include "lista_sala.h"

// file bst_evento.h

typedef struct eventBstStruct *eventBst;

eventBst nuovo_evento_bst();
int inserisci_evento_bst(eventBst bst, event evento);
event bst_rimuovi_evento(eventBst bst, event evento);
event bst_rimuovi_evento_by_id(eventBst bst, int id);
int get_bst_size(eventBst bst);
void stampa_evento_bst(eventBst bst, listaSala sala_lista);
event bst_get_evento_by_id(eventBst bst, int id);
void free_event_bst(eventBst bst);
void salva_evento_bst_nodi(eventBstNode node, FILE *file);
void salva_evento_bst_su_file(eventBst bst, FILE *file);
eventBst leggi_evento_bst_da_file(FILE *file);
