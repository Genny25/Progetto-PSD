// file evento.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"

// Definizione della struttura mioEvento che rappresenta un evento
typedef struct mioEvento
{
    int id;      // Identificativo dell'evento
    char *nome;  // Nome dell'evento
    int tipo;    // Tipo dell'evento (Workshop, Sessione di keynote, Panel di discussione)
    Data inizio; // Data di inizio dell'evento
    Data fine;   // Data di fine dell'evento
    int sala_id; // Identificativo della sala dove si tiene l'evento
} mioEvento;

// Funzione per creare un nuovo evento
Evento crea_evento(char *nome, int tipo, Data inizio, Data fine, int id)
{
    // Alloca memoria per la struttura mioEvento
    mioEvento *evento = malloc(sizeof(mioEvento));
    if (evento == NULL)
    {
        // Se l'allocazione fallisce, stampa un errore e ritorna NULL
        perror("Allocazione fallita.");
        return NULL;
    }
    // Inizializza i campi della struttura
    evento->id = id;
    evento->inizio = inizio;
    evento->fine = fine;
    evento->sala_id = 0;
    evento->nome = strdup(nome); // Copia il nome passato come argomento

    // Controlla se la copia del nome è riuscita
    if (evento->nome == NULL)
    {
        perror("Allocazione fallita.");
        libera_data(evento->inizio); // Libera la memoria allocata per la data di inizio
        libera_data(evento->fine);   // Libera la memoria allocata per la data di fine
        free(evento);                // Libera la memoria allocata per l'evento
        return NULL;
    }
    evento->tipo = tipo;

    return evento; // Ritorna il puntatore all'evento creato
}

// Funzione per ottenere l'ID di un evento
int prendi_id(Evento evento)
{
    if (evento == NULL)
    {
        return -1; // Ritorna -1 se l'evento è NULL
    }
    return evento->id; // Ritorna l'ID dell'evento
}

// Funzione per ottenere il nome di un evento
char *prendi_nome(Evento evento)
{
    if (evento == NULL)
    {
        return NULL; // Ritorna NULL se l'evento è NULL
    }
    return strdup(evento->nome); // Ritorna una copia del nome dell'evento
}

// Funzione per ottenere l'ID della sala di un evento
int prendi_evento_sala_id(Evento evento)
{
    if (evento == NULL)
    {
        return 0; // Ritorna 0 se l'evento è NULL
    }
    return evento->sala_id; // Ritorna l'ID della sala dell'evento
}

// Funzione per ottenere il tipo di un evento
int prendi_tipo(Evento evento)
{
    if (evento == NULL)
    {
        return -1; // Ritorna -1 se l'evento è NULL
    }
    return evento->tipo; // Ritorna il tipo dell'evento
}

// Funzione per ottenere la data di inizio di un evento
Data prendi_data_inizio(Evento evento)
{
    if (evento == NULL)
    {
        return NULL; // Ritorna NULL se l'evento è NULL
    }
    return evento->inizio; // Ritorna la data di inizio dell'evento
}

// Funzione per ottenere la data di fine di un evento
Data prendi_data_fine(Evento evento)
{
    if (evento == NULL)
    {
        return NULL; // Ritorna NULL se l'evento è NUL
    }
    return evento->fine; // Ritorna la data di fine dell'evento
}

// Funzione per impostare la data di inizio di un evento
int imposta_data_inizio(Evento evento, Data inizio)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_data_inizio'.");
        return -1;
    }

    // Controlla se la nuova data di inizio è successiva alla data di fine
    if (confronta_date(inizio, evento->fine) > 0)
    {
        printf("Data inizio superiore alla data di fine in 'imposta_data_inizio'.");
        return -2;
    }

    libera_data(evento->inizio);
    evento->inizio = inizio;
    return 0; // Ritorna 0 se l'operazione è riuscita
}

int imposta_data_fine(Evento evento, Data fine)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_data_fine'.");
        return -1;
    }

    if (confronta_date(fine, evento->inizio) < 0)
    {
        printf("Data fine inferiore alla data di inizio in 'imposta_data_fine'.");
        return -2;
    }

    libera_data(evento->fine);
    evento->fine = fine;
    return 0;
}

int imposta_nome(Evento evento, char *nome)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_nome'.");
        return -1;
    }
    char *temp = strdup(nome);
    if (temp == NULL)
    {
        printf("Copia di 'nome' in 'imposta_nome' fallita.");
        return -1;
    }
    free(evento->nome);
    evento->nome = temp;
    return 0;
}

int imposta_tipo(Evento evento, int tipo)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_tipo'.");
        return -1;
    }
    evento->tipo = tipo;
    return 0;
}

int imposta_evento_sala_id(Evento evento, int id_sala)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_evento_sala_id'.");
        return -1;
    }
    evento->sala_id = id_sala;
    return 0;
}

int id_uguale(Evento evento1, Evento evento2)
{
    if (evento1 == NULL || evento2 == NULL)
    {
        return 0;
    }
    return evento1->id == evento2->id;
}

Evento input_evento(int id_evento)
{
    char nome[101] = {0};
    int tipo;

    while (1)
    {
        char temp[101] = {0};
        printf("Inserisci nome evento [Max 100 caratteri]: ");
        if (leggi_input(temp, 101))
        {
            printf("Nome troppo lungo");
            continue;
        }
        sscanf(temp, "%[^\n]", nome);
        if (strlen(nome) == 0)
        {
            continue;
        }
        break;
    }

    do
    {
        printf("\nTipologie Evento\n");
        printf("[1]: Workshop\n");
        printf("[2]: Sessione di keynote\n");
        printf("[3]: Panel di discussione\n");
        printf("Seleziona tipologia evento (1, 2 o 3):> ");
        scanf("%d", &tipo);
        pulisci_buffer(stdin);
    } while (tipo < 1 || tipo > 3);

    Data inizio = NULL;
    do
    {
        printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm):> ");
        inizio = input_data();
    } while (inizio == NULL && printf("Data inserita non valida\n"));

    Data fine = NULL;
    do
    {
        printf("Inserisci data fine evento (DD/MM/AAAA hh:mm):> ");
        fine = input_data();
    } while ((fine == NULL || confronta_date(inizio, fine) > 0) && printf("Data inserita non valida\n"));

    Evento evento = crea_evento(nome, tipo, inizio, fine, id_evento);
    return evento;
}

void stampa_evento(Evento evento, Sala sala_assegnata)
{
    if (evento == NULL)
    {
        printf("Evento non valido\n");
        return;
    }

    printf("\n");
    printf("ID evento:> %d\n", evento->id);
    printf("Nome evento:> %s\n", evento->nome);
    printf("Tipologia evento:> ");
    switch (evento->tipo)
    {
    case 1:
        printf("Workshop\n");
        break;
    case 2:
        printf("Sessione di keynote\n");
        break;
    case 3:
        printf("Panel di discussione\n");
        break;
    }
    printf("Data inizio:> ");
    stampa_data(evento->inizio);

    printf("\n");

    printf("Data fine:> ");
    stampa_data(evento->fine);

    printf("\n");

    if (sala_assegnata != NULL)
    {
        printf("Sala:> ");
        stampa_sala(sala_assegnata);
    }
}

int confronta_eventi(Evento evento1, Evento evento2)
{
    int data_comparison = confronta_date(prendi_data_inizio(evento1), prendi_data_fine(evento2));
    if (data_comparison < 0)
    {
        return -1;
    }
    if (data_comparison > 0)
    {
        return 1;
    }
    return strcmp(evento1->nome, evento2->nome);
}

void salva_evento_su_file(Evento evento, FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return;
    }

    fprintf(file, "%d %d %d %s\n", evento->id, evento->tipo, evento->sala_id, evento->nome);
    salva_data_su_file(evento->inizio, file);
    salva_data_su_file(evento->fine, file);
}

Evento leggi_evento_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return NULL;
    }

    int id = 0;
    int tipo = 0;
    int sala_id = 0;
    char nome[102];

    if (fscanf(file, "%d %d %d", &id, &tipo, &sala_id) != 3)
    {
        pulisci_buffer(file);
        return NULL;
    }

    fgetc(file);
    leggi_input_da_file(nome, 102, file);

    Data inizio = leggi_data_da_file(file);
    if (inizio == NULL)
    {
        return NULL;
    }

    Data fine = leggi_data_da_file(file);
    if (fine == NULL)
    {
        libera_data(inizio);
        return NULL;
    }

    pulisci_buffer(file);

    Evento evento = crea_evento(nome, tipo, inizio, fine, id);
    if (evento != NULL)
    {
        evento->sala_id = sala_id;
    }
    else
    {
        libera_data(inizio);
        libera_data(fine);
    }

    return evento;
}

void libera_evento(Evento evento)
{
    libera_data(evento->inizio);
    libera_data(evento->fine);
    free(evento->nome);
    free(evento);
}
