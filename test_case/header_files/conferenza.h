// file conferenza.h

#include "utile.h"
#include "bst_evento.h"
#include "data.h"
#include "sala.h"
#include "lista_sala.h"

typedef struct ConferenzaStruct *Conferenza;

Conferenza nuova_conferenza();

int aggiungi_conferenza_evento(Conferenza conf);
int aggiungi_conferenza_sala(Conferenza conf);

int rimuovi_conferenza_evento(Conferenza conf);

int modifica_nome_conferenza_evento(Conferenza conf, Evento evento);
int modifica_data_inizio_conferenza_evento(Conferenza conf, Evento evento);
int modifica_data_fine_conferenza_evento(Conferenza conf, Evento evento);
int modifica_tipo_conferenza_evento(Conferenza conf, Evento evento);
int modifica_conferenza_evento(Conferenza conf);

int stampa_conferenza(Conferenza conf);
int stampa_conferenza_sale(Conferenza conf);

int conferenza_assegna_evento_a_sala(Conferenza conf);

void salva_conferenza_su_file(Conferenza conf, FILE *file);
Conferenza leggi_conferenza_da_file(FILE *file);

void libera_conferenza(Conferenza conf);