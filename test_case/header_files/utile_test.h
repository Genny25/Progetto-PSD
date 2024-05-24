// file utile_test.h

#include "evento.h"
#include "conferenza.h"

int confronta_file(FILE *f1, FILE *f2);
int aggiungi_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file);
int rimuovi_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file);
int modifica_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file);
int mostra_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file);
