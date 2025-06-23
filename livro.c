#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "livro.h"

struct Livro
{
    int id;
    char* titulo;
    char* autor;
    char* genero;
    int ano;
};

Livro* criaLivro(int id, char* titulo, char* autor, char* genero, int ano)
{
    Livro* livro = malloc(sizeof(Livro));

    livro->id = id;
    livro->ano = ano;

    livro->titulo = strdup(titulo);
    livro->autor = strdup(autor);
    livro->genero = strdup(genero);

    return livro;
}

void imprimeLivro(void* livro)
{
    Livro* l = (Livro*)livro;
    printf("Titulo do livro: %s\n", l->titulo);
}

int getIdLivro(Livro* livro)
{
    return livro->id;
}

void desalocaLivro(void* livro)
{
    if (livro)
    {
        Livro* l = (Livro*)livro;
        if (l->titulo) free(l->titulo);
        l->titulo = NULL;
        if (l->autor) free(l->autor);
        l->autor = NULL;
        if (l->genero) free(l->genero);
        l->genero = NULL;
        free(l);
    }
    livro = NULL;
}

int comparaIDLivro(void* livro, int id)
{
    Livro* l = (Livro*)livro;
    return l->id == id;
}
