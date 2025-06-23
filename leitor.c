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

static int comparaRecomendacao(void *rec, int id_livro)
{
    Recomendacao *recomendacao = (Recomendacao *)rec;
    return (getIdLivro(recomendacao->livro) == id_livro);
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

void imprimeLeitor(void *leitor)
{
    Leitor *l = (Leitor *)leitor;
    printf("Leitor: %s ID:%d\n", l->nome, l->id);
}

int comparaIDLeitor(void *leitor, int id)
{
    Leitor *l = (Leitor *)leitor;
    return l->id == id;
}

void adicionaLivroLidoLeitor(Leitor *leitor, Livro *livro)
{
    insereFimLista(leitor->lidos, livro, desalocaLivro, imprimeLivro, comparaIDLivro);
}

void imprimeLivrosLidosLeitor(Leitor *leitor)
{
    printf("Livros lidos:\n");
    imprimeLista(leitor->lidos);
    printf("\n\n");
}

void adicionaLivroDesejadoLeitor(Leitor *leitor, Livro *livro)
{
    // Vendo se o livro não está na lista de lidos
    if (!buscaLista(leitor->lidos, getIdLivro(livro)))
    {
        insereFimLista(leitor->desejados, livro, desalocaLivro, imprimeLivro, comparaIDLivro);
        printf("Livro adicionado aos recomendados com sucesso!\n");
    }
    else
    {
        printf("Erro ao cadastrar livro nas recomendações: o Livro já foi lido.\n");
    }
}

void imprimeLivrosDesejadosLeitor(Leitor *leitor)
{
    printf("Livros desejados:\n");
    imprimeLista(leitor->desejados);
    printf("\n\n");
}

void adicionaRecomendacao(Leitor *destinatario, Livro *livro, Leitor *recomendador)
{
    // Cria a recomendação
    Recomendacao *nova_rec = malloc(sizeof(Recomendacao));
    nova_rec->livro = livro;
    nova_rec->recomendador = recomendador;

    // Insere na lista genérica usando as funções específicas
    insereFimLista(destinatario->recomendacoes, nova_rec, desalocaRecomendacao, imprimeRecomendacao, comparaRecomendacao);
}

void imprimeRecomendacoesLeitor(Leitor* leitor)
{
    printf("Livros recomendados de %s:\n", leitor->nome);
    imprimeLista(leitor->recomendacoes);
    printf("\n\n");
}

void aceitaRecomendacaoLeitor(Leitor *leitor, int id_livro)
{
    // Busca a recomendação na lista
    Recomendacao *rec = (Recomendacao *)buscaLista(leitor->recomendacoes, id_livro);

    if (rec)
    {
        // Adiciona o livro à lista de desejados
        insereFimLista(leitor->desejados, rec->livro, desalocaLivro, imprimeLivro, comparaIDLivro);

        // Remove da lista de recomendações
        removeLista(leitor->recomendacoes, id_livro);
    }
}