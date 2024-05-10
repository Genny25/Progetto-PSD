
#include <stdio.h>
#include <stdlib.h>
#include "utile.h"
#include "data.h"
#include "conferenza.h"

struct ConferenceStruct
{
    eventBst bst;
};

conferenza nuova_conferenza()
{
    eventBst bst = nuovo_evento_bst();
    if (bst == NULL)
    {
        return NULL;
    }

    conferenza conf = malloc(sizeof(*conf));
    if (conf == NULL)
    {
        free_event_bst(bst);
        return NULL;
    }
    conf->bst = bst;
    return conf;
}

int aggiungi_conferenza_evento(conferenza conf)
{
    event evento = input_evento();
    if (evento == NULL)
    {
        return -1;
    }
    inserisci_evento_bst(conf->bst, evento);
    return 0;
}

int rimuovi_conferenza_evento(conferenza conf)
{
    stampa_evento_bst(conf->bst);
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

int modifica_data_conferenza_evento(conferenza conf, event evento)
{
    Date data = NULL;
    do
    {
        printf("Inserisci data evento (DD/MM/AAAA hh:mm):> ");
        data = input_data();
    } while (data == NULL && printf("Data inserita non valida\n"));
    return set_data(evento, data);
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
        pulisci_buffer();
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

    stampa_evento_bst(conf->bst);

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
            printf("2 - Data\n");
            printf("3 - Tipo\n");
            printf("4-  Esci dal menu\n");
            printf("Inserisci il campo da modificare:> ");
            scanf("%d", &scelta);
            pulisci_buffer();
            switch (scelta)
            {
            case 1:
                modifica_nome_conferenza_evento(conf, modifica);
                break;
            case 2:
                modifica_data_conferenza_evento(conf, modifica);
                break;
            case 3:
                modifica_tipo_conferenza_evento(conf, modifica);
                break;
            default:
                printf("Errore nella scelta\n");
                break;
            }
        } while (scelta != 4);

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
    stampa_evento_bst(conf->bst);
    return 0;
}

void free_conferenza(conferenza conf)
{
    free_event_bst(conf->bst);
    free(conf);
}