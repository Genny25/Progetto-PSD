// file data.h

typedef struct DateTime *Date;

Date nuova_data(int year, int month, int day, int hour, int minutes);
int controllo_data(Date date);
int utile_data(int d1, int d2);
int confronta_date(Date date1, Date date2);
int get_hour(Date date);
int get_minutes(Date date);
int get_day(Date date);
int get_month(Date date);
int get_year(Date date);
Date input_data(void);
void stampa_data(Date date);
void free_date(Date date);