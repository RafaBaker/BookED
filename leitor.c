#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "leitor.h"
#include "livro.h"
#include "lista.h"

// Recomendacoes
typedef struct
{
    Livro *livro;
    Leitor *recomendador;
} Recomendacao;

typedef struct
{
    int idLivro;
    int idRecomendador;
} ContextoRecomendacao;

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

// Função para imprimir uma recomendação
static void imprimeRecomendacaoLivro(void *rec, FILE* saida)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    imprimeLivro(recomendacao->livro, saida); // Supondo que você tenha esta função
}

// Função para imprimir uma recomendação
static void imprimeRecomendacao(void *rec, FILE* saida)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    printf("Livro destinatario: ");
    fprintf(saida, "Livro destinatario: ");
    imprimeLivro(recomendacao->livro, saida); // Supondo que você tenha esta função
    printf("Destinatario por ");
    fprintf(saida, "Destinatario por ");
    imprimeLeitor(recomendacao->recomendador, saida);
}

// Função para desalocar uma recomendação
static void desalocaRecomendacao(void *rec)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    if (recomendacao) free(recomendacao);
}

static int getTipoRec()
{
    return RECOMENDACAO;
}

struct Leitor
{
    int id;
    char *nome;
    Lista *lidos;
    Lista *desejados;
    Lista *recomendacoes;
    Lista *preferencias; // Lista de strings
    Lista *afinidades; // lista de pessoas
    // afinidades (?)
};

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
    
    //Livros lidos
    imprimeLivrosLidosLeitor(l, saida);

    //Livros desejados
    imprimeLivrosDesejadosLeitor(l, saida);

    //Livros recomendados
    imprimeRecomendacoesLeitor(l, saida);

    // //Preferencias
    // imprimePreferenciasLeitor(l, saida);

    // Afinidades
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
    // Vendo se o livro não está na lista de lidos
    if (!buscaLista(leitor->lidos, getIdLivro(livro)))
    {
        // Vendo se o livro já não está na lista de desejados
        if (!buscaLista(leitor->desejados, getIdLivro(livro)))
        {
            insereFimLista(leitor->desejados, livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
            printf("Livro adicionado aos desejados com sucesso!\n");
        }
        else
        {
            printf("Erro ao cadastrar livro nas recomendações: o Livro já está nos desejados.\n");
            return 0;
        }
    }
    else
    {
        printf("Erro ao cadastrar livro nas recomendações: o Livro já foi lido.\n");
        return 0;
    }
    return 1;
}

void imprimeLivrosDesejadosLeitor(Leitor *leitor, FILE* saida)
{
    printf("Desejados: ");
    fprintf(saida, "Desejados: ");
    imprimeLista(leitor->desejados, saida);
    printf("\n");
    fprintf(saida, "\n");
}

/**
 * RETORNA 1 = DEU CERTO
 * RETORNA 0 = DEU ERRADO (LIVRO JÁ FOI LIDO)
 * RETORNA -1 = DEU ERRADO (LIVRO JÁ ESTÁ NOS DESEJADOS)
 */
int adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador)
{
    // Cria a recomendação
    Recomendacao *nova_rec = malloc(sizeof(Recomendacao));
    nova_rec->livro = livro;
    nova_rec->recomendador = recomendador;

    if (buscaLista(destinatario->lidos, getIdLivro(livro)))
    {
        desalocaRecomendacao(nova_rec);
        return 0;
    }
    else if (buscaLista(destinatario->desejados, getIdLivro(livro)))
    {
        desalocaRecomendacao(nova_rec);
        return -1;
    }
    // Insere na lista genérica usando as funções específicas
    insereFimLista(destinatario->recomendacoes, nova_rec, desalocaRecomendacao, getTipoRec, imprimeRecomendacaoLivro, comparaRecomendacao);
    return 1;

}

void imprimeRecomendacoesLeitor(Leitor* leitor, FILE* saida)
{
    printf("Recomendacoes: ");
    fprintf(saida, "Recomendacoes: ");
    imprimeLista(leitor->recomendacoes, saida);
    printf("\n");
    fprintf(saida, "\n");
}

int aceitaRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador)
{
    // Busca a recomendação na lista
    ContextoRecomendacao ctx = {idLivro, idRecomendador};
    Recomendacao *rec = (Recomendacao *)buscaListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);

    if (rec)
    {
        // Adiciona o livro à lista de desejados
        if (!buscaLista(leitor->desejados, idLivro))
        {
            insereFimLista(leitor->desejados, rec->livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
        }

        // Remove da lista de recomendações
        removeListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
        desalocaRecomendacao(rec);
        return 1;
    }
    return 0;
}

int removerRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador)
{
    // Busca a recomendação na lista
    ContextoRecomendacao ctx = {idLivro, idRecomendador};
    Recomendacao *rec = (Recomendacao *)buscaListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);

    if (rec)
    {
        // Remove da lista de recomendações
        removeListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
        desalocaRecomendacao(rec);
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
    printf("Preferencias: ");
    fprintf(saida, "Preferencias: ");
    imprimeLista(leitor->preferencias, saida);
    printf("\n");
    fprintf(saida, "\n");
}

int temGenerosComuns(Leitor* l1, Leitor* l2)
{
    Lista* lista = temItemComumLista(l1->preferencias, l2->preferencias);
    int result = 1;
    if (listaVazia(lista))
        result = 0;
    desalocaListaStruct(lista);
    return result;
}

Lista* temLivrosComuns(Leitor* l1, Leitor* l2)
{
    return temItemComumLista(l1->lidos, l2->lidos);
}

void adicionaAfinidadeLeitor(Leitor* l1, Leitor* l2)
{
    insereFimLista(l1->afinidades, l2, NULL, getTipoAfinidade, imprimeNomeLeitor, comparaIDLeitor);
}

void imprimeAfinidadesLeitor(Leitor* leitor, FILE* saida)
{
    printf("Afinidades: ");
    fprintf(saida, "Afinidades: ");
    imprimeLista(leitor->afinidades, saida);
    printf("\n");
    fprintf(saida, "\n");
}