
#include <stdio.h>
#include <stdbool.h> //contiene macro per i tipi di dato booleani
#include "utile.h"

// file sala.h

typedef struct StructSala *Sala;

Sala nuova_sala(char *nome, int id);

bool sale_uguali(Sala s1, Sala s2);
Sala input_sala(int id);

char *prendi_sala_nome(Sala s);
int prendi_sala_id(Sala s);

void stampa_sala(Sala s);

void salva_sala_su_file(Sala s, FILE *file);
Sala leggi_sala_da_file(FILE *file);

void libera_sala(Sala s);