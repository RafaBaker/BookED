#ifndef LIVRO_H
#define LIVRO_H

typedef struct Livro Livro;

Livro* criaLivro(int id, char* titulo, char* autor, char* genero, int ano);

void imprimeLivro(void* livro);

int getIdLivro(Livro* livro);

void desalocaLivro(void* livro);

int comparaIDLivro(void* livro, int id);

int getTipoLivro();

#endif