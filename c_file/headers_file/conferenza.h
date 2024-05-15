// file conferenza.h

#include "utile.h"
#include "bst_evento.h"

typedef struct ConferenceStruct *conferenza;

conferenza nuova_conferenza();
int aggiungi_conferenza_evento(conferenza conf);
int aggiungi_conferenza_sala(conferenza conf);
int rimuovi_conferenza_evento(conferenza conf);
int modifica_nome_conferenza_evento(conferenza conf, event evento);
int modifica_data_inizio_conferenza_evento(conferenza conf, event evento);
int modifica_data_fine_conferenza_evento(conferenza conf, event evento);
int modifica_tipo_conferenza_evento(conferenza conf, event evento);
int modifica_conferenza_evento(conferenza conf);
int stampa_conferenza(conferenza conf);
int stampa_conferenza_sale(conferenza conf);
int conferenza_assegna_evento_a_sala(conferenza conf);
void free_conferenza(conferenza conf);
void salva_conferenza_su_file(conferenza conf, FILE *file);
conferenza leggi_conferenza_da_file(FILE *file);