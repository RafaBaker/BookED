#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "livro.h"
#include "utils.h"
#include "lista.h"

/**
 * @brief Estrutura que representa uma célula da lista.
 * 
 * Armazena um item genérico e ponteiros para funções de manipulação.
 */
struct Celula
{
    void *item;                         /**< Ponteiro para o item armazenado */
    func_ptr_desaloca desaloca;         /**< Função para desalocar o item */
    func_ptr_tipo getTipo;              /**< Função para obter o tipo do item */
    func_ptr_imprime imprime;           /**< Função para imprimir o item */
    func_ptr_compara compara;           /**< Função para comparar o item */
    Celula *prox;                       /**< Ponteiro para a próxima célula */
    // Celula* ant;
};

/**
 * @brief Estrutura que representa uma lista genérica.
 * 
 * Armazena ponteiros para as células inicial e final, além de um identificador.
 */
struct Lista
{
    int idLista;            /**< Identificador da lista */
    Celula *primeiro;       /**< Ponteiro para a primeira célula */
    Celula *ultimo;         /**< Ponteiro para a última célula */
};

Lista *inicializaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->idLista = -1;

    return lista;
}

void insereFimLista(Lista *lista, void *item, func_ptr_desaloca desaloca, func_ptr_tipo getTipo, func_ptr_imprime imprime, func_ptr_compara compara)
{
    Celula *nova = malloc(sizeof(Celula));

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
    lista->ultimo->getTipo = getTipo;
    lista->ultimo->imprime = imprime;
    lista->ultimo->compara = compara;
    lista->ultimo->prox = NULL;

    // printf("Item inserido com sucesso!\n");
}

void *buscaLista(Lista *lista, int id)
{
    Celula *aux = lista->primeiro;
    while (aux && !aux->compara(aux->item, id))
    {
        aux = aux->prox;
    }

    if (!aux)
    {
        // printf("Item não encontrado\n");
        return NULL;
    }
    return aux->item;
}

void removeLista(Lista *lista, int id)
{
    Celula *ant = lista->primeiro;
    Celula *aux = ant;
    while (aux && !aux->compara(aux->item, id))
    {
        ant = aux;
        aux = aux->prox;
    }

    if (!aux)
    {
        return; // não achou
    }

    if (aux == lista->primeiro && aux == lista->ultimo)
    {
        lista->primeiro = lista->ultimo = NULL;
    }
    else if (aux == lista->ultimo)
    {
        lista->ultimo = ant;
        lista->ultimo->prox = NULL;
    }
    else if (aux == lista->primeiro)
    {
        lista->primeiro = aux->prox;
    }
    else
    {
        ant->prox = aux->prox;
    }
    free(aux);
}

void *buscaListaComContexto(Lista *lista, func_ptr_compara_contexto compara, void *contexto)
{
    if (!lista || !compara)
        return NULL;

    Celula *aux = lista->primeiro;
    while (aux)
    {
        if (compara(aux->item, contexto))
        {
            return aux->item;
        }
        aux = aux->prox;
    }
    return NULL;
}

void removeListaComContexto(Lista* lista, func_ptr_compara_contexto compara, void* contexto)
{
    Celula* ant = lista->primeiro;
    Celula* aux = ant;
    while (aux && !compara(aux->item, contexto))
    {
        ant = aux;
        aux = aux->prox;
    }

    if (!aux)
        return;

    if (aux == lista->primeiro && aux == lista->ultimo)
    {
        lista->primeiro = lista->ultimo = NULL;
    }
    else if (aux == lista->ultimo)
    {
        lista->ultimo = ant;
        lista->ultimo->prox = NULL;
    }
    else if (aux == lista->primeiro)
    {
        lista->primeiro = aux->prox;
    }
    else
    {
        ant->prox = aux->prox;
    }
    free(aux);
}

void imprimeLista(Lista *lista, FILE* saida)
{
    if (!lista || !lista->primeiro) return;

    Celula *aux = lista->primeiro;
    while (aux)
    {
        aux->imprime(aux->item, saida);
        if ((aux->getTipo() == LIVRO || aux->getTipo() == RECOMENDACAO || aux->getTipo() == AFINIDADE || aux->getTipo() == STRING) && aux != lista->ultimo)
        {
            printf(", ");
            if (saida)
                fprintf(saida, ", ");
        }
        aux = aux->prox;
    }
}

void imprimeListaStruct(void* lista, FILE* saida)
{
    Lista* l = (Lista*)lista;
    printf("Lista de ID %d\n", l->idLista);
}

int listaVazia(Lista* lista)
{
    return lista->primeiro == NULL && lista->ultimo == NULL;
}

void desalocaLista(void *lista)
{
    if (lista)
    {
        Lista* l = (Lista*)lista;
        Celula *aux;
        Celula *prox;
        aux = l->primeiro;
        while (aux)
        {
            prox = aux->prox;
            if (aux->desaloca) aux->desaloca(aux->item);
            free(aux);
            aux = prox;
        }
        free (l);
    }
    lista = NULL;
}

void desalocaListaStruct(void* lista)
{
    Lista* l = (Lista*)lista;
    if (l)
    {
        Celula* aux = l->primeiro;
        Celula* prox;
        while (aux)
        {
            prox = aux->prox;
            free(aux);
            aux = prox;
        }

        free(lista);
        lista = NULL;
    }
}

int getTipoLista()
{
    return LISTA;
}

int quantidadeLista(Lista* lista)
{
    Celula* aux = lista->primeiro;
    int i = 0;
    while (aux)
    {
        i++;
        aux = aux->prox;
    }
    return i;
}

int setIdLista(Lista* lista, int id)
{
    lista->idLista = id;
}

int getIdLista(Lista* lista)
{
    return lista->idLista;
}

Lista* temItemComumLista(Lista* l1, Lista* l2)
{
    Celula* aux1 = l1->primeiro;
    Celula* aux2 = l2->primeiro;
    int qtdL1, qtdL2;

    if (!aux1 && !aux2)
    {
        return NULL;
    }

    if (!aux1 || !aux2)
    {
        return NULL;
    }

    Lista* nova = inicializaLista();

    while (aux1)
    {
        aux2 = l2->primeiro;
        while (aux2)
        {
            if (aux1->getTipo() == STRING)
            {
                if (!strcmp(aux1->item, aux2->item))
                {
                    insereFimLista(nova, aux2->item, desalocaString, getTipoString, imprimeString, NULL);
                }
            }
            else
            {
                if (aux1->item == aux2->item)
                {
                    insereFimLista(nova, aux2->item, NULL, getTipoLivro, imprimeLivro, comparaIDLivro);
                }
            }
            aux2 = aux2->prox;
        }
        aux1 = aux1->prox;
    }
    return nova;
}

int comparaLista(void* l1, int id)
{
    Lista* lista = (Lista*)l1;
    return lista->idLista == id;
}

Celula* getCelula(Lista* lista)
{
    return lista->primeiro;
}

void* getItemCelula(Celula* celula)
{
    return celula->item;
}

Celula* proximaCelula(Celula* celula)
{
    return celula->prox;
}
