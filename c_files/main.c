// file main.c
#include <stdio.h>
#include <stdlib.h>
#include "conferenza.h"

int main(int argc, char **argv)
{
    // Nome di default del file per i dati della conferenza
    char *filename = "conferenza.txt";
    // Se viene fornito un nome file come argomento da linea di comando, usa quello
    if (argc > 1)
    {
        filename = argv[1];
    }

    // Apre il file dei dati della conferenza in modalità lettura
    FILE *conf_file = fopen(filename, "r");
    Conferenza conf = NULL; // Inizializza l'oggetto conferenza a NULL
    if (conf_file != NULL)
    {
        // Legge i dati della conferenza dal file, se esiste
        conf = leggi_conferenza_da_file(conf_file);
        fclose(conf_file); // Chiude il file dopo la lettura
    }
    // Se non è stato possibile leggere i dati della conferenza, crea una nuova conferenza
    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }
    // Se la creazione di una nuova conferenza fallisce, stampa un messaggio di errore ed esce
    if (conf == NULL)
    {
        printf("Errore: impossibile creare la conferenza\n");
        return -1;
    }

    int scelta;
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
        scanf("%d", &scelta);  // Legge la scelta dell'utente
        pulisci_buffer(stdin); // Pulisce il buffer di input per evitare problemi con gli input successivi
        switch (scelta)
        {
        case 1:
            aggiungi_conferenza_evento(conf); // Aggiunge un evento alla conferenza
            break;
        case 2:
            rimuovi_conferenza_evento(conf); // Rimuove un evento dalla conferenza
            break;
        case 3:
            modifica_conferenza_evento(conf); // Modifica un evento nella conferenza
            break;
        case 4:
            stampa_conferenza(conf); // Stampa la lista degli eventi della conferenza
            break;
        case 5:
            aggiungi_conferenza_sala(conf); // Aggiunge una sala alla conferenza
            break;
        case 6:
            stampa_conferenza_sale(conf); // Stampa la lista delle sale della conferenza
            break;
        case 7:
            conferenza_assegna_evento_a_sala(conf); // Assegna una sala a un evento della conferenza
            break;
        case 8:
            printf("Hai scelto Esci dal menu. Arrivederci!\n"); // Messaggio di uscita
            break;
        default:
            printf("Input non valido. Si prega di inserire un numero tra 1 e 8.\n"); // Messaggio per input non valido
        }
    } while (scelta != 8); // Ripete il menu finché l'utente non sceglie di uscire

    // Apre il file dei dati della conferenza in modalità scrittura
    conf_file = fopen(filename, "w");
    if (conf_file == NULL)
    {
        printf("Errore apertura file\n");
        return -2;
    }

    // Salva i dati della conferenza sul file
    salva_conferenza_su_file(conf, conf_file);
    fclose(conf_file); // Chiude il file dopo la scrittura

    // Libera la memoria allocata per la conferenza
    libera_conferenza(conf);

    return 0;
}
