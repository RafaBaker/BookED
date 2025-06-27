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
    Lista* afinidades;
};

BookED* inicializaBookED()
{
    BookED* b = malloc(sizeof(BookED));

    b->leitores = inicializaLista();
    b->livros = inicializaLista();
    b->afinidades = inicializaLista();

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
        insereFimLista(b->livros, livro, desalocaLivro, getTipoLivro, imprimeLivro, comparaIDLivro);
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
        linha[strcspn(linha, "\n")] = '\0';  // tirando o \n e substituindo por \0

        sscanf(linha, "%d;%[^;];", &id, nome);

        leitor = criaLeitor(id, nome);
        
        //Fatiando a string para pegar as afinidades
        char* token = strtok(linha, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");
        if (token) qtdAfinidades = atoi(token);
        
        for (int i = 0; i < qtdAfinidades; i++)
        {
            token = strtok(NULL, ";");
            char* afinidade = strdup(token);
            inserePreferenciaLeitor(leitor, afinidade);
        }
        
        insereFimLista(b->leitores, leitor, desalocaLeitor, getTipoLeitor, imprimeLeitor, comparaIDLeitor);
        imprimePreferenciasLeitor(leitor);
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
        printf("Livro não encontrado para recomendação\n");
        return;
    }

    adicionaRecomendacao(recomendado, livro, recomendador);
    imprimeRecomendacoesLeitor(recomendado);
}

void aceitarRecomendacao(BookED* b, int idRecomendado, int idLivro, int idRecomendador)
{
    Leitor* recomendado = (Leitor*)buscaLista(b->leitores, idRecomendado);;
    Leitor* recomendador = (Leitor*)buscaLista(b->leitores, idRecomendador);
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
        printf("Livro não encontrado para recomendação\n");
        return;
    }

    aceitaRecomendacaoLeitor(recomendado, idLivro, idRecomendador);
    // imprimeRecomendacoesLeitor(recomendado);
    // imprimeLivrosDesejadosLeitor(recomendado);
}

void removerRecomendacao(BookED* b, int idRecomendado, int idLivro, int idRecomendador)
{
    Leitor* recomendado = (Leitor*)buscaLista(b->leitores, idRecomendado);;
    Leitor* recomendador = (Leitor*)buscaLista(b->leitores, idRecomendador);
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
        printf("Livro não encontrado para recomendação\n");
        return;
    }

    removerRecomendacaoLeitor(recomendado, idLivro, idRecomendador);
}

void imprimeBookEd(BookED* b)
{
    imprimeLista(b->leitores);
}


int desalocaBookEd(BookED* b)
{
    if (b)
    {
        desalocaLista(b->livros);
        desalocaLista(b->leitores);
        free(b);
    }
    b = NULL;
    return 1;
}

void inicializaAfinidades(BookED* b)
{
    int qtdLeitores = quantidadeLista(b->leitores);
    for (int i = 1; i <= qtdLeitores; i++)
    {
        Lista* afLeitor = inicializaLista();
        Leitor* leitor = buscaLista(b->leitores, i);
        // imprimePreferenciasLeitor(leitor);

        for (int j = 1; j <=qtdLeitores; j++)
        {
            if (i==j) continue;

            Leitor* aux = buscaLista(b->leitores, j);

            if (temGenerosComuns(leitor, aux))
            {
                int* id = malloc(sizeof(id));
                *id = j;
                insereFimLista(afLeitor, id, free, getTipoInt, imprimeInt, NULL);
            }

        }
        setaIdLista(afLeitor,  i);
        imprimeLista(afLeitor);
        printf("\n");
        // Carregando as afinidades
        insereFimLista(b->afinidades, afLeitor, desalocaListaStruct, getTipoLista, imprimeListaStruct, NULL);
    }
    imprimeLista(b->afinidades);
}

void carregaAfinidades(BookED* b)
{
    
}