// file evento.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utile.h"
#include "data.h"
#include "evento.h"

static int id_counter = 0;

typedef struct myEvent
{
    int id;
    char *nome;
    int tipo;
    Date data;
} myEvent;

event crea_evento(char *nome, int tipo, Date data)
{
    myEvent *evento = malloc(sizeof(myEvent));
    if (evento == NULL)
    {
        perror("Allocazione fallita.");
        return NULL;
    }
    evento->id = id_counter++;
    evento->data = data;
    evento->nome = strdup(nome);
    if (evento->nome == NULL)
    {
        perror("Allocazione fallita.");
        free_date(evento->data);
        free(evento);
        return NULL;
    }
    evento->tipo = tipo;

    return evento;
}

int get_id(event evento)
{
    if (evento == NULL)
    {
        return -1;
    }
    return evento->id;
}

char *get_nome(event evento)
{
    if (evento == NULL)
    {
        return NULL;
    }
    return strdup(evento->nome);
}

int get_tipo(event evento)
{
    if (evento == NULL)
    {
        return -1;
    }
    return evento->tipo;
}

Date get_data(event evento)
{
    if (evento == NULL)
    {
        return NULL;
    }
    return evento->data;
}

int set_data(event evento, Date data)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_event_start_date'.");
        return -1;
    }

    free_date(evento->data);
    evento->data = data;
    return 0;
}

int set_nome(event evento, char *nome)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_name'.");
        return -1;
    }
    char *temp = strdup(nome);
    if (temp == NULL)
    {
        printf("Copia di 'name' in 'set_name' fallita.");
        return -1;
    }
    free(evento->nome);
    evento->nome = temp;
    return 0;
}

int set_tipo(event evento, int tipo)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_event_type'.");
        return -1;
    }
    evento->tipo = tipo;
    return 0;
}

int equal_id(event evento1, event evento2)
{
    if (evento1 == NULL || evento2 == NULL)
    {
        return 0;
    }
    return evento1->id == evento2->id;
}

event input_evento(void)
{
    char nome[101];
    int tipo;

    printf("Inserisci nome evento [Max 100 caratteri]:> ");
    if (leggi_input(nome, 101))
    {
        return NULL;
    }
    do
    {
        printf("\nTipologie Evento\n");
        printf("[1]: Workshop\n");
        printf("[2]: Sessione di keynote\n");
        printf("[3]: Panel di discussione\n");
        printf("Seleziona tipologia evento (1, 2 o 3):> ");
        scanf("%d", &tipo);
        pulisci_buffer();
    } while (tipo < 1 || tipo > 3);

    // Read event date
    Date data = NULL;
    do
    {
        printf("Inserisci data evento (DD/MM/AAAA hh:mm):> ");
        data = input_data();
    } while (data == NULL && printf("Data inserita non valida\n"));

    event evento = crea_evento(nome, tipo, data);
    return evento;
}

void stampa_evento(event evento)
{
    if (evento == NULL)
    {
        printf("Evento non valido\n");
        return;
    }

    printf("\n");
    printf("ID evento: %d\n", evento->id);
    printf("Nome evento: %s\n", evento->nome);
    printf("Tipologia evento: ");
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
    printf("Data: ");
    stampa_data(evento->data);
}

int confronta_eventi(event evento1, event evento2)
{
    int date_comparison = confronta_date(get_data(evento1), get_data(evento2));
    if (date_comparison < 0)
    {
        return -1;
    }
    if (date_comparison > 0)
    {
        return 1;
    }
    return strcmp(get_nome(evento1), get_nome(evento2));
}

void free_event(event evento)
{
    free_date(evento->data);
    free(evento->nome);
    free(evento);
}