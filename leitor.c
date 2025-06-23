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
    Lista* recomendacoes;
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
}
