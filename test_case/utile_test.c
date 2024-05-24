#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utile_test.h"

int confronta_file(FILE *f1, FILE *f2)
{
    int temp1 = 0, temp2 = 0, pass = 1;
    while ((temp1 = fgetc(f1)) != EOF && (temp2 = fgetc(f2)) != EOF)
    {
        if (temp1 != temp2)
        {
            pass = 0;
        }
    }
    if (temp1 == EOF && fgetc(f2) != EOF)
    {
        pass = 0;
    }
    else if (temp1 != EOF)
    {
        pass = 0;
    }

    return pass;
}

int aggiungi_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{

    Conferenza conf = leggi_conferenza_da_file(conference_file);

    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }

    if (conf == NULL)
    {
        fprintf(stderr, "Errore ");
        return 0; // Indicate failure
    }

    aggiungi_conferenza_evento(conf);

    salva_conferenza_su_file(conf, output_file);
    fflush(output_file);
    rewind(output_file);

    int pass = confronta_file(oracle_file, output_file);

    libera_conferenza(conf);

    return pass;
}

int rimuovi_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    Conferenza conf = leggi_conferenza_da_file(conference_file);
    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }
    if (conf == NULL)
    {
        return EXIT_FAILURE;
    }
    rimuovi_conferenza_evento(conf);

    salva_conferenza_su_file(conf, output_file);

    fflush(output_file);
    rewind(output_file);

    int pass = confronta_file(oracle_file, output_file);

    libera_conferenza(conf);

    return pass;
}

int modifica_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    Conferenza conf = leggi_conferenza_da_file(conference_file);
    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }
    if (conf == NULL)
    {
        return EXIT_FAILURE;
    }
    modifica_conferenza_evento(conf);
    salva_conferenza_su_file(conf, output_file);

    fflush(output_file);
    rewind(output_file);
    int pass = confronta_file(oracle_file, output_file);

    libera_conferenza(conf);

    return pass;
}

int mostra_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    int pass;
    Conferenza conf = leggi_conferenza_da_file(conference_file);
    if (conf == NULL)
    {
        pass = 0;
        return pass;
    }

    fflush(stdout);
    int fd_output = fileno(output_file);
    int stdout_fd = dup(STDOUT_FILENO);
    dup2(fd_output, STDOUT_FILENO);

    // freopen(NULL, "w", output_file);
    stampa_conferenza(conf);

    fflush(stdout);
    dup2(stdout_fd, STDOUT_FILENO);
    close(stdout_fd);

    fflush(output_file);
    rewind(output_file);

    pass = confronta_file(oracle_file, output_file);

    libera_conferenza(conf);

    return pass;
}
