#ifndef BOOKED_H
#define BOOKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

typedef struct BookED BookED;

BookED* inicializaBookED();

void leLivrosArquivo(BookED* b, FILE* pLivros);

void leLeitoresArquivo(BookED* b, FILE* pLeitores);

void imprimeLeitores(BookED* b);

void imprimeLivros(BookED* b);

void imprimeBookEd(BookED* b, FILE* saida);

void adicionaLivroLido(BookED* b, int idLeitor, int idLivro, FILE* saida);

void adicionarLivroDesejado(BookED* b, int idLeitor, int idLivro, FILE* saida);

void recomendarLivro(BookED* b, int idRecomendador, int idLivro, int idDestinatario, FILE* saida);

void aceitarRecomendacao(BookED* b, int idDestinatario, int idLivro, int idRecomendador, FILE* saida);

void removerRecomendacao(BookED* b, int idDestinatario, int idLivro, int idRecomendador, FILE* saida);

int desalocaBookEd(BookED* b);

void inicializaAfinidades(BookED* b);

void verificarAfinidade(BookED* b, int idLeitorOrigem, int idLeitorDestino, FILE* saida);

static int buscaAfinidade(BookED* b, int idLeitorOrigem, int idLeitorDestino, int* visitado);

void executaBookED(BookED* b, FILE* pComandos, FILE* pSaida);


#endif