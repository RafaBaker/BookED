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
        //imprimePreferenciasLeitor(leitor);
    }
    inicializaAfinidades(b);
}

// // Ajeitar essas duas bombas
// void imprimeLeitores(BookED* b)
// {
//     printf("LISTA DE LEITORES\n");
//     imprimeLista(b->leitores, saida);
//     printf("\n\n");
// }

// void imprimeLivros(BookED* b)
// {
//     printf("LISTA DE LIVROS\n");
//     imprimeLista(b->livros);
//     printf("\n\n");
// }

void adicionaLivroLido(BookED* b, int idLeitor, int idLivro, FILE* saida)
{
    Leitor* leitor = (Leitor*)buscaLista(b->leitores, idLeitor);
    if (!leitor)
    {
        fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitor);
        return;
    }

    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);
    if (!livro)
    {
        fprintf(saida, "Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }
    // if (livro)
    //     //imprimeLivro(livro);
    int f = 0;
    f = adicionaLivroLidoLeitor(leitor, livro);
    if (f)
        fprintf(saida, "%s leu \"%s\"\n", getNomeLeitor(leitor), getTituloLivro(livro));
    else
        fprintf(saida, "%s já leu \"%s\"\n", getNomeLeitor(leitor), getTituloLivro(livro));
    //imprimeLivrosLidosLeitor(leitor);

}

void adicionarLivroDesejado(BookED* b, int idLeitor, int idLivro, FILE* saida)
{
    //Pegando livro e leitor
    Leitor* leitor = (Leitor*)buscaLista(b->leitores, idLeitor);
    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);

    if (!leitor)
    {
        fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitor);
        return;
    }
    if (!livro)
    {
        fprintf(saida, "Erro: Livro com ID %d não encontrado\n", idLivro);
        return;
    }

    int f = 0;
    if (livro) f = adicionaLivroDesejadoLeitor(leitor, livro);
    // imprimeLivrosDesejadosLeitor(leitor);
    if (f)
        fprintf(saida, "%s deseja ler \"%s\"\n", getNomeLeitor(leitor), getTituloLivro(livro));
    else
        fprintf(saida, "%s já deseja ler \"%s\"\n", getNomeLeitor(leitor), getTituloLivro(livro));

}

void recomendarLivro(BookED* b, int idRecomendador, int idLivro, int idDestinatario, FILE* saida)
{
    Leitor* recomendador = (Leitor*)buscaLista(b->leitores, idRecomendador);
    Leitor* destinatario = (Leitor*)buscaLista(b->leitores, idDestinatario);;
    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);

    if (!recomendador)
    {
        printf("Recomendador não achado\n");
        return;
    }
    if (!destinatario)
    {
        printf("Destinatario não achado\n");
        return;
    }
    if (!livro)
    {
        printf("Livro não encontrado para recomendação\n");
        return;
    }
    if (destinatario == recomendador)
    {
        fprintf(saida, "%s não pode recomendar livros para si mesmo\n", getNomeLeitor(destinatario));
        return;
    }

    int f = adicionaRecomendacao(destinatario, livro, recomendador);
    if (f == 1)
        fprintf(saida, "%s recomenda \"%s\" para %s\n", getNomeLeitor(recomendador), getTituloLivro(livro), getNomeLeitor(destinatario));
    else if (f == 0)
        fprintf(saida, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", getNomeLeitor(destinatario), getTituloLivro(livro));
    else if (f == -1)
        fprintf(saida, "%s já deseja ler \"%s\", recomendação desnecessária\n", getNomeLeitor(destinatario), getTituloLivro(livro));
    // imprimeRecomendacoesLeitor(destinatario);
}

void aceitarRecomendacao(BookED* b, int idDestinatario, int idLivro, int idRecomendador, FILE* saida)
{
    Leitor* destinatario = (Leitor*)buscaLista(b->leitores, idDestinatario);;
    Leitor* recomendador = (Leitor*)buscaLista(b->leitores, idRecomendador);
    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);

    if (!recomendador)
    {
        fprintf(saida, "Erro: Leitor recomendador com ID %d não encontrado\n", idRecomendador);
        return;
    }
    if (!destinatario)
    {
        fprintf(saida, "Erro: Leitor destinatário com ID %d não encontrado\n", idDestinatario);
        return;
    }
    if (!livro)
    {
        printf("Livro não encontrado para recomendação\n");
        return;
    }

    if (aceitaRecomendacaoLeitor(destinatario, idLivro, idRecomendador))
        fprintf(saida, "%s aceita recomendação \"%s\" de %s\n", getNomeLeitor(destinatario), getTituloLivro(livro), getNomeLeitor(recomendador));
    else
        fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", getNomeLeitor(destinatario), getIdLivro(livro), getNomeLeitor(recomendador));
    // imprimeRecomendacoesLeitor(destinatario);
    // imprimeLivrosDesejadosLeitor(destinatario);
}

void removerRecomendacao(BookED* b, int idDestinatario, int idLivro, int idRecomendador, FILE* saida)
{
    Leitor* destinatario = (Leitor*)buscaLista(b->leitores, idDestinatario);;
    Leitor* recomendador = (Leitor*)buscaLista(b->leitores, idRecomendador);
    Livro* livro = (Livro*)buscaLista(b->livros, idLivro);

    if (!recomendador)
    {
        printf("Recomendador não achado\n");
        return;
    }
    if (!destinatario)
    {
        printf("Destinatario não achado\n");
        return;
    }
    if (!livro)
    {
        printf("Livro não encontrado para recomendação\n");
        return;
    }

    if (removerRecomendacaoLeitor(destinatario, idLivro, idRecomendador))
        fprintf(saida, "%s rejeita recomendação \"%s\" de %s\n", getNomeLeitor(destinatario), getTituloLivro(livro), getNomeLeitor(recomendador));
    else
        fprintf(saida, "%s não possui recomendação do livro ID %d feita por %s\n", getNomeLeitor(destinatario), getIdLivro(livro), getNomeLeitor(recomendador));
}

void imprimeBookEd(BookED* b, FILE* saida)
{
    printf("Imprime toda a BookED\n");
    fprintf(saida, "Imprime toda a BookED\n");
    imprimeLista(b->leitores, saida);
}


int desalocaBookEd(BookED* b)
{
    if (b)
    {
        desalocaLista(b->livros);
        desalocaLista(b->leitores);
        desalocaLista(b->afinidades);
        free(b);
    }
    b = NULL;
    return 1;
}

void inicializaAfinidades(BookED* b)
{
    FILE* pTeste = fopen("teste.txt", "w");
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
                // int* id = malloc(sizeof(int));
                // *id = j;
                // insereFimLista(afLeitor, id, desalocaInt, getTipoInt, imprimeInt, NULL);
                insereFimLista(afLeitor, aux, NULL, getTipoLeitor, imprimeNomeLeitor, comparaIDLeitor);
                adicionaAfinidadeLeitor(leitor, aux);
            }

        }
        setIdLista(afLeitor,  i);
        imprimeLista(afLeitor, pTeste);
        printf("\n");
        // Carregando as afinidades
        insereFimLista(b->afinidades, afLeitor, desalocaLista, getTipoLista, imprimeListaStruct, comparaLista);
    }

    // imprimeLista(b->afinidades, NULL);
}

void verificarAfinidade(BookED* b, int idLeitorOrigem, int idLeitorDestino, FILE* saida)
{
    int result = 0;
    int* visitado = NULL;
    Leitor* l1 = buscaLista(b->leitores, idLeitorOrigem);
    Leitor* l2 = buscaLista(b->leitores, idLeitorDestino);

    if (!l1)
    {
        fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitorOrigem);
        return;
    }
    if (!l2)
    {
        fprintf(saida, "Erro: Leitor com ID %d não encontrado\n", idLeitorDestino);
        return;
    }

    if (idLeitorDestino == idLeitorOrigem)
    {
        result = 1;
    }
    else
    {
        int tamanho = quantidadeLista(b->afinidades);
        visitado = calloc(tamanho, sizeof(int));
        
        result = buscaAfinidade(b, idLeitorOrigem-1, idLeitorDestino-1, visitado);
    }

    if (result)
        fprintf(saida, "Existe afinidade entre %s e %s\n", getNomeLeitor(l1), getNomeLeitor(l2));
    else
    {
        fprintf(saida, "NÃO existe afinidade entre %s e %s\n", getNomeLeitor(l1), getNomeLeitor(l2));
    }

    if (visitado) free(visitado);

}

static int buscaAfinidade(BookED* b, int idLeitorOrigem, int idLeitorDestino, int* visitado)
{
    int result = 0;
    if (idLeitorOrigem == idLeitorDestino) return 1;
    visitado[idLeitorOrigem] = 1;
    Celula* aux = getCelula(buscaLista(b->afinidades, idLeitorOrigem+1));
    for (int i = 0; aux != NULL; i++, aux = proximaCelula(aux))
    {
        int indice = getIdLista(getItemCelula(aux)) - 1;
        // printf("nada\n");
        if (!visitado[indice])
            result += buscaAfinidade(b, indice, idLeitorDestino, visitado);
    }
    return result;
}

void executaBookED(BookED* b, FILE* pComandos, FILE* pSaida)
{
    char linha[200];
    int idComando = 0;
    int id1 = 0;
    int id2 = 0;
    int id3 = 0;
    fgets(linha, sizeof(linha), pComandos);

    while (fgets(linha, sizeof(linha), pComandos) != NULL)
    {
        sscanf(linha, "%d;%d;%d;%d", &idComando, &id1, &id2, &id3);

        switch (idComando)
        {
        case 1:
            adicionaLivroLido(b, id1, id2, pSaida);
            break;
        case 2:
            adicionarLivroDesejado(b, id1, id2, pSaida);
            break;
        case 3:
            recomendarLivro(b, id1, id2, id3, pSaida);
            break;
        case 4:
            aceitarRecomendacao(b, id1, id2, id3, pSaida);
            break;
        case 5:
            removerRecomendacao(b, id1, id2, id3, pSaida);
            break;
        case 6:
            printf("Livros em comum WIP\n");
            fprintf(pSaida, "Livros em comum WIP\n");
            break;
        case 7:
            verificarAfinidade(b, id1, id3, pSaida);
            break;
        case 8:
            imprimeBookEd(b, pSaida);
            break;
        
        default:
            printf("Erro: Comando %d não reconhecido\n", idComando);
            fprintf(pSaida, "Erro: Comando %d não reconhecido\n", idComando);
            break;
        }
    }
}