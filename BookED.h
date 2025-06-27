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

void imprimeBookEd(BookED* b);

void adicionaLivroLido(BookED* b, int idLeitor, int idLivro);

void adicionarLivroDesejado(BookED* b, int idLeitor, int idLivro);

void recomendarLivro(BookED* b, int idRecomendador, int idLivro, int idRecomendado);

void aceitarRecomendacao(BookED* b, int idRecomendado, int idLivro, int idRecomendador);

void removerRecomendacao(BookED* b, int idRecomendado, int idLivro, int idRecomendador);

int desalocaBookEd(BookED* b);

void inicializaAfinidades(BookED* b);


#endif