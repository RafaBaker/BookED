#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

typedef void (*func_ptr_desaloca)(void* dado);

typedef void (*func_ptr_tipo)(void* dado);

typedef void (*func_ptr_imprime)(void* dado);

typedef int (*func_ptr_compara)(void* dado, int id);

Lista* inicializaLista();

void insereFimLista(Lista* lista, void* item, func_ptr_desaloca desaloca, func_ptr_imprime imprime, func_ptr_compara compara);

void* buscaLista(Lista* lista, int id);

void removeLista(Lista* lista, int id);

void imprimeLista(Lista* lista);

int desalocaLista(Lista* lista);


#endif