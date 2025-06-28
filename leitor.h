#ifndef LEITOR_H
#define LEITOR_H

#include "leitor.h"
#include "livro.h"
#include "lista.h"

typedef struct Leitor Leitor;

Leitor* criaLeitor(int id, char* nome);

void desalocaLeitor(void* leitor);

int getTipoLeitor();

char* getNomeLeitor(Leitor* leitor);

void imprimeNomeLeitor(void *leitor, FILE* saida);

void imprimeIdLeitor(void *leitor);

void imprimeLeitor(void* leitor, FILE* saida);

int comparaIDLeitor(void* leitor, int id);

int adicionaLivroLidoLeitor(Leitor* leitor, Livro* livro);

void imprimeLivrosLidosLeitor(Leitor* leitor, FILE* saida);

int adicionaLivroDesejadoLeitor(Leitor* leitor, Livro* livro);

void imprimeLivrosDesejadosLeitor(Leitor* leitor, FILE* saida);

int adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador);

void imprimeRecomendacoesLeitor(Leitor* leitor, FILE* saida);

int aceitaRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador);

int removerRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador);

void inserePreferenciaLeitor(Leitor* leitor, char* afinidade);

void imprimePreferenciasLeitor(Leitor* leitor, FILE* saida);

int temGenerosComuns(Leitor* l1, Leitor* l2);

Lista* temLivrosComuns(Leitor* l1, Leitor* l2);

void adicionaAfinidadeLeitor(Leitor* l1, Leitor* l2);

void imprimeAfinidadesLeitor(Leitor* leitor, FILE* saida);

#endif