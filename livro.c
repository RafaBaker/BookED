#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "livro.h"
#include "lista.h"

/**
 * @brief Estrutura que representa um livro.
 * 
 * Contém informações como id, título, autor, gênero e ano de publicação.
 */
struct Livro
{
    int id;         /**< Identificador do livro */
    char* titulo;   /**< Título do livro */
    char* autor;    /**< Autor do livro */
    char* genero;   /**< Gênero do livro */
    int ano;        /**< Ano de publicação do livro */
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

void imprimeLivro(void* livro, FILE* saida)
{
    Livro* l = (Livro*)livro;
    printf("%s", l->titulo);
    fprintf(saida, "%s", l->titulo);
}

int getIdLivro(Livro* livro)
{
    return livro->id;
}

char* getTituloLivro(Livro* livro)
{
    return livro->titulo;
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

int getTipoLivro()
{
    return LIVRO;
}
