#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utile_test.h"

#define M 30 // Definisce una costante M che rappresenta la lunghezza massima per i nomi dei file

// Funzione che esegue un caso di test specificato da tc_id e input_choice
int run_test_case(char *tc_id, int input_choice)
{
    char input_fname[M], output_fname[M], oracle_fname[M], conference_name[M];
    char temp[100];

    // Costruisce il nome del file di input usando tc_id
    strcpy(input_fname, tc_id);
    strcat(input_fname, "/input.txt");

    // Costruisce il nome del file oracle usando tc_id
    strcpy(oracle_fname, tc_id);
    strcat(oracle_fname, "/oracle.txt");

    // Costruisce il nome del file di output usando tc_id
    strcpy(output_fname, tc_id);
    strcat(output_fname, "/output.txt");

    // Costruisce il nome del file conferenza usando tc_id
    strcpy(conference_name, tc_id);
    strcat(conference_name, "/conferenza.txt");

    // Apre il file conferenza in modalità lettura
    FILE *conferenza_file = fopen(conference_name, "r");

    // Apre il file oracle in modalità lettura
    FILE *oracle_file = fopen(oracle_fname, "r");
    if (oracle_file == NULL)
    {
        printf("Errore nell'apertura del file di output %s\n", oracle_fname);
        exit(EXIT_FAILURE);
    }

    // Apre il file di output in modalità scrittura
    FILE *output_file = fopen(output_fname, "w+");
    if (output_file == NULL)
    {
        printf("Errore nell'apertura del file di output %s\n", output_fname);
        exit(EXIT_FAILURE);
    }

    // Reindirizza lo stdin al file di input
    fflush(stdin);
    if (freopen(input_fname, "r", stdin) == NULL)
    {
        printf("Errore nell'apertura del file di input %s\n", temp);
        exit(EXIT_FAILURE);
    }

    int pass = 0;

    // Esegue l'operazione specificata in input_choice
    switch (input_choice)
    {
    case 1:
        pass = aggiungi_evento(conferenza_file, output_file, oracle_file);
        break;
    case 2:
        pass = rimuovi_evento(conferenza_file, output_file, oracle_file);
        break;
    case 3:
        pass = modifica_evento(conferenza_file, output_file, oracle_file);
        break;
    case 4:
        pass = mostra_evento(conferenza_file, output_file, oracle_file);
        break;
    default:
        printf("Invalid operation in the input file\n");
        break;
    }

    // Chiude i file aperti
    fclose(conferenza_file);
    fclose(output_file);
    fclose(oracle_file);
    // Restituisce 1 se i file corrispondono, altrimenti restituisce 0
    return pass;
}

int main(int argc, char *argv[])
{
    FILE *test_suite, *result;
    char tc_id[M];
    int n, pass;

    // Controlla se il numero di argomenti è sufficiente
    if (argc < 3)
    {
        printf("Nomi dei file mancanti \n");
        exit(1);
    }

    // Apre il file di suite di test e il file di risultati
    test_suite = fopen(argv[1], "r");
    result = fopen(argv[2], "w");

    // Controlla se i file sono stati aperti correttamente
    if (test_suite == NULL || result == NULL)
    {
        printf("Errore in apertura dei file \n");
        exit(1);
    }

    // Legge i casi di test dal file di suite di test e li esegue uno per uno
    while (fscanf(test_suite, "%s %d", tc_id, &n) == 2)
    {
        pass = run_test_case(tc_id, n);

        // Scrive il risultato del caso di test nel file di risultati
        fprintf(result, "%s ", tc_id);
        if (pass == 1)
            fprintf(result, "PASS \n");
        else
            fprintf(result, "FAIL \n");
    }
    // Chiude i file di suite di test e di risultati
    fclose(test_suite);
    fclose(result);
}
