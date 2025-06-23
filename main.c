#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lista.h"
#include "livro.h"
#include "BookED.h"

int main(int argc, char const *argv[])
{
    // Lista lista = inicializaLista();

    // Livro* l1 = criaLivro(1, "ABC", "Rafael", "Ação", 2004);
    // Livro* l2 = criaLivro(1, "DEF", "Penha", "Mistério", 1958);

    // // imprimeLivro(l1);
    // // imprimeLivro(l2);

    // insereFimLista(lista, l1, desalocaLivro, imprimeLivro);
    // insereFimLista(lista, l2, desalocaLivro, imprimeLivro);
    // imprimeLista(lista);

    // desalocaLivro(l1);
    // desalocaLivro(l2);

    // desalocaLista(lista);

    BookED* b = inicializaBookED();


    char arquivoLivros[200];
    // printf("%s/livros.txt", argv[1]);
    sprintf(arquivoLivros, "%s/livros.txt", argv[1]);
    FILE* pLivros;
    pLivros = fopen(arquivoLivros, "r");
    if (!pLivros)
    {
        printf("Erro ao abrir arquivo de livros\n");
        exit(0);
    }

    leLivrosArquivo(b, pLivros);
    fclose(pLivros);


    char arquivoLeitores[200];
    sprintf(arquivoLeitores, "%s/leitores.txt", argv[1]);
    FILE* pLeitores;
    pLeitores = fopen(arquivoLeitores, "r");
    if (!pLeitores)
    {
        printf("Erro ao abrir arquivo de leitores\n");
        exit(0);
    }

    leLeitoresArquivo(b, pLeitores);
    fclose(pLeitores);

    imprimeLivros(b);
    imprimeLeitores(b);

    adicionaLivroLido(b, 1, 1);
    adicionaLivroLido(b, 1, 2);
    adicionaLivroLido(b, 1, 3);
    adicionaLivroLido(b, 1, 20);
    // FUNCIONANDO !

    adicionarLivroDesejado(b, 1, 4);


    return 0;
}