#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Enumeração dos tipos de dados suportados.
 */
enum Tipo
{
    LIVRO,        /**< Tipo livro */
    LEITOR,       /**< Tipo leitor */
    RECOMENDACAO, /**< Tipo recomendação */
    STRING,       /**< Tipo string */
    LISTA,        /**< Tipo lista */
    INT,          /**< Tipo inteiro */
    AFINIDADE,    /**< Tipo afinidade */
};

/**
 * @brief Imprime uma string na saída padrão e em um arquivo.
 * @param string Ponteiro para a string.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeString(void* string, FILE* saida);

/**
 * @brief Libera a memória alocada para uma string.
 * @param string Ponteiro para a string a ser desalocada.
 */
void desalocaString(void* string);

/**
 * @brief Libera a memória alocada para um inteiro.
 * @param inteiro Ponteiro para o inteiro a ser desalocado.
 */
void desalocaInt(void* inteiro);

/**
 * @brief Imprime um inteiro na saída padrão e em um arquivo.
 * @param inteiro Ponteiro para o inteiro.
 * @param saida Ponteiro para o arquivo de saída.
 */
void imprimeInt(void* inteiro, FILE* saida);

/**
 * @brief Obtém o tipo de uma string.
 * @return O tipo da string.
 */
int getTipoString();

/**
 * @brief Obtém o tipo de um inteiro.
 * @return O tipo do inteiro.
 */
int getTipoInt();

/**
 * @brief Obtém o tipo de afinidade.
 * @return O tipo de afinidade.
 */
int getTipoAfinidade();

#endif