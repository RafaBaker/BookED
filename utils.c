#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

void imprimeString(void* string, FILE* saida)
{
    char* s = (char*)string;
    printf("%s ", s);
    fprintf(saida, "%s ", s);
    // printf(" "); // ????????????
}

void desalocaString(void* string)
{
    char* s = (char*)string;
    if (s)
    {
        free(string);
    }
}

void desalocaInt(void* inteiro)
{
    if (inteiro)
    {
        free(inteiro);
    }
}

void imprimeInt(void* inteiro, FILE* saida)
{
    int i = *(int*)inteiro;
    printf("%d ", i);
    fprintf(saida, "%d ", i);
}

int getTipoString()
{
    return STRING;
}

int getTipoInt()
{
    return INT;
}