#ifndef LISTA_H
#define LISTA_H

#include "utils.h"

/**
 * @brief Estrutura opaca que representa uma lista genérica.
 */
typedef struct Lista Lista;

/**
 * @brief Estrutura opaca que representa uma célula da lista.
 */
typedef struct Celula Celula;

/**
 * @brief Ponteiro para função de desalocação de item.
 * @param dado Ponteiro para o item a ser desalocado.
 */
typedef void (*func_ptr_desaloca)(void* dado);

/**
 * @brief Ponteiro para função que retorna o tipo do item.
 * @return Tipo do item.
 */
typedef int (*func_ptr_tipo)();

/**
 * @brief Ponteiro para função de impressão de item.
 * @param dado Ponteiro para o item a ser impresso.
 * @param saida Ponteiro para o arquivo de saída.
 */
typedef void (*func_ptr_imprime)(void* dado, FILE* saida);

/**
 * @brief Ponteiro para função de comparação de item por id.
 * @param dado Ponteiro para o item.
 * @param id Identificador a ser comparado.
 * @return 1 se iguais, 0 caso contrário.
 */
typedef int (*func_ptr_compara)(void* dado, int id);

/**
 * @brief Ponteiro para função de comparação de item com contexto.
 * @param item Ponteiro para o item.
 * @param contexto Ponteiro para o contexto.
 * @return 1 se iguais, 0 caso contrário.
 */
typedef int (*func_ptr_compara_contexto)(void* item, void* contexto);

/**
 * @brief Inicializa uma nova lista.
 * @return Ponteiro para a lista criada.
 */
Lista* inicializaLista();

/**
 * @brief Insere um item no final da lista.
 * @param lista Ponteiro para a lista.
 * @param item Ponteiro para o item a ser inserido.
 * @param desaloca Função para desalocar o item.
 * @param getTipo Função para obter o tipo do item.
 * @param imprime Função para imprimir o item.
 * @param compara Função para comparar o item.
 */
void insereFimLista(Lista* lista, void* item, func_ptr_desaloca desaloca, func_ptr_tipo getTipo, func_ptr_imprime imprime, func_ptr_compara compara);

/**
 * @brief Busca um item na lista pelo seu identificador.
 * @param lista Ponteiro para a lista.
 * @param id Identificador do item a ser buscado.
 * @return Ponteiro para o item encontrado ou NULL se não encontrado.
 */
void* buscaLista(Lista* lista, int id);

/**
 * @brief Remove um item da lista pelo seu identificador.
 * @param lista Ponteiro para a lista.
 * @param id Identificador do item a ser removido.
 */
void removeLista(Lista* lista, int id);

/**
 * @brief Busca um item na lista utilizando uma função de comparação com contexto.
 * @param lista Ponteiro para a lista.
 * @param compara Função de comparação.
 * @param contexto Ponteiro para o contexto a ser utilizado na comparação.
 * @return Ponteiro para o item encontrado ou NULL se não encontrado.
 */
void* buscaListaComContexto(Lista* lista, func_ptr_compara_contexto compara, void* contexto);

/**
 * @brief Remove um item da lista utilizando uma função de comparação com contexto.
 * @param lista Ponteiro para a lista.
 * @param compara Função de comparação.
 * @param contexto Ponteiro para o contexto a ser utilizado na comparação.
 */
void removeListaComContexto(Lista* lista, func_ptr_compara_contexto compara, void* contexto);

/**
 * @brief Imprime os itens da lista em um arquivo.
 * @param lista Ponteiro para a lista.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeLista(Lista* lista, FILE* saida);

/**
 * @brief Imprime a lista utilizando a função de impressão padrão.
 * @param lista Ponteiro para a lista.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeListaStruct(void* lista, FILE* saida);

// void imprimeListaLeitores(Lista *lista);

/**
 * @brief Verifica se a lista está vazia.
 * @param lista Ponteiro para a lista.
 * @return 1 se a lista estiver vazia, 0 caso contrário.
 */
int listaVazia(Lista* lista);

/**
 * @brief Desaloca toda a memória utilizada pela lista.
 * @param lista Ponteiro para a lista.
 */
void desalocaLista(void* lista);

/**
 * @brief Desaloca toda a memória utilizada pela lista, incluindo seus itens.
 * @param lista Ponteiro para a lista.
 */
void desalocaListaStruct(void* lista);

/**
 * @brief Obtém o tipo da lista.
 * @return Tipo da lista.
 */
int getTipoLista();

/**
 * @brief Obtém a quantidade de itens na lista.
 * @param lista Ponteiro para a lista.
 * @return Quantidade de itens na lista.
 */
int quantidadeLista(Lista* lista);

/**
 * @brief Define o identificador para os itens da lista.
 * @param lista Ponteiro para a lista.
 * @param id Identificador a ser definido.
 * @return 1 se o identificador foi definido com sucesso, 0 caso contrário.
 */
int setIdLista(Lista* lista, int id);

/**
 * @brief Obtém o identificador de um item da lista.
 * @param lista Ponteiro para a lista.
 * @return Identificador do item.
 */
int getIdLista(Lista* lista);

/**
 * @brief Verifica se há itens comuns entre duas listas.
 * @param l1 Ponteiro para a primeira lista.
 * @param l2 Ponteiro para a segunda lista.
 * @return Ponteiro para a lista com os itens comuns ou NULL se não houver itens comuns.
 */
Lista* temItemComumLista(Lista* l1, Lista* l2);

/**
 * @brief Obtém a célula da lista.
 * @param lista Ponteiro para a lista.
 * @return Ponteiro para a célula da lista.
 */
Celula* getCelula(Lista* lista);

/**
 * @brief Obtém o item contido em uma célula.
 * @param celula Ponteiro para a célula.
 * @return Ponteiro para o item contido na célula.
 */
void* getItemCelula(Celula* celula);

/**
 * @brief Obtém a próxima célula na lista.
 * @param celula Ponteiro para a célula atual.
 * @return Ponteiro para a próxima célula.
 */
Celula* proximaCelula(Celula* celula);

/**
 * @brief Compara um item da lista com um identificador.
 * @param l1 Ponteiro para o item da lista.
 * @param id Identificador a ser comparado.
 * @return 1 se os identificadores forem iguais, 0 caso contrário.
 */
int comparaLista(void* l1, int id);

#endif