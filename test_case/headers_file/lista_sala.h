
#include <stdbool.h>
#include "sala.h"
#include "utile.h"

// file lista_sala.h

typedef struct ListaSalaStruct *listaSala;

void aumenta_capacita_lista_sala(listaSala lista);
listaSala nuova_lista_sala(void);
bool lista_sala_vuota(listaSala lista);
void aggiungi_sala_lista(listaSala lista, sala s);
sala sala_fine_lista(listaSala lista);
sala get_prima_sala_lista(listaSala lista);
int get_dimensione_lista_sala(listaSala lista);
int get_posizione_sala_lista(listaSala lista, sala da_cercare);
sala sala_in_posizione_lista(listaSala lista, int posizione);
void stampa_lista_sala(listaSala lista);
void free_lista_sala(listaSala lista);
void salva_lista_sala_su_file(listaSala lista, FILE *file);
listaSala leggi_lista_sala_da_file(FILE *file);
sala sala_per_id_lista(listaSala lista, int id_sala);
