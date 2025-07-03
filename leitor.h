#ifndef LEITOR_H
#define LEITOR_H

#include "leitor.h"
#include "livro.h"
#include "lista.h"

/**
 * @brief Estrutura opaca que representa um leitor.
 */
typedef struct Leitor Leitor;

/**
 * @brief Cria uma nova estrutura Leitor.
 * @param id Identificador do leitor.
 * @param nome Nome do leitor.
 * @return Ponteiro para a estrutura Leitor criada.
 */
Leitor* criaLeitor(int id, char* nome);

/**
 * @brief Libera a memória alocada para a estrutura Leitor.
 * @param leitor Ponteiro para a estrutura Leitor a ser desalocada.
 */
void desalocaLeitor(void* leitor);

/**
 * @brief Retorna o tipo do leitor.
 * @return Constante que representa o tipo LEITOR.
 */
int getTipoLeitor();

/**
 * @brief Retorna o nome do leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @return Ponteiro para a string com o nome do leitor.
 */
char* getNomeLeitor(Leitor* leitor);

/**
 * @brief Imprime o nome do leitor na saída padrão e em um arquivo.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeNomeLeitor(void *leitor, FILE* saida);

/**
 * @brief Imprime o ID do leitor na saída padrão.
 * @param leitor Ponteiro para a estrutura Leitor.
 */
void imprimeIdLeitor(void *leitor);

/**
 * @brief Imprime todas as informações do leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeLeitor(void* leitor, FILE* saida);

/**
 * @brief Compara o ID de um leitor com um valor fornecido.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param id ID a ser comparado.
 * @return 1 se os IDs forem iguais, 0 caso contrário.
 */
int comparaIDLeitor(void* leitor, int id);

/**
 * @brief Adiciona um livro à lista de livros lidos pelo leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param livro Ponteiro para a estrutura Livro a ser adicionada.
 * @return 1 se o livro foi adicionado com sucesso, 0 caso contrário.
 */
int adicionaLivroLidoLeitor(Leitor* leitor, Livro* livro);

/**
 * @brief Imprime a lista de livros lidos pelo leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeLivrosLidosLeitor(Leitor* leitor, FILE* saida);

/**
 * @brief Adiciona um livro à lista de livros desejados pelo leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param livro Ponteiro para a estrutura Livro a ser adicionada.
 * @return 1 se o livro foi adicionado com sucesso, 0 caso contrário.
 */
int adicionaLivroDesejadoLeitor(Leitor* leitor, Livro* livro);

/**
 * @brief Imprime a lista de livros desejados pelo leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeLivrosDesejadosLeitor(Leitor* leitor, FILE* saida);

/**
 * @brief Adiciona uma recomendação de livro de um leitor para outro.
 * @param destinatario Ponteiro para o leitor que receberá a recomendação.
 * @param livro Ponteiro para o livro recomendado.
 * @param recomendador Ponteiro para o leitor que está fazendo a recomendação.
 * @return 1 se a recomendação foi adicionada com sucesso, 0 caso contrário.
 */
int adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador);

/**
 * @brief Imprime as recomendações de livros para um leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeRecomendacoesLeitor(Leitor* leitor, FILE* saida);

/**
 * @brief Aceita uma recomendação de livro por parte do leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param idLivro ID do livro a ser aceito.
 * @param idRecomendador ID do leitor que fez a recomendação.
 * @return 1 se a recomendação foi aceita com sucesso, 0 caso contrário.
 */
int aceitaRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador);

/**
 * @brief Remove uma recomendação de livro da lista de recomendações do leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param idLivro ID do livro cuja recomendação será removida.
 * @param idRecomendador ID do leitor que fez a recomendação.
 * @return 1 se a recomendação foi removida com sucesso, 0 caso contrário.
 */
int removerRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador);

/**
 * @brief Insere uma preferência de gênero literário para o leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param afinidade String representando a afinidade a ser adicionada.
 */
void inserePreferenciaLeitor(Leitor* leitor, char* afinidade);

/**
 * @brief Imprime as preferências de gênero literário do leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimePreferenciasLeitor(Leitor* leitor, FILE* saida);

/**
 * @brief Verifica se dois leitores têm gêneros literários em comum.
 * @param l1 Ponteiro para o primeiro leitor.
 * @param l2 Ponteiro para o segundo leitor.
 * @return 1 se os leitores têm gêneros em comum, 0 caso contrário.
 */
int temGenerosComuns(Leitor* l1, Leitor* l2);

/**
 * @brief Verifica se dois leitores têm livros em comum.
 * @param l1 Ponteiro para o primeiro leitor.
 * @param l2 Ponteiro para o segundo leitor.
 * @return Lista* com os livros em comum, ou NULL se não houverem.
 */
Lista* temLivrosComuns(Leitor* l1, Leitor* l2);

/**
 * @brief Adiciona afinidade entre dois leitores com base em seus gostos literários.
 * @param l1 Ponteiro para o primeiro leitor.
 * @param l2 Ponteiro para o segundo leitor.
 */
void adicionaAfinidadeLeitor(Leitor* l1, Leitor* l2);

/**
 * @brief Imprime as afinidades literárias de um leitor.
 * @param leitor Ponteiro para a estrutura Leitor.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeAfinidadesLeitor(Leitor* leitor, FILE* saida);

#endif