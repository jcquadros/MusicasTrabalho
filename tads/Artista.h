#ifndef _ARTISTA_H_
#define _ARTISTA_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define QTD_ATRIBUTOS_ARTISTA 5

typedef struct artista *Artista;

typedef enum artista_atributos Artista_atributos;

// abre corretamente o arquivo
FILE *artista_abre_arquivo(int argc, char **argv);

// aloca espaco para uma artista
Artista artista_create();

// ler arquivo de artista
size_t artista_read(FILE *file, Artista artista);

// separar as informacoes da artista em tokens e armazena-la no tipo
void artista_tok(Artista artista, char *artista_str);

// imprimir uma artista
void artista_print(Artista artista);

// desaloca artista
void artista_destroy(Artista artista);

// salva atributos da artista
char *artista_salva_string(char *string_in);
float artista_salva_float(char *float_str);
int artista_salva_inteiro(char *inteiro_str);
char **artista_salva_generos(char *generos_str, int *generos_len);

#endif