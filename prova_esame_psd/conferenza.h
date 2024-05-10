

#include "bst_evento.h"

typedef struct ConferenceStruct *conferenza;

conferenza nuova_conferenza();
int aggiungi_conferenza_evento(conferenza conf);
int rimuovi_conferenza_evento(conferenza conf);
int modifica_nome_conferenza_evento(conferenza conf, event evento);
int modifica_data_conferenza_evento(conferenza conf, event evento);
int modifica_tipo_conferenza_evento(conferenza conf, event evento);
int modifica_conferenza_evento(conferenza conf);
int stampa_conferenza(conferenza conf);
void free_conferenza(conferenza conf);
