#ifndef BOOKED_H
#define BOOKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

/**
 * @brief Estrutura opaca que representa o sistema BookED.
 */
typedef struct BookED BookED;

/**
 * @brief Inicializa o sistema BookED.
 * @return Ponteiro para a estrutura BookED criada.
 */
BookED* inicializaBookED();

/**
 * @brief Lê os livros do arquivo e os adiciona ao sistema.
 * @param b Ponteiro para a estrutura BookED.
 * @param pLivros Ponteiro para o arquivo de livros.
 */
void leLivrosArquivo(BookED* b, FILE* pLivros);

/**
 * @brief Lê os leitores do arquivo e os adiciona ao sistema.
 * @param b Ponteiro para a estrutura BookED.
 * @param pLeitores Ponteiro para o arquivo de leitores.
 */
void leLeitoresArquivo(BookED* b, FILE* pLeitores);

/**
 * @brief Imprime a lista de leitores.
 * @param b Ponteiro para a estrutura BookED.
 */
void imprimeLeitores(BookED* b);

/**
 * @brief Imprime a lista de livros.
 * @param b Ponteiro para a estrutura BookED.
 */
void imprimeLivros(BookED* b);

/**
 * @brief Imprime o sistema BookED em um arquivo de saída.
 * @param b Ponteiro para a estrutura BookED.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeBookEd(BookED* b, FILE* saida);

/**
 * @brief Adiciona um livro lido por um leitor.
 * @param b Ponteiro para a estrutura BookED.
 * @param idLeitor ID do leitor.
 * @param idLivro ID do livro.
 * @param saida Ponteiro para o arquivo de saída.
 */
void adicionaLivroLido(BookED* b, int idLeitor, int idLivro, FILE* saida);

/**
 * @brief Adiciona um livro desejado por um leitor.
 * @param b Ponteiro para a estrutura BookED.
 * @param idLeitor ID do leitor.
 * @param idLivro ID do livro.
 * @param saida Ponteiro para o arquivo de saída.
 */
void adicionarLivroDesejado(BookED* b, int idLeitor, int idLivro, FILE* saida);

/**
 * @brief Recomenda um livro de um leitor para outro.
 * @param b Ponteiro para a estrutura BookED.
 * @param idRecomendador ID do leitor que recomenda o livro.
 * @param idLivro ID do livro recomendado.
 * @param idDestinatario ID do leitor que receberá a recomendação.
 * @param saida Ponteiro para o arquivo de saída.
 */
void recomendarLivro(BookED* b, int idRecomendador, int idLivro, int idDestinatario, FILE* saida);

/**
 * @brief Aceita uma recomendação de livro.
 * @param b Ponteiro para a estrutura BookED.
 * @param idDestinatario ID do leitor que recebeu a recomendação.
 * @param idLivro ID do livro recomendado.
 * @param idRecomendador ID do leitor que fez a recomendação.
 * @param saida Ponteiro para o arquivo de saída.
 */
void aceitarRecomendacao(BookED* b, int idDestinatario, int idLivro, int idRecomendador, FILE* saida);

/**
 * @brief Remove uma recomendação de livro.
 * @param b Ponteiro para a estrutura BookED.
 * @param idDestinatario ID do leitor que recebeu a recomendação.
 * @param idLivro ID do livro recomendado.
 * @param idRecomendador ID do leitor que fez a recomendação.
 * @param saida Ponteiro para o arquivo de saída.
 */
void removerRecomendacao(BookED* b, int idDestinatario, int idLivro, int idRecomendador, FILE* saida);

/**
 * @brief Desaloca a memória utilizada pelo sistema BookED.
 * @param b Ponteiro para a estrutura BookED.
 * @return 0 se a desalocação foi bem-sucedida, outro valor caso contrário.
 */
int desalocaBookEd(BookED* b);

/**
 * @brief Inicializa as afinidades entre os leitores.
 * @param b Ponteiro para a estrutura BookED.
 */
void inicializaAfinidades(BookED* b);

/**
 * @brief Verifica a afinidade entre dois leitores.
 * @param b Ponteiro para a estrutura BookED.
 * @param idLeitorOrigem ID do leitor de origem.
 * @param idLeitorDestino ID do leitor de destino.
 * @param saida Ponteiro para o arquivo de saída.
 */
void verificarAfinidade(BookED* b, int idLeitorOrigem, int idLeitorDestino, FILE* saida);

/**
 * @brief Função auxiliar para buscar afinidade entre leitores.
 * @param b Ponteiro para a estrutura BookED.
 * @param idLeitorOrigem ID do leitor de origem.
 * @param idLeitorDestino ID do leitor de destino.
 * @param visitado Array de controle de leitores visitados.
 * @return 1 se a afinidade foi encontrada, 0 caso contrário.
 */
static int buscaAfinidade(BookED* b, int idLeitorOrigem, int idLeitorDestino, int* visitado);

/**
 * @brief Executa os comandos no sistema BookED.
 * @param b Ponteiro para a estrutura BookED.
 * @param pComandos Ponteiro para o arquivo de comandos.
 * @param pSaida Ponteiro para o arquivo de saída.
 */
void executaBookED(BookED* b, FILE* pComandos, FILE* pSaida);


#endif