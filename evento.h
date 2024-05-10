#include "data.h"

// file evento.h

typedef struct myEvent *event;

event crea_evento(char *nome, int tipo, Date data);
int get_id(event evento);
char *get_nome(event evento);
int get_tipo(event evento);
Date get_data(event evento);
int set_data(event evento, Date data);
int set_nome(event evento, char *nome);
int set_tipo(event evento, int tipo);
int equal_id(event evento1, event evento2);
event input_evento(void);
void stampa_evento(event evento);
int confronta_eventi(event evento1, event evento2);
void free_event(event evento);
