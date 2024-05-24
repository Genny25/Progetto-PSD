#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utile_test.h"

#define M 30

int run_test_case(char *tc_id, int input_choice)
{
    char input_fname[M], output_fname[M], oracle_fname[M], conference_name[M];
    char temp[100];

    strcpy(input_fname, tc_id);
    strcat(input_fname, "/input.txt");

    strcpy(oracle_fname, tc_id);
    strcat(oracle_fname, "/oracle.txt");

    strcpy(output_fname, tc_id);
    strcat(output_fname, "/output.txt");

    strcpy(conference_name, tc_id);
    strcat(conference_name, "/conferenza.txt");

    FILE *conferenza_file = fopen(conference_name, "r");

    FILE *oracle_file = fopen(oracle_fname, "r");
    if (oracle_file == NULL)
    {
        printf("Errore nell'apertura del file di output %s\n", oracle_fname);
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(output_fname, "w+");
    if (output_file == NULL)
    {
        printf("Errore nell'apertura del file di output %s\n", output_fname);
        exit(EXIT_FAILURE);
    }

    fflush(stdin);
    if (freopen(input_fname, "r", stdin) == NULL)
    {
        printf("Errore nell'apertura del file di input %s\n", temp);
        exit(EXIT_FAILURE);
    }

    int pass = 0;

    // Execute the operations specified in the input file
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

    // Close the input file
    fclose(conferenza_file);
    fclose(output_file);
    fclose(oracle_file);
    // Return 1 if the files match, otherwise return 0
    return pass;
}

int main(int argc, char *argv[])
{
    FILE *test_suite, *result;
    char tc_id[M];
    int n, pass;

    if (argc < 3)
    {
        printf("Nomi dei file mancanti \n");
        exit(1);
    }

    test_suite = fopen(argv[1], "r");
    result = fopen(argv[2], "w");

    if (test_suite == NULL || result == NULL)
    {
        printf("Errore in apertura dei file \n");
        exit(1);
    }

    while (fscanf(test_suite, "%s %d", tc_id, &n) == 2)
    {
        pass = run_test_case(tc_id, n);

        fprintf(result, "%s ", tc_id);
        if (pass == 1)
            fprintf(result, "PASS \n");
        else
            fprintf(result, "FAIL \n");
    }
    fclose(test_suite);
    fclose(result);
}
