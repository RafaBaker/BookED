#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

void imprimeString(void* string)
{
    char* s = (char*)string;
    printf("%s ", s);
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

void imprimeInt(void* inteiro)
{
    int i = *(int*)inteiro;
    printf("%d ", i);
}

int getTipoString()
{
    return STRING;
}

int getTipoInt()
{
    return INT;
}