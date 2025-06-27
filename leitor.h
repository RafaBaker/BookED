#ifndef LEITOR_H
#define LEITOR_H

#include "leitor.h"
#include "livro.h"
#include "lista.h"

typedef struct Leitor Leitor;

Leitor* criaLeitor(int id, char* nome);

void desalocaLeitor(void* leitor);

int getTipoLeitor();

void imprimeNomeLeitor(void *leitor);

void imprimeIdLeitor(void *leitor);

void imprimeLeitor(void* leitor);

int comparaIDLeitor(void* leitor, int id);

void adicionaLivroLidoLeitor(Leitor* leitor, Livro* livro);

void imprimeLivrosLidosLeitor(Leitor* leitor);

void adicionaLivroDesejadoLeitor(Leitor* leitor, Livro* livro);

void imprimeLivrosDesejadosLeitor(Leitor* leitor);

void adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador);

void imprimeRecomendacoesLeitor(Leitor* leitor);

void aceitaRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador);

void removerRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador);

void inserePreferenciaLeitor(Leitor* leitor, char* afinidade);

void imprimePreferenciasLeitor(Leitor* leitor);

int temGenerosComuns(Leitor* l1, Leitor* l2);

int comparaLista(void* l1, int id);

#endif