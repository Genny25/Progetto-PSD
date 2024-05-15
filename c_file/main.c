// file main.c

#include <stdio.h>
#include <stdlib.h>

#include "conferenza.h"

int main()
{
    conferenza conf = nuova_conferenza();
    int scelta, temp;
    do
    {
        printf("\n\n");
        printf("1. Aggiungi evento \n");
        printf("2. Rimuovi evento \n");
        printf("3. Modifica  evento \n");
        printf("4. Mostra eventi \n");
        printf("5. Aggiungi sala \n");
        printf("6. Mostra sale \n");
        printf("7. Assegna sala ad evento \n");
        printf("8. Esci dal menu\n");
        printf("\nOperazione:> ");
        scanf("%d", &scelta);
        pulisci_buffer(stdin);
        switch (scelta)
        {
        case 1:
            aggiungi_conferenza_evento(conf);
            break;
        case 2:
            rimuovi_conferenza_evento(conf);
            break;
        case 3:
            modifica_conferenza_evento(conf);
            break;
        case 4:
            stampa_conferenza(conf);
            break;
        case 5:
            aggiungi_conferenza_sala(conf);
            break;
        case 6:
            stampa_conferenza_sale(conf);
            break;
        case 7:
            conferenza_assegna_evento_a_sala(conf);
            break;
        case 8:
            printf("Hai scelto Esci dal menu. Arrivederci!\n");
            break;
        default:
            printf("Input non valido. Si prega di inserire un numero tra 1 e 8.\n");
        }
    } while (scelta != 8);

    return 0;
}
