#ifndef LIVRO_H
#define LIVRO_H

typedef struct Livro Livro;

Livro* criaLivro(int id, char* titulo, char* autor, char* genero, int ano);

void imprimeLivro(void* livro);

void desalocaLivro(void* livro);

#endif