// file utile.h
#include <stdio.h>

void pulisci_buffer(FILE *file);

int leggi_input_da_file(char *riga, int dimensione, FILE *file);
int leggi_input(char *riga, int dimensione);
int leggi_intero();

void *my_alloc(unsigned long num_membri, unsigned long dimensione);
void *my_realloc(void *p, unsigned long num_membri, unsigned long dimensione);
char *my_strdup(char *stringa);