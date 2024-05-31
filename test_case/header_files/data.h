#include "utile.h"
// file data.h

typedef struct DataOra *Data;

Data nuova_data(int anno, int mese, int giorno, int ora, int minuti);

int controllo_data(Data data);
int utile_data(int d1, int d2);
int confronta_date(Data date1, Data date2);
Data input_data(void);

void stampa_data(Data data);

void salva_data_su_file(Data data, FILE *file);
Data leggi_data_da_file(FILE *file);

void libera_data(Data date);
