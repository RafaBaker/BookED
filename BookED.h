#ifndef BOOKED_H
#define BOOKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "leitor.h"
#include "livro.h"
#include "lista.h"

typedef struct BookED BookED;


BookED* inicializaBookED();

void leLivrosArquivo(BookED* b, FILE* pLivros);


#endif