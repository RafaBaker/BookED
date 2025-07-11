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
    if (argc > 1)
    {
        sprintf(arquivoLivros, "%s/livros.txt", argv[1]);
    }
    else
    {
        sprintf(arquivoLivros, "livros.txt");
    }
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
    if (argc > 1)
    {
        sprintf(arquivoLeitores, "%s/leitores.txt", argv[1]);
    }
    else
    {
        sprintf(arquivoLeitores, "leitores.txt");
    }
    FILE* pLeitores;
    pLeitores = fopen(arquivoLeitores, "r");
    if (!pLeitores)
    {
        printf("Erro ao abrir arquivo de leitores\n");
        exit(0);
    }

    leLeitoresArquivo(b, pLeitores);
    fclose(pLeitores);

    char arquivoComandos[200];
    if (argc > 1)
    {
        sprintf(arquivoComandos, "%s/comandos.txt", argv[1]);
    }
    else
    {
        sprintf(arquivoComandos, "comandos.txt");
    }
    FILE* pComandos;
    pComandos = fopen(arquivoComandos, "r");
    if (!pComandos)
    {
        printf("Erro ao abrir arquivo de comandos\n");
        exit(0);
    }

    FILE* pSaida = fopen("saida.txt", "w");

    executaBookED(b, pComandos, pSaida);
    fclose(pComandos);
    fclose(pSaida);


    // imprimeLivros(b);
    // imprimeLeitores(b);

    // adicionaLivroLido(b, 1, 1);
    // adicionaLivroLido(b, 1, 2);
    // adicionaLivroLido(b, 1, 3);
    // adicionaLivroLido(b, 1, 20);
    // // FUNCIONANDO !

    // adicionarLivroDesejado(b, 1, 4);
    // // Funcionando


    // recomendarLivro(b, 1, 1, 2);
    // recomendarLivro(b, 1, 2, 2);
    // recomendarLivro(b, 1, 3, 2);
    
    
    // aceitarRecomendacao(b, 2, 1, 1);
    // imprimeBookEd(b);

    // printf("==================\n");

    // removerRecomendacao(b, 2, 3, 1);
    // imprimeBookEd(b);

    // inicializaAfinidades(b);


    // Testando as afinidades
    // int test1 = 7, test2 = 9;
    // if (verificarAfinidade(b, test1, test2)) printf("Leitor de id %d tem afinidade com Leitor de id %d\n", test1, test2);
    // else printf("Leitor de id %d NÃO tem afinidade com Leitor de id %d\n", test1, test2);

    if(desalocaBookEd(b)) printf("BookED desalocado com sucesso.\n");
    

    return 0;
}