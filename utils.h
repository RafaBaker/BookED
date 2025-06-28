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

void imprimeString(void* string, FILE* saida);

void desalocaString(void* string);

void desalocaInt(void* inteiro);

void imprimeInt(void* inteiro, FILE* saida);

int getTipoString();

int getTipoInt();


#endif