#include "data.h"
#include "sala.h"
#include "utile.h"

// file evento.h

typedef struct mioEvento *Evento;

Evento crea_evento(char *nome, int tipo, Data inizio, Data fine, int id);

int prendi_id(Evento evento);
char *prendi_nome(Evento evento);
int prendi_evento_sala_id(Evento evento);
int prendi_tipo(Evento evento);
Data prendi_data_inizio(Evento evento);
Data prendi_data_fine(Evento evento);

int imposta_data_inizio(Evento evento, Data inizio);
int imposta_data_fine(Evento evento, Data fine);
int imposta_nome(Evento evento, char *nome);
int imposta_tipo(Evento evento, int tipo);
int imposta_evento_sala_id(Evento evento, int id_sala);

int id_uguale(Evento evento1, Evento evento2);

Evento input_evento(int id_evento);
void stampa_evento(Evento evento, Sala sala_assegnata);
int confronta_eventi(Evento evento1, Evento evento2);

void salva_evento_su_file(Evento evento, FILE *file);
Evento leggi_evento_da_file(FILE *file);

void libera_evento(Evento evento);