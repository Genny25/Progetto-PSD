// file sala.c
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sala.h"

struct StructSala
{
    int id;
    char *nome;
};

sala nuova_sala(char *nome, int id)
{
    sala s = my_alloc(1, sizeof(*s));
    s->nome = my_strdup(nome);
    s->id = id;

    return s;
}

bool eq_sale(sala s1, sala s2)
{
    if (s1 == s2)
    {
        return true;
    }
    return s1 != NULL && s2 != NULL && s1->id == s2->id;
}

sala input_sala(int id)
{
    char nome[101] = {0};

    while (1)
    {
        char temp[101] = {0};
        printf("Inserisci nome sala [Max 100 caratteri]: ");
        if (leggi_input(temp, 101))
        {
            printf("Nome troppo lungo\n");
            continue;
        }

        sscanf(temp, "%[^\n]", nome);
        if (strlen(nome) == 0)
        {
            continue;
        }
        break;
    }

    sala s = nuova_sala(nome, id);
    return s;
}

char *get_sala_nome(sala s)
{
    return s->nome;
}

int get_sala_id(sala s)
{
    return s->id;
}

void stampa_sala(sala s)
{
    printf("%s", s->nome);
}

void free_sala(sala s)
{
    free(s->nome);
    free(s);
}

// Function to save a Room structure to a file
void salva_sala_su_file(sala s, FILE *file)
{
    if (s == NULL || file == NULL)
    {
        return;
    }

    // Write Room data to the file
    fprintf(file, "%d\n", s->id);   // Write room ID
    fprintf(file, "%s\n", s->nome); // Write room name
}

// Function to read a Room structure from a file
sala leggi_sala_da_file(FILE *file)
{
    if (file == NULL)
    {
        return NULL;
    }

    // Read room ID from the file
    int id;
    if (fscanf(file, "%d", &id) != 1)
    {
        pulisci_buffer(file); // Clean the file buffer
        return NULL;
    }

    pulisci_buffer(file); // Clean the file buffer

    // Read room name from the file
    char nome[102];
    if (leggi_input_da_file(nome, 102, file) != 0)
    {
        return NULL;
    }

    // Create and return a new Room structure
    return nuova_sala(nome, id);
}
