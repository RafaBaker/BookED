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
    // printf("linha: %s\n", linha);

    while (fgets(linha, sizeof(linha), pLivros) != NULL)
    {
        //linha[strcspn(linha, "\n")] = '\0';  // tirando o \n e substituindo por \0

        sscanf(linha, "%d;%[^;];%[^;];%[^;];%d\n", &id, titulo, autor, genero, &ano);
        livro = criaLivro(id, titulo, autor, genero, ano);
        insereFimLista(b->livros, livro, desalocaLivro, imprimeLivro, comparaIDLivro);
    }
}

void leLeitoresArquivo(BookED* b, FILE* pLeitores)
{
    char linha[200];
    // char* token;
    int id;
    int qtdAfinidades;
    char nome[50];
    int ano;
    Leitor* leitor;


    fgets(linha, sizeof(linha), pLeitores);
    // printf("linha: %s\n", linha);

    while (fgets(linha, sizeof(linha), pLeitores) != NULL)
    {
        //linha[strcspn(linha, "\n")] = '\0';  // tirando o \n e substituindo por \0

        sscanf(linha, "%d;%[^;];", &id, nome);
        leitor = criaLeitor(id, nome);
        insereFimLista(b->leitores, leitor, desalocaLeitor, imprimeLeitor, comparaIDLeitor);
    }
}

void imprimeLeitores(BookED* b)
{
    printf("LISTA DE LEITORES\n");
    imprimeLista(b->leitores);
    printf("\n\n");
}

void imprimeLivros(BookED* b)
{
    printf("LISTA DE LIVROS\n");
    imprimeLista(b->livros);
    printf("\n\n");
}

void adicionaLivroLido(BookED* b, int idLeitor, int idLivro)
{
    Leitor* leitor = (Leitor*)buscaLista(b->leitores, idLeitor);
    imprimeLeitor(leitor);

    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);
    if (livro) imprimeLivro(livro);

    if (livro) adicionaLivroLidoLeitor(leitor, livro);
    imprimeLivrosLidosLeitor(leitor);

}

void adicionarLivroDesejado(BookED* b, int idLeitor, int idLivro)
{
    //Pegando livro e leitor
    Leitor* leitor = (Leitor*)buscaLista(b->leitores, idLeitor);
    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);

    if (livro) adicionaLivroDesejadoLeitor(leitor, livro);
    imprimeLivrosDesejadosLeitor(leitor);

}

void recomendarLivro(BookED* b, int idRecomendador, int idLivro, int idRecomendado)
{
    Leitor* recomendador = (Leitor*)buscaLista(b->leitores, idRecomendador);
    Leitor* recomendado = (Leitor*)buscaLista(b->leitores, idRecomendado);;
    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);

    if (!recomendador)
    {
        printf("Recomendador não achado\n");
        return;
    }
    if (!recomendado)
    {
        printf("Recomendado não achado\n");
        return;
    }
    if (!livro)
    {
        printf("Livro não encontrado para recomendação");
        return;
    }

    adicionaRecomendacao(recomendado, livro, recomendador);
}
