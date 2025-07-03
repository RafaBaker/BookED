#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "leitor.h"
#include "livro.h"
#include "lista.h"

/**
 * @brief Estrutura que representa uma recomendação de livro.
 * 
 * Contém ponteiros para o livro recomendado e para o leitor recomendador.
 */
typedef struct
{
    Livro *livro;           /**< Livro recomendado */
    Leitor *recomendador;   /**< Leitor que fez a recomendação */
} Recomendacao;

/**
 * @brief Estrutura que representa o contexto de uma recomendação.
 * 
 * Usada para identificar recomendações específicas por id do livro e do recomendador.
 */
typedef struct
{
    int idLivro;            /**< ID do livro recomendado */
    int idRecomendador;     /**< ID do leitor recomendador */
} ContextoRecomendacao;

/**
 * @brief Estrutura que representa um leitor.
 * 
 * Contém informações como id, nome, listas de livros lidos, desejados, recomendações, preferências e afinidades.
 */
struct Leitor
{
    int id;                 /**< Identificador do leitor */
    char *nome;             /**< Nome do leitor */
    Lista *lidos;           /**< Lista de livros lidos */
    Lista *desejados;       /**< Lista de livros desejados */
    Lista *recomendacoes;   /**< Lista de recomendações recebidas */
    Lista *preferencias;    /**< Lista de gêneros preferidos (strings) */
    Lista *afinidades;      /**< Lista de leitores com afinidade */
};

static int comparaRecomendacao(void *rec, int idLivro)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    return (getIdLivro(recomendacao->livro) == idLivro);
}

static int comparaRecomendacaoComContexto(void* item, void* contexto) {
    Recomendacao* rec = (Recomendacao*)item;
    ContextoRecomendacao* ctx = (ContextoRecomendacao*)contexto;
    return (getIdLivro(rec->livro) == ctx->idLivro && comparaIDLeitor(rec->recomendador, ctx->idRecomendador));
}

static void imprimeRecomendacaoLivro(void *rec, FILE* saida)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    imprimeLivro(recomendacao->livro, saida);
}

static void imprimeRecomendacao(void *rec, FILE* saida)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    printf("Livro destinatario: ");
    fprintf(saida, "Livro destinatario: ");
    imprimeLivro(recomendacao->livro, saida);
    printf("Destinatario por ");
    fprintf(saida, "Destinatario por ");
    imprimeLeitor(recomendacao->recomendador, saida);
}

static void desalocaRecomendacao(void *rec)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    if (recomendacao) free(recomendacao);
}

static int getTipoRec()
{
    return RECOMENDACAO;
}

Leitor *criaLeitor(int id, char *nome)
{
    Leitor *leitor = malloc(sizeof(Leitor));
    leitor->id = id;
    leitor->nome = strdup(nome);
    leitor->lidos = inicializaLista();
    leitor->desejados = inicializaLista();
    leitor->recomendacoes = inicializaLista();
    leitor->preferencias = inicializaLista();
    leitor->afinidades = inicializaLista();
    return leitor;
}

void desalocaLeitor(void *leitor)
{
    if (leitor)
    {
        Leitor *l = (Leitor *)leitor;
        free(l->nome);
        desalocaListaStruct(l->lidos);
        desalocaListaStruct(l->desejados);
        desalocaLista(l->recomendacoes);
        desalocaLista(l->preferencias);
        desalocaLista(l->afinidades);
        free(leitor);
    }
    leitor = NULL;
}

int getTipoLeitor()
{
    return LEITOR;
}

char* getNomeLeitor(Leitor* leitor)
{
    return leitor->nome;
}

void imprimeNomeLeitor(void *leitor, FILE* saida)
{
    Leitor *l = (Leitor *)leitor;
    printf("%s", l->nome);
    fprintf(saida, "%s", l->nome);
}

void imprimeIdLeitor(void *leitor)
{
    Leitor *l = (Leitor *)leitor;
    printf("%d", l->id);
}

void imprimeLeitor(void *leitor, FILE* saida)
{
    Leitor *l = (Leitor *)leitor;
    printf("\nLeitor: ");
    fprintf(saida, "\nLeitor: ");
    imprimeNomeLeitor(leitor, saida);
    printf("\n");
    fprintf(saida, "\n");
    imprimeLivrosLidosLeitor(l, saida);
    imprimeLivrosDesejadosLeitor(l, saida);
    imprimeRecomendacoesLeitor(l, saida);
    imprimeAfinidadesLeitor(l, saida);
}

int comparaIDLeitor(void *leitor, int id)
{
    Leitor *l = (Leitor *)leitor;
    return l->id == id;
}

int adicionaLivroLidoLeitor(Leitor *leitor, Livro *livro)
{
    if (buscaLista(leitor->lidos, getIdLivro(livro)) == NULL)
    {
        insereFimLista(leitor->lidos, livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
        return 1;
    }
    return 0;
}

void imprimeLivrosLidosLeitor(Leitor *leitor, FILE* saida)
{
    printf("Lidos: ");
    fprintf(saida, "Lidos: ");
    imprimeLista(leitor->lidos, saida);
    printf("\n");
    fprintf(saida, "\n");
}

int adicionaLivroDesejadoLeitor(Leitor *leitor, Livro *livro)
{
    if (buscaLista(leitor->desejados, getIdLivro(livro)) == NULL)
    {
        insereFimLista(leitor->desejados, livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
        return 1;
    }
    return 0;
}

void imprimeLivrosDesejadosLeitor(Leitor *leitor, FILE* saida)
{
    printf("Desejados: ");
    fprintf(saida, "Desejados: ");
    imprimeLista(leitor->desejados, saida);
    printf("\n");
    fprintf(saida, "\n");
}

int adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador)
{
    if (buscaLista(destinatario->lidos, getIdLivro(livro)))
        return 0;
    if (buscaLista(destinatario->desejados, getIdLivro(livro)))
        return -1;
    Recomendacao *rec = malloc(sizeof(Recomendacao));
    rec->livro = livro;
    rec->recomendador = recomendador;
    insereFimLista(destinatario->recomendacoes, rec, desalocaRecomendacao, getTipoRec, imprimeRecomendacaoLivro, comparaRecomendacao);
    return 1;
}

void imprimeRecomendacoesLeitor(Leitor* leitor, FILE* saida)
{
    printf("Recomendações: ");
    fprintf(saida, "Recomendações: ");
    imprimeLista(leitor->recomendacoes, saida);
    printf("\n");
    fprintf(saida, "\n");
}

int aceitaRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador)
{
    ContextoRecomendacao ctx;
    ctx.idLivro = idLivro;
    ctx.idRecomendador = idRecomendador;
    Recomendacao *rec = buscaListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
    if (rec)
    {
        adicionaLivroDesejadoLeitor(leitor, rec->livro);
        removeListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
        return 1;
    }
    return 0;
}

int removerRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador)
{
    ContextoRecomendacao ctx;
    ctx.idLivro = idLivro;
    ctx.idRecomendador = idRecomendador;
    Recomendacao *rec = buscaListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
    if (rec)
    {
        removeListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
        return 1;
    }
    return 0;
}

void inserePreferenciaLeitor(Leitor* leitor, char* afinidade)
{
    insereFimLista(leitor->preferencias, afinidade, desalocaString, getTipoString, imprimeString, NULL);
}

void imprimePreferenciasLeitor(Leitor* leitor, FILE* saida)
{
    printf("Preferências: ");
    fprintf(saida, "Preferências: ");
    imprimeLista(leitor->preferencias, saida);
    printf("\n");
    fprintf(saida, "\n");
}

int temGenerosComuns(Leitor* l1, Leitor* l2)
{
    Celula* aux1 = getCelula(l1->preferencias);
    Celula* aux2 = getCelula(l2->preferencias);
    while (aux1)
    {
        aux2 = getCelula(l2->preferencias);
        while (aux2)
        {
            if (!strcmp(aux1->item, aux2->item))
                return 1;
            aux2 = proximaCelula(aux2);
        }
        aux1 = proximaCelula(aux1);
    }
    return 0;
}

Lista* temLivrosComuns(Leitor* l1, Leitor* l2)
{
    return temItemComumLista(l1->lidos, l2->lidos);
}

void adicionaAfinidadeLeitor(Leitor* l1, Leitor* l2)
{
    insereFimLista(l1->afinidades, l2, NULL, getTipoLeitor, imprimeNomeLeitor, comparaIDLeitor);
}

void imprimeAfinidadesLeitor(Leitor* leitor, FILE* saida)
{
    printf("Afinidades: ");
    fprintf(saida, "Afinidades: ");
    imprimeLista(leitor->afinidades, saida);
    printf("\n");
    fprintf(saida, "\n");
}