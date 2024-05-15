// file conferenza.c

#include <stdio.h>
#include <stdlib.h>
#include "utile.h"
#include "data.h"
#include "bst_evento.h"
#include "sala.h"
#include "lista_sala.h"
#include "conferenza.h"

struct ConferenceStruct
{
    eventBst bst;
    int id_evento;
    int id_sala;
    listaSala sale;
};

conferenza nuova_conferenza()
{
    eventBst bst = nuovo_evento_bst();
    if (bst == NULL)
    {
        return NULL;
    }
    listaSala sala_lista = nuova_lista_sala();
    if (sala_lista == NULL)
    {
        return NULL;
    }

    conferenza conf = my_alloc(1, sizeof(*conf));
    if (conf == NULL)
    {
        free_event_bst(bst);
        return NULL;
    }
    conf->bst = bst;
    conf->sale = sala_lista;
    conf->id_evento = 0;
    conf->id_sala = 1;

    return conf;
}

int aggiungi_conferenza_evento(conferenza conf)
{
    event evento = input_evento(conf->id_evento);
    if (evento == NULL)
    {
        return -1;
    }
    if (inserisci_evento_bst(conf->bst, evento))
    {
        free_event(evento);
    }
    conf->id_evento++;

    return 0;
}

int aggiungi_conferenza_sala(conferenza conf)
{
    sala s = input_sala(conf->id_sala);
    if (s == NULL)
    {
        return -1;
    }
    aggiungi_sala_lista(conf->sale, s);
    conf->id_sala++;
    return 0;
}

int rimuovi_conferenza_evento(conferenza conf)
{
    stampa_evento_bst(conf->bst, conf->sale);
    int res;
    while (1)
    {
        printf("Inserisci l'id dell'evento da rimuovere [inserire un numero negativo per annullare l'operazione]:> ");
        res = leggi_intero();
        if (res < 0)
        {
            return 1;
        }

        event rimuovi = bst_rimuovi_evento_by_id(conf->bst, res);
        if (rimuovi == NULL)
        {
            printf("L'evento non è presente nella conferenza\n");
            return -1;
        }
        free_event(rimuovi);
        printf("Evento rimosso correttamente\n");
        return 0;
    }
}

int modifica_nome_conferenza_evento(conferenza conf, event evento)
{
    char temp[101];
    printf("inserisci nome evento [Max 100 caratteri]:> ");
    if (leggi_input(temp, sizeof(temp)))
    {
        puts("Nome non valido");
        return -1;
    }

    if (set_nome(evento, temp))
    {
        puts("Errore nella modifica del nome");
        return -1;
    }

    return 0;
}

int modifica_data_inizio_conferenza_evento(conferenza conf, event evento)
{
    Date data = NULL;
    do
    {
        printf("Inserisci data inizio evento (DD/MM/AAAA hh:mm):> ");
        data = input_data();
    } while (data == NULL && printf("Data inserita non valida\n"));
    return set_data_inizio(evento, data);
}

int modifica_data_fine_conferenza_evento(conferenza conf, event evento)
{
    Date data = NULL;
    do
    {
        printf("Inserisci data fine evento (DD/MM/AAAA hh:mm):> ");
        data = input_data();
    } while (data == NULL && printf("Data inserita non valida\n"));
    return set_data_fine(evento, data);
}

int modifica_tipo_conferenza_evento(conferenza conf, event evento)
{
    int tipo;
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

    if (set_tipo(evento, tipo))
    {
        puts("Errore nella modifica del tipo");
        return -1;
    }

    return 0;
}

int modifica_conferenza_evento(conferenza conf)
{
    int res, scelta, flag = 1;

    stampa_evento_bst(conf->bst, conf->sale);

    while (1)
    {
        printf("Inserisci l'id dell'evento da modificare [inserire un numero negativo per annullare l'operazione]:> ");
        res = leggi_intero();
        if (res < 0)
        {
            return 1;
        }

        event modifica = bst_rimuovi_evento_by_id(conf->bst, res);
        if (modifica == NULL)
        {
            printf("Errore nella ricerca dell'evento\n");
            return -1;
        }

        do
        {
            printf("1 - Nome\n");
            printf("2 - Data inizio\n");
            printf("3 - Data fine\n");
            printf("4 - Tipo\n");
            printf("5-  Esci dal menu\n");
            printf("Inserisci il campo da modificare:> ");
            scanf("%d", &scelta);
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
        } while (scelta != 5);

        if (flag)
        {
            printf("\n\n");
            sala s = sala_per_id_lista(conf->sale, get_evento_sala_id(modifica));
            stampa_evento(modifica, s);
            printf("\n\n");
        }

        if (inserisci_evento_bst(conf->bst, modifica))
        {
            free_event(modifica);
            puts("Errore durante la modifica");
            return -1;
        }
        puts("Evento modifica correttamente");
        return 0;
    }
}

int stampa_conferenza(conferenza conf)
{
    stampa_evento_bst(conf->bst, conf->sale);
    return 0;
}

int stampa_conferenza_sale(conferenza conf)
{
    stampa_lista_sala(conf->sale);
    return 0;
}

int conferenza_assegna_evento_a_sala(conferenza conf)
{
    int res = 0;
    event evento = NULL;
    if (get_dimensione_lista_sala(conf->sale) == 0)
    {
        printf("Non ci sono sale disponibili.\n");
        return -1;
    }
    stampa_evento_bst(conf->bst, conf->sale);
    while (1)
    {
        printf("Inserisci l'id dell'evento da assegnare [inserire un numero negativo per annullare l'operazione]:> ");
        res = leggi_intero();
        if (res < 0)
        {
            return 1;
        }

        evento = bst_get_evento_by_id(conf->bst, res);

        stampa_lista_sala(conf->sale);

        int pos = 0;
        do
        {
            printf("Inserisci numero sala: ");
            int res_sala = leggi_intero();
            pos = res_sala - 1;

        } while ((pos < 0 || pos >= get_dimensione_lista_sala(conf->sale)) && printf("Numero sala inseriro non valido\n"));

        sala s = sala_in_posizione_lista(conf->sale, pos);
        if (s == NULL)
        {
            printf("Qualcosa è andato storto durante la ricerca della sala\n");
            return -2;
        }

        set_evento_sala_id(evento, get_sala_id(s));
        printf("Sala assegnata con successo\n");

        return 0;
    }
}

void free_conferenza(conferenza conf)
{
    free_event_bst(conf->bst);
    free_lista_sala(conf->sale);
    free(conf);
}

void salva_conferenza_su_file(conferenza conf, FILE *file)
{
    if (conf == NULL || file == NULL)
    {
        perror("Invalid conference or file pointer");
        return;
    }

    // Save event ID counter and room ID counter
    fprintf(file, "%d %d\n", conf->id_evento, conf->id_sala);

    // Save events
    salva_evento_bst_su_file(conf->bst, file);

    // Save rooms
    salva_lista_sala_su_file(conf->sale, file);
}

conferenza leggi_conferenza_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("Invalid file pointer");
        return NULL;
    }

    // Read event ID counter and room ID counter
    int evento_id = 0;
    int sala_id = 0;
    if (fscanf(file, "%d %d", &evento_id, &sala_id) != 2)
    {
        perror("Error reading event ID counter and room ID counter");
        return NULL;
    }
    pulisci_buffer(file);

    // Create a new conference
    conferenza conf = nuova_conferenza;
    if (conf == NULL)
    {
        perror("Error creating new conference");
        return NULL;
    }

    conf->id_evento = evento_id;
    conf->id_sala = sala_id;

    // Read events
    conf->bst = leggi_evento_bst_da_file(file);
    if (conf->bst == NULL)
    {
        perror("Error reading events");
        free_conference(conf);
        return NULL;
    }

    // Read rooms
    conf->sale = leggi_lista_sala_da_file(file);
    if (conf->sale == NULL)
    {
        perror("Error reading rooms");
        free_conferenza(conf);
        return NULL;
    }

    return conf;
}