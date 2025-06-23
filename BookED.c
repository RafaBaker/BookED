#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"
#include "BookED.h"

struct BookED
{
    Lista* leitores;
    Lista* livros;
};

BookED* inicializaBookED()
{
    BookED* b = malloc(sizeof(BookED));

    b->leitores = inicializaLista();
    b->livros = inicializaLista();

    return b;
}

void leLivrosArquivo(BookED* b, FILE* pLivros)
{
    char linha[200];
    // char* token;
    int id;
    char titulo[50];
    char autor[50];
    char genero[50];
    int ano;
    Livro* livro;


    fgets(linha, sizeof(linha), pLivros);
    printf("linha: %s\n", linha);

    while (fgets(linha, sizeof(linha), pLivros) != NULL)
    {
        //linha[strcspn(linha, "\n")] = '\0';  // tirando o \n e substituindo por \0

        sscanf(linha, "%d;%[^;];%[^;];%[^;];%d\n", &id, titulo, autor, genero, &ano);
        livro = criaLivro(id, titulo, autor, genero, ano);
        insereFimLista(b->livros, livro, desalocaLivro, imprimeLivro);
    }
}

void leLivrosArquivo(BookED* b, FILE* pLeitores)
{
    char linha[200];
    // char* token;
    int id;
    char titulo[50];
    char autor[50];
    char genero[50];
    int ano;
    Livro* livro;


    fgets(linha, sizeof(linha), pLeitores);
    printf("linha: %s\n", linha);

    while (fgets(linha, sizeof(linha), pLeitores) != NULL)
    {
        //linha[strcspn(linha, "\n")] = '\0';  // tirando o \n e substituindo por \0

        sscanf(linha, "%d;%[^;];%[^;];%[^;];%d\n", &id, titulo, autor, genero, &ano);
        livro = criaLivro(id, titulo, autor, genero, ano);
        insereFimLista(b->livros, livro, desalocaLivro, imprimeLivro);
    }
}