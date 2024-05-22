// file evento.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"

// Definizione della struttura myEvent che rappresenta un evento
typedef struct myEvent
{
    int id;       // Identificativo dell'evento
    char *nome;   // Nome dell'evento
    int tipo;     // Tipo dell'evento ( Workshop, Sessione di keynote, Panel di discussione)
    Date inizio;  // Data di inizio dell'evento
    Date fine;    // Data di fine dell'evento
    int sala_id;  // Identificativo della sala dove si tiene l'evento
} myEvent;

// Funzione per creare un nuovo evento
event crea_evento(char *nome, int tipo, Date inizio, Date fine, int id)
{
    // Alloca memoria per la struttura myEvent
    myEvent *evento = malloc(sizeof(myEvent));
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
    evento->nome = strdup(nome);  // Copia il nome passato come argomento

    // Controlla se la copia del nome è riuscita
    if (evento->nome == NULL)
    {
        perror("Allocazione fallita.");
        free_date(evento->inizio);  // Libera la memoria allocata per la data di inizio
        free_date(evento->fine);    // Libera la memoria allocata per la data di fine
        free(evento);               // Libera la memoria allocata per l'evento
        return NULL;
    }
    evento->tipo = tipo;

    return evento;  // Ritorna il puntatore all'evento creato
}

// Funzione per ottenere l'ID di un evento
int get_id(event evento)
{
    if (evento == NULL)
    {
        return -1;  // Ritorna -1 se l'evento è NULL
    }
    return evento->id;  // Ritorna l'ID dell'evento
}

// Funzione per ottenere il nome di un evento
char *get_nome(event evento)
{
    if (evento == NULL)
    {
        return NULL;  //Ritorna NULL se l'evento è NULL
    }
    return strdup(evento->nome); // Ritorna una copia del nome dell'evento
}

// Funzione per ottenere l'ID della sala di un evento
int get_evento_sala_id(event evento)
{
    if (evento == NULL)
    {
        return 0; // Ritorna 0 se l'evento è NULL
    }
    return evento->sala_id; // Ritorna l'ID della sala dell'evento
}

// Funzione per ottenere il tipo di un evento
int get_tipo(event evento)
{
    if (evento == NULL)
    {
        return -1;  // Ritorna -1 se l'evento è NULL
    }
    return evento->tipo;  // Ritorna il tipo dell'evento
}

// Funzione per ottenere la data di inizio di un evento
Date get_data_inizio(event evento)
{
    if (evento == NULL)
    {
        return NULL; // Ritorna NULL se l'evento è NULL
    }
    return evento->inizio; // Ritorna la data di inizio dell'evento
}

// Funzione per impostare la data di inizio di un evento
int set_data_inizio(event evento, Date inizio)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_event_start_date'."); // Perchè non scrivere al posto di ser_event_start_date set_data_inizio
        return -1; // Ritorna -1 se l'evento è NULL
    }

    // Controlla se la nuova data di inizio è successiva alla data di fine
    if (confronta_date(inizio, evento->fine) > 0)
    {
        printf("Data inizio superiore alla data di fine in 'set_event_start_date'.");
        return -2;  // Ritorna -2 se la data di inizio è successiva alla data di fine
    }

    // Libera la memoria della vecchia data di inizio e assegna la nuova
    free_date(evento->inizio);
    evento->inizio = inizio;
    return 0;  // Ritorna 0 se l'operazione è riuscita
}

// Funzione per ottenere la data di fine di un evento
Date get_data_fine(event evento)
{
    if (evento == NULL)
    {
        return NULL; // Ritorna NULL se l'evento è NULL
    }
    return evento->fine; // Ritorna la data di fine dell'evento
}

// Funzione per impostare la data di fine di un evento
int set_data_fine(event evento, Date fine)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_event_start_date'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }

    // Controlla se la data di fine è precedente alla data di inizio
    if (confronta_date(fine, evento->inizio) < 0)
    {
        printf("Data inizio superiore alla data di fine in 'set_event_start_date'.");
        return -2; // Ritorna -2 se la data di fine è precedente alla data di inizio
    }

    // Libera la memoria della vecchia data di fine e assegna la nuova
    free_date(evento->fine);
    evento->fine = fine;
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per impostare il nome di un evento
int set_nome(event evento, char *nome)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_name'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }
    char *temp = strdup(nome);
    if (temp == NULL)
    {
        printf("Copia di 'name' in 'set_name' fallita.");
        return -1; // Ritorna -1 se la copia del nome fallisce
    }
    // Libera la memoria del vecchio nome e assegna il nuovo
    free(evento->nome);
    evento->nome = temp;
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per impostare il tipo di un evento
int set_tipo(event evento, int tipo)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_event_type'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }
    evento->tipo = tipo; // Assegna il nuovo tipo all'evento
    return 0; // Ritorna 0 se l'operazione è riuscita
}

int set_evento_sala_id(event evento, int id_sala)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'set_event_start_date'.");
        return -1;
    }
    evento->sala_id = id_sala;
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

event input_evento(int id_evento)
{
    char nome[101] = {0};
    int tipo;

    // Chiede all'utente di inserire il nome dell'evento
    while(1){
        char temp[101] = {0};    // Buffer per memorizzare l'input
        printf("Inserisci nome evento [Max 100 caratteri]: ");
        if (leggi_input(temp, 101)) // Legge l'input dall'utente
        {
            printf("Nome troppo lungo");
            continue; //riprova se il nome è troppo lungo
        }
        sscanf(temp,"%[^\n]",nome); //copia l'input in nome escludendo '\n'
        if(strlen(nome) == 0) //controlla se l'input è vuoto
        {
            continue; //riprova se l'input è vuoto
        }
        break; //esce dal ciclo se l'input è valido
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

    // Read event date
    Date inizio = NULL;
    do
    {
        printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm):> ");
        inizio = input_data();
    } while (inizio == NULL && printf("Data inserita non valida\n"));

    Date fine = NULL;
    do
    {
        printf("Inserisci data fine evento (DD/MM/AAAA hh:mm):> ");
        fine = input_data();
    } while ((fine == NULL || confronta_date(inizio, fine) > 0) && printf("Data inserita non valida\n"));

    event evento = crea_evento(nome, tipo, inizio, fine, id_evento);
    return evento;
}

void stampa_evento(event evento, sala sala_assegnata)
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
    printf("Data inizio: ");
    stampa_data(evento->inizio);

    printf("\n");

    printf("Data fine: ");
    stampa_data(evento->fine);

    printf("\n");

    if (sala_assegnata != NULL)
    {
        printf("Sala:> ");
        stampa_sala(sala_assegnata);
    }
}

int confronta_eventi(event evento1, event evento2)
{
    int date_comparison = confronta_date(get_data_inizio(evento1), get_data_fine(evento2));
    if (date_comparison < 0)
    {
        return -1;
    }
    if (date_comparison > 0)
    {
        return 1;
    }
    return strcmp(evento1->nome, evento2->nome);
}

void free_event(event evento)
{
    free_date(evento->inizio);
    free_date(evento->fine);
    free(evento->nome);
    free(evento);
}

void salva_evento_su_file(event evento, FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return;
    }

    // Write event data to the file
    fprintf(file, "%d %s %d %d\n", evento->id, evento->nome, evento->tipo, evento->sala_id);

    // Save start date to file
    salva_data_su_file(evento->inizio, file);

    // Save end date to file
    salva_data_su_file(evento->fine, file);
}

// Function to read an event from a file
event leggi_evento_da_file(FILE *file)
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

    // Read event data from the file
    if (fscanf(file, "%d %d %d", &id, &tipo, &sala_id) != 3)
    {
        pulisci_buffer(file);
        return NULL;
    }

    (void)fgetc(file);
    leggi_input_da_file(nome, 102, file);

    // Read start date from file
    Date inizio = leggi_data_da_file(file);
    if (inizio == NULL)
    {
        return NULL;
    }

    // Read end date from file
    Date fine = leggi_data_da_file(file);
    if (fine == NULL)
    {
        free_date(inizio); // Free allocated memory before returning NULL_EVENT
        return NULL;
    }

    // Create a new event object with the read data
    event evento = crea_evento(nome, tipo, inizio, fine, id);
    if (evento != NULL)
    {
        evento->sala_id = sala_id;
    }
    else
    {
        free_date(inizio);
        free_date(fine);
    }

    return evento;
}
