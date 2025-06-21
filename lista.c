#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lista.h"

typedef struct Celula Celula;

struct Celula
{
    void* item;
    func_ptr_desaloca desaloca;
    // func_ptr_tipo getTipo;
    func_ptr_imprime imprime;
    Celula* prox;
    Celula* ant;
};

struct Lista
{
    Celula *primeiro, *ultimo;
};

Lista* inicializaLista()
{
    Lista* lista = (Lista*)malloc(sizeof(Lista));

    lista->primeiro = NULL;
    lista->ultimo = NULL;

    return lista;
}

void insereFimLista(Lista* lista, void* item, func_ptr_desaloca desaloca, func_ptr_imprime imprime)
{
    Celula* nova = malloc(sizeof(Celula));

    if (!lista->ultimo)
    {
        lista->primeiro = lista->ultimo = nova;
    }
    else 
    {
        lista->ultimo = lista->ultimo->prox = nova;
    }
    lista->ultimo->item = item;
    lista->ultimo->desaloca = desaloca;
    lista->ultimo->imprime = imprime;
    lista->ultimo->prox = NULL;

    printf("Item inserido com sucesso!\n");
}

void imprimeLista(Lista* lista)
{
    Celula* aux = lista->primeiro;
    while (aux)
    {
        aux->imprime(aux->item);

        aux = aux->prox;
    }
}

int desalocaLista(Lista* lista)
{
    if (lista)
    {
        Celula* aux;
        Celula* prox;
        aux = lista->primeiro;
        while (aux)
        {
            prox = aux->prox;
            free(aux);
            aux = prox;
        }
        free(lista);
    }
    lista = NULL;
    return 1;
}