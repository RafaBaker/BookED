#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lista.h"
#include "livro.h"
#include "BookED.h"

int main(int argc, char const *argv[])
{
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
    // Funcionando


    recomendarLivro(b, 1, 1, 2);


    return 0;
}