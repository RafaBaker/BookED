#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

struct Leitor
{
    int id;
    char* nome;
    Lista* lidos;
    Lista* desejados;
    Lista* recomendacoes; //provavelmente vai ter que ser expandido para uma struct
    Lista* preferencias;
    Lista* afinidades; // lista de pessoas
    // afinidades (?)
};

Leitor* criaLeitor(int id, char* nome)
{
    Leitor* leitor = malloc(sizeof(Leitor));

    leitor->id = id;
    leitor->nome = strdup(nome);

    leitor->lidos = inicializaLista();
    leitor->desejados = inicializaLista();
    leitor->recomendacoes = inicializaLista();
    leitor->afinidades = inicializaLista();

    return leitor;
}

void desalocaLeitor(void* leitor)
{
    if (leitor)
    {
        Leitor* l = (Leitor*)leitor;

        free(l->nome);

        free(l);
    }
    leitor = NULL;
}

void imprimeLeitor(void* leitor)
{
    Leitor* l = (Leitor*)leitor;
    printf("Leitor: %s ID:%d\n", l->nome, l->id);
}

int comparaIDLeitor(void* leitor, int id)
{
    Leitor* l = (Leitor*)leitor;
    return l->id == id;
}

void adicionaLivroLidoLeitor(Leitor* leitor, Livro* livro)
{
    insereFimLista(leitor->lidos, livro, desalocaLivro, imprimeLivro, comparaIDLivro);
}

void imprimeLivrosLidosLeitor(Leitor* leitor)
{
    printf("Livros lidos:\n");
    imprimeLista(leitor->lidos);
    printf("\n\n");
}

void adicionaLivroDesejadoLeitor(Leitor* leitor, Livro* livro)
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

void imprimeLivrosDesejadosLeitor(Leitor* leitor)
{
    printf("Livros desejados:\n");
    imprimeLista(leitor->desejados);
    printf("\n\n");
}

void adicionaRecomendacao(Leitor* leitor, Livro* livro, Leitor* recomendador)
{

}