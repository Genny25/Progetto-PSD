
#include <stdio.h>
#include <stdlib.h>
#include "utile.h"
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
        printf("5. Esci dal menu\n");
        printf("\nOperazione:> ");
        scanf("%d", &scelta);
        pulisci_buffer();
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
            printf("Hai scelto Esci dal menu. Arrivederci!\n");
            break;
        default:
            printf("Input non valido. Si prega di inserire un numero tra 1 e 5.\n");
        }
    } while (scelta != 5);

    return 0;
}
