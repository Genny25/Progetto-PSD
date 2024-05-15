// file bst_evento.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_evento.h"

typedef struct eventBstNodeStruct *eventBstNode;

struct eventBstNodeStruct
{
    event value;
    eventBstNode parent;
    eventBstNode left;
    eventBstNode right;
};

struct eventBstStruct
{
    eventBstNode root;
    int size;
};

eventBst nuovo_evento_bst()
{
    eventBst new = malloc(sizeof(*new));
    if (new == NULL)
    {
        return NULL;
    }
    new->root = NULL;
    new->size = 0;
    return new;
}

int inserisci_evento_bst(eventBst bst, event evento)
{
    if (bst == NULL)
    {
        printf("Errore");
        return -1;
    }

    eventBstNode new = calloc(1, sizeof(struct eventBstNodeStruct));
    if (new == NULL)
    {
        printf("Errore");
        return -1;
    }

    new->value = evento;

    eventBstNode parent = NULL;

    eventBstNode temp = bst->root;
    while (temp != NULL)
    {
        parent = temp;
        if (confronta_eventi(new->value, parent->value) < 0)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }

    new->parent = parent;

    if (parent == NULL)
    {
        bst->root = new;
    }
    else if (confronta_eventi(new->value, parent->value) < 0)
    {
        parent->left = new;
    }
    else
    {
        parent->right = new;
    }
    bst->size += 1;
    return 0;
}

eventBstNode bst_cerca_evento(eventBst bst, event evento)
{
    eventBstNode result = bst->root;
    while (result != NULL && !equal_id(evento, result->value))
    {
        if (confronta_eventi(evento, result->value) < 0)
        {
            result = result->left;
        }
        else
        {
            result = result->right;
        }
    }
    return result;
}

eventBstNode bst_cerca_nodi_evento_by_id(eventBstNode node, int id)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (get_id(node->value) == id)
    {
        return node;
    }
    eventBstNode temp = NULL;
    temp = bst_cerca_nodi_evento_by_id(node->left, id);
    if (temp != NULL)
    {
        return temp;
    }
    return bst_cerca_nodi_evento_by_id(node->right, id);
}

eventBstNode bst_cerca_evento_by_id(eventBst bst, int id)
{
    return bst_cerca_nodi_evento_by_id(bst->root, id);
}

void bst_shift_nodi(eventBst bst, eventBstNode node1, eventBstNode node2)
{
    if (node1->parent == NULL)
    {
        bst->root = node2;
    }
    else if (node1 == node1->parent->left)
    {
        node1->parent->left = node2;
    }
    else
    {
        node1->parent->right = node2;
    }
    if (node2 != NULL)
    {
        node2->parent = node1->parent;
    }
}

eventBstNode bst_massimo(eventBstNode node)
{
    if (node == NULL)
    {
        return NULL;
    }
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

eventBstNode bst_minimo(eventBstNode node)
{
    if (node == NULL)
    {
        return NULL;
    }
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

eventBstNode bst_precedente(eventBstNode node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->left != NULL)
    {
        return bst_massimo(node->left);
    }
    eventBstNode res = node->parent;
    while (res != NULL && node == res->left)
    {
        node = res;
        res = res->parent;
    }
    return res;
}

eventBstNode bst_successivo(eventBstNode node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->right != NULL)
    {
        return bst_minimo(node->right);
    }
    eventBstNode res = node->parent;
    while (res != NULL && node == res->right)
    {
        node = res;
        res = res->parent;
    }
    return res;
}

event bst_rimuovi_nodo(eventBst bst, eventBstNode node)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->left == NULL)
    {
        bst_shift_nodi(bst, node, node->right);
    }
    else if (node->right == NULL)
    {
        bst_shift_nodi(bst, node, node->left);
    }
    else
    {
        eventBstNode temp = bst_successivo(node);
        if (temp->parent != node)
        {
            bst_shift_nodi(bst, temp, temp->right);
            temp->right = node->right;
            temp->right->parent = temp;
        }
        bst_shift_nodi(bst, node, temp);
        temp->left = node->left;
        temp->left->parent = temp;
    }
    event value = node->value;
    free(node);
    bst->size--;
    return value;
}

event bst_rimuovi_evento(eventBst bst, event evento)
{
    eventBstNode node = bst_cerca_evento(bst, evento);
    return bst_rimuovi_nodo(bst, node);
}

event bst_rimuovi_evento_by_id(eventBst bst, int id)
{
    eventBstNode node = bst_cerca_evento_by_id(bst, id);
    return bst_rimuovi_nodo(bst, node);
}

void stampa_evento_bst_nodi(eventBstNode node, listaSala sala_lista)
{
    if (node == NULL)
    {
        return;
    }
    stampa_evento_bst_nodi(node->left, sala_lista);
    stampa_evento(node->value, sala_per_id_lista(sala_lista, get_evento_sala_id(node->value)));
    printf("\n\n");
    stampa_evento_bst_nodi(node->right, sala_lista);
}

void stampa_evento_bst(eventBst bst, listaSala sala_lista)
{
    stampa_evento_bst_nodi(bst->root, sala_lista);
}

int get_bst_size(eventBst bst)
{
    return bst->size;
}

event bst_get_evento_by_id(eventBst bst, int id)
{
    eventBstNode e = bst_cerca_evento_by_id(bst, id);
    if (e == NULL)
    {
        return NULL;
    }
    return e->value;
}

void free_event_bst_nodi(eventBstNode node)
{
    if (node == NULL)
    {
        return;
    }

    free_event_bst_nodi(node->left);
    free_event_bst_nodi(node->right);

    free_event(node->value);
    free(node);
}

void free_event_bst(eventBst bst)
{
    if (bst == NULL)
    {
        return;
    }
    free_event_bst_nodi(bst->root);
    free(bst);
}

void salva_evento_bst_nodi(eventBstNode node, FILE *file)
{
    if (node == NULL)
    {
        return;
    }

    // Save current node's event to the file
    salva_evento_su_file(node->value, file);

    // TODO
    // Add spacing between events
    // fprintf(file, "\n"); // Add a newline between events

    // Recursively save left and right subtrees
    salva_evento_bst_nodi(node->left, file);
    salva_evento_bst_nodi(node->right, file);
}

void salva_evento_bst_su_file(eventBst bst, FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return;
    }

    fprintf(file, "%zd\n", bst->size);
    // Traverse the BST and save each event to the file
    salva_evento_bst_nodi(bst->root, file);
}

// Function to read an event BST from a file
eventBst leggi_evento_bst_da_file(FILE *file)
{
    if (file == NULL)
    {
        perror("File pointer is NULL");
        return NULL;
    }

    size_t size = 0;
    if (fscanf(file, "%zu\n", &size) != 1)
    {
        perror("Error reading BST size");
        return NULL;
    }

    eventBst bst = nuovo_evento_bst(); // Create a new empty BST

    // Read event data from the file and insert into the BST
    for (size_t i = 0; i < size; i++)
    {
        event evento = leggi_evento_da_file(file);
        if (evento == NULL)
        {
            perror("Error reading event data");
            free_event_bst(bst);
            return NULL;
        }
        inserisci_evento_bst(bst, evento);
    }

    return bst;
}