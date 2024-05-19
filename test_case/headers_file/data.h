#include "utile.h"
// file data.h

typedef struct DateTime *Date;

Date nuova_data(int year, int month, int day, int hour, int minutes);
int controllo_data(Date date);
int utile_data(int d1, int d2);
int confronta_date(Date date1, Date date2);
Date input_data(void);
void stampa_data(Date date);
void free_date(Date date);
void salva_data_su_file(Date data, FILE *file);
Date leggi_data_da_file(FILE *file);
