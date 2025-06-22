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
    Lista* afinidades;
    // afinidades (?)
};

Leitor* criaLeitor(int id, char* nome)
{
    Leitor* leitor = malloc(sizeof(Leitor));

    leitor->id = id;
    leitor->nome = strdup(nome);

    leitor->lidos = NULL;
    leitor->desejados = NULL;
    leitor->recomendacoes = NULL;
    leitor->afinidades = NULL;

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