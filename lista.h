#ifndef LISTA_H
#define LISTA_H

#include "utils.h"

typedef struct Lista Lista;

typedef void (*func_ptr_desaloca)(void* dado);

typedef int (*func_ptr_tipo)();

typedef void (*func_ptr_imprime)(void* dado);

typedef int (*func_ptr_compara)(void* dado, int id);

typedef int (*func_ptr_compara_contexto)(void* item, void* contexto);

typedef struct Celula Celula;

Lista* inicializaLista();

void insereFimLista(Lista* lista, void* item, func_ptr_desaloca desaloca, func_ptr_tipo getTipo, func_ptr_imprime imprime, func_ptr_compara compara);

void* buscaLista(Lista* lista, int id);

void removeLista(Lista* lista, int id);

void* buscaListaComContexto(Lista* lista, func_ptr_compara_contexto compara, void* contexto);

void removeListaComContexto(Lista* lista, func_ptr_compara_contexto compara, void* contexto);

void imprimeLista(Lista* lista);

void imprimeListaStruct(void* lista);

// void imprimeListaLeitores(Lista *lista);

int listaVazia(Lista* lista);

int desalocaLista(Lista* lista);

void desalocaListaStruct(void* lista);

int getTipoLista();

int quantidadeLista(Lista* lista);

int setaIdLista(Lista* lista, int id);

int temItemComumLista(Lista* l1, Lista* l2);

Celula* getCelula(Lista* lista);

#endif