
#include <stdbool.h>
#include "sala.h"
#include "utile.h"

// file lista_sala.h

typedef struct ListaSalaStruct *ListaSala;

ListaSala nuova_lista_sala(void);

void aumenta_capacita_lista_sala(ListaSala lista);
bool lista_sala_vuota(ListaSala lista);
void aggiungi_sala_lista(ListaSala lista, Sala s);
Sala sala_fine_lista(ListaSala lista);

Sala prendi_prima_sala_lista(ListaSala lista);
int prendi_dimensione_lista_sala(ListaSala lista);
int prendi_posizione_sala_lista(ListaSala lista, Sala da_cercare);

Sala sala_in_posizione_lista(ListaSala lista, int posizione);
Sala sala_per_id_lista(ListaSala lista, int id_sala);

void stampa_lista_sala(ListaSala lista);

void salva_lista_sala_su_file(ListaSala lista, FILE *file);
ListaSala leggi_lista_sala_da_file(FILE *file);

void libera_lista_sala(ListaSala lista);
