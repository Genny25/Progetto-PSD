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
        return -1; // Ritorna -1 se l'evento è NULL
    }

    // Controlla se la nuova data di inizio è successiva alla data di fine
    if (confronta_date(inizio, evento->fine) > 0)
    {
        printf("Data inizio superiore alla data di fine in 'imposta_data_inizio'.");
        return -2; // Ritorna -2 se la data di inizio è successiva alla data di fine
    }

    // Libera la memoria della vecchia data di inizio e assegna la nuova
    libera_data(evento->inizio);
    evento->inizio = inizio;
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per impostare la data di fine di un evento
int imposta_data_fine(Evento evento, Data fine)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_data_fine'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }

    // Controlla se la nuova data di fine è precedente alla data di inizio
    if (confronta_date(fine, evento->inizio) < 0)
    {
        printf("Data fine inferiore alla data di inizio in 'imposta_data_fine'.");
        return -2; // Ritorna -2 se la data di fine è precedente alla data di inizio
    }

    // Libera la memoria della vecchia data di fine e assegna la nuova
    libera_data(evento->fine);
    evento->fine = fine;
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per impostare il nome di un evento
int imposta_nome(Evento evento, char *nome)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_nome'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }
    // Copia il nuovo nome
    char *temp = strdup(nome);
    if (temp == NULL)
    {
        printf("Copia di 'nome' in 'imposta_nome' fallita.");
        return -1; // Ritorna -1 se la copia del nome fallisce
    }
    // Libera la memoria del vecchio nome e assegna il nuovo
    free(evento->nome);
    evento->nome = temp;
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per impostare il tipo di un evento
int imposta_tipo(Evento evento, int tipo)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_tipo'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }
    evento->tipo = tipo; // Assegna il nuovo tipo all'evento
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per impostare l'ID della sala di un evento
int imposta_evento_sala_id(Evento evento, int id_sala)
{
    if (evento == NULL)
    {
        printf("Passato puntatore NULL alla funzione 'imposta_evento_sala_id'.");
        return -1; // Ritorna -1 se l'evento è NULL
    }
    evento->sala_id = id_sala; // Assegna il nuovo ID della sala all'evento
    return 0; // Ritorna 0 se l'operazione è riuscita
}

// Funzione per confrontare gli ID di due eventi
int id_uguale(Evento evento1, Evento evento2)
{
    if (evento1 == NULL || evento2 == NULL)
    {
        return 0; // Ritorna 0 se uno dei due eventi è NULL
    }
    return evento1->id == evento2->id; // Ritorna 1 se gli ID sono uguali, 0 altrimenti
}

// Funzione per inserire un evento da input utente
Evento input_evento(int id_evento)
{
    char nome[101] = {0};
    int tipo;

    // Chiede all'utente di inserire il nome dell'evento
    while (1)
    {
        char temp[101] = {0}; // Buffer per memorizzare l'input
        printf("Inserisci nome evento [Max 100 caratteri]: ");
        if (leggi_input(temp, 101)) // Legge l'input dall'utente
        {
            printf("Nome troppo lungo");
            continue; // Riprova se il nome è troppo lungo
        }
        sscanf(temp, "%[^\n]", nome); // Copia l'input in nome escludendo '\n'
        if (strlen(nome) == 0) // Controlla se l'input è vuoto
        {
            continue; // Riprova se l'input è vuoto
        }
        break; // Esce dal ciclo se l'input è valido
    }

    do
    {
        // Chiede all'utente di selezionare il tipo di evento
        printf("\nTipologie Evento\n");
        printf("[1]: Workshop\n");
        printf("[2]: Sessione di keynote\n");
        printf("[3]: Panel di discussione\n");
        printf("Seleziona tipologia evento (1, 2 o 3):> ");
        scanf("%d", &tipo);
        pulisci_buffer(stdin);
    } while (tipo < 1 || tipo > 3); // Continua a chiedere finché l'input non è valido

    Data inizio = NULL;
    do
    {
        // Chiede all'utente di inserire la data di inizio dell'evento
        printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm):> ");
        inizio = input_data();
    } while (inizio == NULL && printf("Data inserita non valida\n")); // Continua a chiedere finché l'input non è valido

    Data fine = NULL;
    do
    {
        // Chiede all'utente di inserire la data di fine dell'evento
        printf("Inserisci data fine evento (DD/MM/AAAA hh:mm):> ");
        fine = input_data();
    } while ((fine == NULL || confronta_date(inizio, fine) > 0) && printf("Data inserita non valida\n")); // Continua a chiedere finché l'input non è valido
    
    // Crea l'evento con i dati inseriti dall'utente
    Evento evento = crea_evento(nome, tipo, inizio, fine, id_evento);
    return evento; // Ritorna il puntatore all'evento creato
}

// Funzione per stampare le informazioni di un evento
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
    stampa_data(evento->inizio); // Stampa la data di inizio

    printf("\n");

    printf("Data fine:> ");
    stampa_data(evento->fine); // Stampa la data di fine

    printf("\n");

    if (sala_assegnata != NULL)
    {
        printf("Sala:> ");
        stampa_sala(sala_assegnata); // Stampa le informazioni della sala assegnata
    }
}

// Funzione per confrontare due eventi
int confronta_eventi(Evento evento1, Evento evento2)
{
    int data_comparison = confronta_date(prendi_data_inizio(evento1), prendi_data_fine(evento2));
    if (data_comparison < 0)
    {
        return -1; // Ritorna -1 se la data di inizio del primo evento è precedente alla data di fine del secondo
    }
    if (data_comparison > 0)
    {
        return 1; // Ritorna 1 se la data di inizio del primo evento è successiva alla data di fine del secondo
    }
    return strcmp(evento1->nome, evento2->nome); // Ritorna il risultato del confronto dei nomi degli eventi
}

// Funzione per salvare un evento su file
void salva_evento_su_file(Evento evento, FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return;
    }

    // Scrive i dati dell'evento sul file
    fprintf(file, "%d %d %d %s\n", evento->id, evento->tipo, evento->sala_id, evento->nome);
    // Salva la data di inizio sul file
    salva_data_su_file(evento->inizio, file);
    // Salva la data di fine sul file
    salva_data_su_file(evento->fine, file);
}

// Funzione per leggere un evento da un file
Evento leggi_evento_da_file(FILE *file)
{
    // Controlla se il puntatore al file è NULL
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return NULL; // Ritorna NULL se il file non è valido
    }

    int id = 0;
    int tipo = 0;
    int sala_id = 0;
    char nome[102];

    // Legge i dati dell'evento dal file (id, tipo e sala_id)
    if (fscanf(file, "%d %d %d", &id, &tipo, &sala_id) != 3)
    {
        // Se la lettura non ha successo, pulisce il buffer e ritorna NULL
        pulisci_buffer(file);
        return NULL;
    }

    // Consuma il carattere di newline rimasto nel buffer
    fgetc(file);
    // Legge il nome dell'evento dal file
    leggi_input_da_file(nome, 102, file);

    // Legge la data di inizio dal file
    Data inizio = leggi_data_da_file(file);
    if (inizio == NULL)
    {
        // Se la lettura della data di inizio fallisce, ritorna NULL
        return NULL;
    }

    // Legge la data di fine dal file
    Data fine = leggi_data_da_file(file);
    if (fine == NULL)
    {
        // Se la lettura della data di fine fallisce, libera la memoria allocata per la data di inizio e ritorna NULL
        libera_data(inizio); 
        return NULL;
    }

    pulisci_buffer(file);

    // Crea un nuovo evento con i dati letti
    Evento evento = crea_evento(nome, tipo, inizio, fine, id);
    if (evento != NULL)
    {
        // Se la creazione dell'evento ha successo, assegna l'id della sala
        evento->sala_id = sala_id;
    }
    else
    {
        // Se la creazione dell'evento fallisce, libera la memoria delle date
        libera_data(inizio);
        libera_data(fine);
    }

    // Ritorna il puntatore all'evento creato
    return evento;
}

// Funzione per liberare la memoria allocata per un evento
void libera_evento(Evento evento)
{
    libera_data(evento->inizio);  // Libera la memoria della data di inizio
    libera_data(evento->fine);    // Libera la memoria della data di fine
    free(evento->nome);           // Libera la memoria del nome
    free(evento);                 // Libera la memoria della struttura evento
}
