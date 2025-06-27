#ifndef UTILS_H
#define UTILS_H

enum Tipo
{
    LIVRO,
    LEITOR,
    RECOMENDACAO,
    STRING,
    LISTA,
    INT,
};

void imprimeString(void* string);

void desalocaString(void* string);

void desalocaInt(void* inteiro);

void imprimeInt(void* inteiro);

int getTipoString();

int getTipoInt();


#endif