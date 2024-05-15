
#include <stdio.h>
#include <stdbool.h> //contiene macro per i tipi di dato booleani
#include "utile.h"

// file sala.h

typedef struct StructSala *sala;

sala nuova_sala(char *nome, int id);
bool eq_sale(sala s1, sala s2);
sala input_sala(int id);
char *get_sala_nome(sala s);
int get_sala_id(sala s);
void stampa_sala(sala s);
void free_sala(sala s);
void salva_sala_su_file(sala s, FILE *file);
sala leggi_sala_da_file(FILE *file);
