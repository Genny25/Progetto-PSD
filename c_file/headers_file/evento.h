#include "data.h"
#include "sala.h"
#include "utile.h"

// file evento.h

typedef struct myEvent *event;

event crea_evento(char *nome, int tipo, Date inizio, Date fine, int id);
int get_id(event evento);
char *get_nome(event evento);
int get_evento_sala_id(event evento);
int get_tipo(event evento);
Date get_data_inizio(event evento);
int set_data_inizio(event evento, Date inizio);
Date get_data_fine(event evento);
int set_data_fine(event evento, Date fine);
int set_nome(event evento, char *nome);
int set_tipo(event evento, int tipo);
int set_evento_sala_id(event evento, int id_sala);
int equal_id(event evento1, event evento2);
event input_evento(int id_evento);
void stampa_evento(event evento, sala sala_assegnata);
int confronta_eventi(event evento1, event evento2);
void free_event(event evento);
void salva_evento_su_file(event evento, FILE *file);
event leggi_evento_da_file(FILE *file);
