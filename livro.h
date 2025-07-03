#ifndef LIVRO_H
#define LIVRO_H

/**
 * @brief Estrutura opaca que representa um livro.
 */
typedef struct Livro Livro;

/**
 * @brief Cria uma nova estrutura Livro.
 * @param id Identificador do livro.
 * @param titulo Título do livro.
 * @param autor Autor do livro.
 * @param genero Gênero do livro.
 * @param ano Ano de publicação do livro.
 * @return Ponteiro para a estrutura Livro criada.
 */
Livro* criaLivro(int id, char* titulo, char* autor, char* genero, int ano);

/**
 * @brief Imprime o título do livro na saída padrão e em um arquivo.
 * @param livro Ponteiro para a estrutura Livro.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeLivro(void* livro, FILE* saida);

/**
 * @brief Retorna o identificador do livro.
 * @param livro Ponteiro para a estrutura Livro.
 * @return Identificador do livro.
 */
int getIdLivro(Livro* livro);

/**
 * @brief Retorna o título do livro.
 * @param livro Ponteiro para a estrutura Livro.
 * @return Ponteiro para a string com o título do livro.
 */
char* getTituloLivro(Livro* livro);

/**
 * @brief Libera a memória alocada para a estrutura Livro.
 * @param livro Ponteiro para a estrutura Livro a ser desalocada.
 */
void desalocaLivro(void* livro);

/**
 * @brief Compara o ID de um livro com um valor fornecido.
 * @param livro Ponteiro para a estrutura Livro.
 * @param id ID a ser comparado.
 * @return 1 se os IDs forem iguais, 0 caso contrário.
 */
int comparaIDLivro(void* livro, int id);

/**
 * @brief Retorna o tipo do livro.
 * @return Constante que representa o tipo LIVRO.
 */
int getTipoLivro();

#endif