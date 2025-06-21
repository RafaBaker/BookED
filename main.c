#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lista.h"
#include "livro.h"

int main(int argc, char const *argv[])
{
    Lista* lista = inicializaLista();

    Livro* l1 = criaLivro(1, "ABC", "Rafael", "Ação", 2004);
    Livro* l2 = criaLivro(1, "DEF", "Penha", "Mistério", 1958);

    // imprimeLivro(l1);
    // imprimeLivro(l2);

    insereFimLista(lista, l1, desalocaLivro, imprimeLivro);
    insereFimLista(lista, l2, desalocaLivro, imprimeLivro);
    imprimeLista(lista);

    desalocaLivro(l1);
    desalocaLivro(l2);

    desalocaLista(lista);
    return 0;
}