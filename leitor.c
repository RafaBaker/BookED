#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
static void imprimeRecomendacaoLivro(void *rec)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    imprimeLivro(recomendacao->livro); // Supondo que você tenha esta função
}

// Função para imprimir uma recomendação
static void imprimeRecomendacao(void *rec)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    printf("Livro recomendado: ");
    imprimeLivro(recomendacao->livro); // Supondo que você tenha esta função
    printf("Recomendado por ");
    imprimeLeitor(recomendacao->recomendador);
}

// Função para desalocar uma recomendação
static void desalocaRecomendacao(void *rec)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    free(recomendacao);
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
    Lista *recomendacoes; // provavelmente vai ter que ser expandido para uma struct
    Lista *preferencias;
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
    leitor->afinidades = inicializaLista();

    return leitor;
}

void desalocaLeitor(void *leitor)
{
    if (leitor)
    {
        Leitor *l = (Leitor *)leitor;

        free(l->nome);

        free(l);
    }
    leitor = NULL;
}

int getTipoLeitor()
{
    return LEITOR;
}

void imprimeNomeLeitor(void *leitor)
{
    Leitor *l = (Leitor *)leitor;
    printf("%s", l->nome);
}

void imprimeIdLeitor(void *leitor)
{
    Leitor *l = (Leitor *)leitor;
    printf("%d", l->id);
}

void imprimeLeitor(void *leitor)
{
    Leitor *l = (Leitor *)leitor;
    printf("\nLeitor: ");
    imprimeNomeLeitor(leitor);
    printf("\n");
    
    //Livros lidos
    imprimeLivrosLidosLeitor(l);

    //Livros desejados
    imprimeLivrosDesejadosLeitor(l);

    //Livros recomendados
    imprimeRecomendacoesLeitor(l);

}

int comparaIDLeitor(void *leitor, int id)
{
    Leitor *l = (Leitor *)leitor;
    return l->id == id;
}

void adicionaLivroLidoLeitor(Leitor *leitor, Livro *livro)
{
    insereFimLista(leitor->lidos, livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
}

void imprimeLivrosLidosLeitor(Leitor *leitor)
{
    printf("Lidos: ");
    imprimeLista(leitor->lidos);
    printf("\n");
}

void adicionaLivroDesejadoLeitor(Leitor *leitor, Livro *livro)
{
    // Vendo se o livro não está na lista de lidos
    if (!buscaLista(leitor->lidos, getIdLivro(livro)))
    {
        insereFimLista(leitor->desejados, livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
        printf("Livro adicionado aos recomendados com sucesso!\n");
    }
    else
    {
        printf("Erro ao cadastrar livro nas recomendações: o Livro já foi lido.\n");
    }
}

void imprimeLivrosDesejadosLeitor(Leitor *leitor)
{
    printf("Desejados: ");
    imprimeLista(leitor->desejados);
    printf("\n");
}

void adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador)
{
    // Cria a recomendação
    Recomendacao *nova_rec = malloc(sizeof(Recomendacao));
    nova_rec->livro = livro;
    nova_rec->recomendador = recomendador;

    // Insere na lista genérica usando as funções específicas
    insereFimLista(destinatario->recomendacoes, nova_rec, desalocaRecomendacao, getTipoRec, imprimeRecomendacaoLivro, comparaRecomendacao);
}

void imprimeRecomendacoesLeitor(Leitor* leitor)
{
    printf("Recomendacoes: ");
    imprimeLista(leitor->recomendacoes);
    printf("\n");
}

void aceitaRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador)
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
    }
}

void removerRecomendacaoLeitor(Leitor *leitor, int idLivro, int idRecomendador)
{
    // Busca a recomendação na lista
    ContextoRecomendacao ctx = {idLivro, idRecomendador};
    Recomendacao *rec = (Recomendacao *)buscaListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);

    if (rec)
    {
        // Remove da lista de recomendações
        removeListaComContexto(leitor->recomendacoes, comparaRecomendacaoComContexto, &ctx);
    }
}