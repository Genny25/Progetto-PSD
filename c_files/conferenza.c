

// file conferenza.c

#include <stdio.h>
#include <stdlib.h>

#include "conferenza.h"

// Struttura per rappresentare una conferenza
struct ConferenzaStruct
{
    eventoBst bst;      // Albero binario di ricerca degli eventi
    int id_evento;      // Contatore per gli ID degli eventi
    int id_sala;        // Contatore per gli ID delle sale
    ListaSala sale;     // Lista delle sale disponibili
};

// Funzione per creare una nuova conferenza
Conferenza nuova_conferenza()
{
    eventoBst bst = nuovo_evento_bst(); // Crea un nuovo albero per gli eventi
    if (bst == NULL)
    {
        return NULL; // Restituisce NULL se non è possibile allocare memoria per l'albero
    }
    ListaSala sala_lista = nuova_lista_sala(); // Crea una nuova lista per le sale
    if (sala_lista == NULL)
    {
        return NULL; // Restituisce NULL se non è possibile allocare memoria per la lista
    }

    // Alloca memoria per la struttura della conferenza
    Conferenza conf = my_alloc(1, sizeof(*conf));
    if (conf == NULL)
    {
        libera_evento_bst(bst); // Libera la memoria dell'albero in caso di errore
        return NULL; // Restituisce NULL se non è possibile allocare memoria per la conferenza
    }
    // Inizializza i campi della conferenza
    conf->bst = bst;
    conf->sale = sala_lista;
    conf->id_evento = 0;
    conf->id_sala = 1;

    return conf; // Restituisce la nuova conferenza
}

// Funzione per aggiungere un nuovo evento alla conferenza
int aggiungi_conferenza_evento(Conferenza conf)
{
    Evento evento = input_evento(conf->id_evento); // Ottiene un nuovo evento dall'input utente
    if (evento == NULL)
    {
        return -1; // Restituisce -1 se l'input è invalido o se si verifica un errore
    }
    if (inserisci_evento_bst(conf->bst, evento)) // Inserisce l'evento nell'albero degli eventi
    {
        libera_evento(evento); // Libera la memoria dell'evento in caso di errore
    }
    conf->id_evento++; // Incrementa l'ID degli eventi per la prossima aggiunta

    return 0; // Restituisce 0 in caso di successo
}

// Funzione per aggiungere una nuova sala alla conferenza
int aggiungi_conferenza_sala(Conferenza conf)
{
    Sala s = input_sala(conf->id_sala); // Ottiene una nuova sala dall'input utente
    if (s == NULL)
    {
        return -1; // Restituisce -1 se l'input è invalido o se si verifica un errore
    }
    aggiungi_sala_lista(conf->sale, s); // Aggiunge la sala alla lista delle sale
    conf->id_sala++; // Incrementa l'ID delle sale per la prossima aggiunta
    return 0; // Restituisce 0 in caso di successo
}

// Funzione per rimuovere un evento dalla conferenza
int rimuovi_conferenza_evento(Conferenza conf)
{
    stampa_evento_bst(conf->bst, conf->sale); // Stampa gli eventi della conferenza
    int res;
    while (1)
    {
        printf("Inserisci l'id dell'evento da rimuovere [inserire un numero negativo per annullare l'operazione]:> ");
        res = leggi_intero(); // Legge l'ID dell'evento dall'input utente
        if (res < 0)
        {
            return 1; // Esce se l'utente sceglie di annullare l'operazione
        }

        Evento rimuovi = bst_rimuovi_evento_by_id(conf->bst, res); // Rimuove l'evento dall'albero
        if (rimuovi == NULL)
        {
            printf("L'evento non è presente nella conferenza\n");
            return -1; // Restituisce -1 se l'evento non è presente nella conferenza
        }
        libera_evento(rimuovi); // Libera la memoria dell'evento rimosso
        printf("Evento rimosso correttamente\n");
        return 0; // Restituisce 0 in caso di successo
    }
}

// Funzione per modificare il nome di un evento nella conferenza
int modifica_nome_conferenza_evento(Conferenza conf, Evento evento)
{
    char temp[101];
    printf("inserisci nome evento [Max 100 caratteri]:> ");
    if (leggi_input(temp, sizeof(temp)))
    {
        puts("Nome non valido");
        return -1; // Restituisce -1 se l'input del nome è invalido
    }

    if (imposta_nome(evento, temp)) // Imposta il nuovo nome per l'evento
    {
        puts("Errore nella modifica del nome");
        return -1; // Restituisce -1 in caso di errore
    }

    return 0; // Restituisce 0 in caso di successo
}

// Funzione per modificare la data di inizio di un evento nella conferenza
int modifica_data_inizio_conferenza_evento(Conferenza conf, Evento evento)
{
    Data data = NULL;
    do
    {
        printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm):> ");
        data = input_data(); // Legge la nuova data di inizio dall'input utente
    } while (data == NULL && printf("Data inserita non valida\n")); // Ripete finché l'input non è valido
    return imposta_data_inizio(evento, data); // Imposta la nuova data di inizio per l'evento
}

// Funzione per modificare la data di fine di un evento nella conferenza
int modifica_data_fine_conferenza_evento(Conferenza conf, Evento evento)
{
    Data data = NULL;
    do
    {
        printf("Inserisci data fine evento (DD/MM/AAAA hh:mm):> ");
        data = input_data(); // Legge la nuova data di fine dall'input utente
    } while (data == NULL && printf("Data inserita non valida\n")); // Ripete finché l'input non è valido
    return imposta_data_fine(evento, data); // Imposta la nuova data di fine per l'evento
}

// Funzione per modificare il tipo di un evento nella conferenza
int modifica_tipo_conferenza_evento(Conferenza conf, Evento evento)
{
    int tipo;
    do
    {
        printf("\nTipologie Evento\n");
        printf("[1]: Workshop\n");
        printf("[2]: Sessione di keynote\n");
        printf("[3]: Panel di discussione\n");
        printf("Seleziona tipologia evento (1, 2 o 3):> ");
        scanf("%d", &tipo); // Legge il tipo di evento dall'input utente
        pulisci_buffer(stdin);
    } while (tipo < 1 || tipo > 3); // Ripete finché l'input non è valido

    if (imposta_tipo(evento, tipo)) // Imposta il nuovo tipo per l'evento
    {
        puts("Errore nella modifica del tipo");
        return -1; // Restituisce -1 in caso di errore
    }

    return 0; // Restituisce 0 in caso di successo
}

// Funzione per modificare un evento nella conferenza
int modifica_conferenza_evento(Conferenza conf)
{
    int res, scelta, flag = 1;

    stampa_evento_bst(conf->bst, conf->sale); // Stampa gli eventi della conferenza

    while (1)
    {
        printf("Inserisci l'id dell'evento da modificare [inserire un numero negativo per annullare l'operazione]:> ");
        res = leggi_intero(); // Legge l'ID dell'evento dall'input utente
        if (res < 0)
        {
            return 1; // Esce se l'utente sceglie di annullare l'operazione
        }

        Evento modifica = bst_rimuovi_evento_by_id(conf->bst, res); // Rimuove l'evento dall'albero
        if (modifica == NULL)
        {
            printf("Errore nella ricerca dell'evento\n");
            return -1; // Restituisce -1 se si verifica un errore nella ricerca dell'evento
        }

        do
        {
            printf("\n");
            printf("1 - Nome\n");
            printf("2 - Data inizio\n");
            printf("3 - Data fine\n");
            printf("4 - Tipo\n");
            printf("5-  Esci dal menu\n");
            printf("Inserisci il campo da modificare:> ");
            scanf("%d", &scelta); // Legge la scelta dall'input utente
            pulisci_buffer(stdin);
            switch (scelta)
            {
            case 1:
                modifica_nome_conferenza_evento(conf, modifica);
                break;
            case 2:
                modifica_data_inizio_conferenza_evento(conf, modifica);
                break;
            case 3:
                modifica_data_fine_conferenza_evento(conf, modifica);
                break;
            case 4:
                modifica_tipo_conferenza_evento(conf, modifica);
                break;
            default:
                printf("Errore nella scelta\n");
                break;
            }
        } while (scelta != 5); // Continua finché l'utente non sceglie di uscire

        if (flag)
        {
            printf("\n\n");
            Sala s = sala_per_id_lista(conf->sale, prendi_evento_sala_id(modifica)); // Ottiene la sala dell'evento modificato
            stampa_evento(modifica, s); // Stampa le informazioni dell'evento modificato
            printf("\n\n");
        }

        if (inserisci_evento_bst(conf->bst, modifica)) // Reinserisce l'evento nell'albero
        {
            libera_evento(modifica); // Libera la memoria dell'evento in caso di errore
            puts("Errore durante la modifica");
            return -1; // Restituisce -1 in caso di errore
        }
        puts("Evento modifica correttamente");
        return 0; // Restituisce 0 in caso di successo
    }
}

// Funzione per stampare tutti gli eventi della conferenza
int stampa_conferenza(Conferenza conf)
{
    stampa_evento_bst(conf->bst, conf->sale); // Stampa gli eventi della conferenza
    return 0; // Restituisce 0 in caso di successo
}

// Funzione per stampare tutte le sale della conferenza
int stampa_conferenza_sale(Conferenza conf)
{
    stampa_lista_sala(conf->sale); // Stampa le sale della conferenza
    return 0; // Restituisce 0 in caso di successo
}

// Funzione per assegnare un evento a una sala nella conferenza
int conferenza_assegna_evento_a_sala(Conferenza conf)
{
    int res = 0;
    Evento evento = NULL;
    if (prendi_dimensione_lista_sala(conf->sale) == 0)
    {
        printf("Non ci sono sale disponibili.\n");
        return -1; // Restituisce -1 se non ci sono sale disponibili
    }
    stampa_evento_bst(conf->bst, conf->sale); // Stampa gli eventi della conferenza
    while (1)
    {
        printf("Inserisci l'id dell'evento da assegnare [inserire un numero negativo per annullare l'operazione]:> ");
        res = leggi_intero(); // Legge l'ID dell'evento dall'input utente
        if (res < 0)
        {
            return 1; // Esce se l'utente sceglie di annullare l'operazione
        }

        evento = bst_prendi_evento_by_id(conf->bst, res); // Ottiene l'evento dall'albero

        stampa_lista_sala(conf->sale); // Stampa le sale disponibili

        int pos = 0;
        do
        {
            printf("Inserisci numero sala: ");
            int res_sala = leggi_intero(); // Legge il numero della sala dall'input utente
            pos = res_sala - 1;

        } while ((pos < 0 || pos >= prendi_dimensione_lista_sala(conf->sale)) && printf("Numero sala inseriro non valido\n")); // Ripete finché l'input non è valido

        Sala s = sala_in_posizione_lista(conf->sale, pos); // Ottiene la sala dalla lista
        if (s == NULL)
        {
            printf("Qualcosa è andato storto durante la ricerca della sala\n");
            return -2; // Restituisce -2 se si verifica un errore durante la ricerca della sala
        }

        imposta_evento_sala_id(evento, prendi_sala_id(s)); // Imposta l'ID della sala per l'evento
        printf("Sala assegnata con successo\n");

        return 0; // Restituisce 0 in caso di successo
    }
}

// Funzione per salvare la conferenza su un file
void salva_conferenza_su_file(Conferenza conf, FILE *file)
{
    if (conf == NULL || file == NULL)
    {
        perror("Puntatore alla conferenza o al file non valido");
        return; // Esce se la conferenza o il file non sono validi
    }

    // Salva i contatori degli ID degli eventi e delle sale
    fprintf(file, "%d %d\n", conf->id_evento, conf->id_sala);

    // Salva gli eventi
    salva_evento_bst_su_file(conf->bst, file);

    // Salva le sale
    salva_lista_sala_su_file(conf->sale, file);
}

// Funzione per leggere la conferenza da un file
Conferenza leggi_conferenza_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("Puntatore al file non valido");
        return NULL; // Esce se il file non è valido
    }

    // Legge i contatori degli ID degli eventi e delle sale
    int evento_id = 0;
    int sala_id = 0;
    if (fscanf(file, "%d %d", &evento_id, &sala_id) != 2)
    {
        perror("Errore nella lettura del contatore ID evento e del contatore ID sala");
        return NULL; // Esce se si verifica un errore nella lettura degli ID
    }
    pulisci_buffer(file);

    // Crea una nuova conferenza
    Conferenza conf = nuova_conferenza();
    if (conf == NULL)
    {
        perror("Errore nella creazione di una nuova conferenza");
        return NULL; // Esce se si verifica un errore nella creazione della conferenza
    }

    conf->id_evento = evento_id;
    conf->id_sala = sala_id;

    // Legge gli eventi
    conf->bst = leggi_evento_bst_da_file(file);
    if (conf->bst == NULL)
    {
        perror("Errore nella lettura degli eventi");
        libera_conferenza(conf);
        return NULL; // Esce se si verifica un errore nella lettura degli eventi
    }

    // Legge le sale
    conf->sale = leggi_lista_sala_da_file(file);
    if (conf->sale == NULL)
    {
        perror("Errore nella lettura delle sale");
        libera_conferenza(conf);
        return NULL; // Esce se si verifica un errore nella lettura delle sale
    }

    return conf; // Restituisce la conferenza letta dal file
}

// Funzione per liberare la memoria allocata per la conferenza
void libera_conferenza(Conferenza conf)
{
    libera_evento_bst(conf->bst);  // Libera l'albero degli eventi
    libera_lista_sala(conf->sale); // Libera la lista delle sale
    free(conf);  // Libera la memoria della struttura conferenza
}
