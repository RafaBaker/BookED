#ifndef UTILS_H
#define UTILS_H

enum Tipo
{
    LIVRO,
    LEITOR,
    RECOMENDACAO,
    STRING
};

void imprimeString(void* string);

void desalocaString(void* string);

int getTipoString();

#endif