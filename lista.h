#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

typedef void (*func_ptr_desaloca)(void* dado);

typedef void (*func_ptr_tipo)(void* dado);

typedef void (*func_ptr_imprime)(void* dado);

Lista* inicializaLista();

void insereFimLista(Lista* lista, void* item, /* func_ptr_tipo getTipo,*/ func_ptr_desaloca desaloca, func_ptr_imprime imprime);

void imprimeLista(Lista* lista);

int desalocaLista(Lista* lista);


#endif