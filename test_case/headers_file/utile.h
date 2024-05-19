// file utile.h

void pulisci_buffer(FILE *file);
int leggi_input_da_file(char *line, int size, FILE *file);
int leggi_input(char *line, int size);
int leggi_intero();
void *my_alloc(unsigned long nmemb, unsigned long size);
void *my_realloc(void *p, unsigned long nmemb, unsigned long size);
char *my_strdup(char *stringa);