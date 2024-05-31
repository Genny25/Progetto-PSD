#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utile_test.h"

// Funzione per confrontare due file carattere per carattere
int confronta_file(FILE *f1, FILE *f2)
{
    int temp1 = 0, temp2 = 0, pass = 1;

    // Confronta i file carattere per carattere fino a quando entrambi non raggiungono EOF
    while ((temp1 = fgetc(f1)) != EOF && (temp2 = fgetc(f2)) != EOF)
    {
        if (temp1 != temp2)
        {
            pass = 0; // Se i caratteri sono diversi, setta pass a 0
        }
    }
    // Controlla se uno dei file ha raggiunto EOF prima dell'altro
    if (temp1 == EOF && fgetc(f2) != EOF)
    {
        pass = 0;
    }
    else if (temp1 != EOF)
    {
        pass = 0;
    }

    return pass; // Ritorna 1 se i file sono identici, altrimenti 0
}

// Funzione per aggiungere un evento alla conferenza
int aggiungi_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    // Legge la conferenza dal file
    Conferenza conf = leggi_conferenza_da_file(conference_file);

    // Se il file della conferenza è vuoto, crea una nuova conferenza
    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }

    // Se non riesce a creare o leggere la conferenza, stampa un errore e ritorna 0
    if (conf == NULL)
    {
        fprintf(stderr, "Errore ");
        return 0;
    }

    // Aggiunge un evento alla conferenza
    aggiungi_conferenza_evento(conf);

    // Salva la conferenza aggiornata nel file di output
    salva_conferenza_su_file(conf, output_file);
    fflush(output_file); // forza la scrittura dei dati bufferizzati sul'output
    rewind(output_file); // imposta la posizione del file all'inizio del file del flusso specificato

    // Confronta il file di output con il file oracle
    int pass = confronta_file(oracle_file, output_file);

    // Libera la memoria allocata per la conferenza
    libera_conferenza(conf);

    return pass; // Ritorna il risultato del confronto
}

// Funzione per rimuovere un evento dalla conferenza
int rimuovi_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    // Legge la conferenza dal file
    Conferenza conf = leggi_conferenza_da_file(conference_file);

    // Se il file della conferenza è vuoto, crea una nuova conferenza
    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }

    // Se non riesce a creare o leggere la conferenza, ritorna EXIT_FAILURE
    if (conf == NULL)
    {
        return EXIT_FAILURE;
    }

    // Rimuove un evento dalla conferenza
    rimuovi_conferenza_evento(conf);

    // Salva la conferenza aggiornata nel file di output
    salva_conferenza_su_file(conf, output_file);

    fflush(output_file);
    rewind(output_file);

    // Confronta il file di output con il file oracle
    int pass = confronta_file(oracle_file, output_file);

    // Libera la memoria allocata per la conferenza
    libera_conferenza(conf);

    return pass; // Ritorna il risultato del confronto
}

// Funzione per modificare un evento della conferenza
int modifica_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    // Legge la conferenza dal file
    Conferenza conf = leggi_conferenza_da_file(conference_file);

    // Se il file della conferenza è vuoto, crea una nuova conferenza
    if (conf == NULL)
    {
        conf = nuova_conferenza();
    }

    // Se non riesce a creare o leggere la conferenza, ritorna EXIT_FAILURE
    if (conf == NULL)
    {
        return EXIT_FAILURE;
    }

    // Modifica un evento della conferenza
    modifica_conferenza_evento(conf);

    // Salva la conferenza aggiornata nel file di output
    salva_conferenza_su_file(conf, output_file);

    fflush(output_file);
    rewind(output_file);

    // Confronta il file di output con il file oracle
    int pass = confronta_file(oracle_file, output_file);

    // Libera la memoria allocata per la conferenza
    libera_conferenza(conf);

    return pass; // Ritorna il risultato del confronto
}

// Funzione per mostrare un evento della conferenza
int mostra_evento(FILE *conference_file, FILE *output_file, FILE *oracle_file)
{
    int pass;

    // Legge la conferenza dal file
    Conferenza conf = leggi_conferenza_da_file(conference_file);

    // Se non riesce a leggere la conferenza, setta pass a 0 e ritorna
    if (conf == NULL)
    {
        pass = 0;
        return pass;
    }

    fflush(stdout);

    // Duplica il file descriptor di output
    int fd_output = fileno(output_file);
    int stdout_fd = dup(STDOUT_FILENO);

    // Reindirizza stdout al file di output
    dup2(fd_output, STDOUT_FILENO);

    // Stampa la conferenza sul file di output
    stampa_conferenza(conf);

    fflush(stdout);

    // Ripristina il vecchio stdout
    dup2(stdout_fd, STDOUT_FILENO);
    close(stdout_fd);

    fflush(output_file);
    rewind(output_file);

    // Confronta il file di output con il file oracle
    pass = confronta_file(oracle_file, output_file);

    // Libera la memoria allocata per la conferenza
    libera_conferenza(conf);

    return pass; // Ritorna il risultato del confronto
}
