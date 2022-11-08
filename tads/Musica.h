#ifndef _MUSICAS_H_
#define _MUSICAS_H_
/*Numeros magicos*/

#define ALOCAR 100
#define QTD_ATRIBUTOS_MUSICA 20
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct musica *Musica;

typedef enum musica_atributos Musica_atributos;

// abre corretamente o arquivo
FILE *musica_abre_arquivo(int argc, char **argv);

// aloca espaco para uma musica
Musica musica_create();

// ler arquivo de musica
size_t musica_read(FILE *file, Musica musica);

// separar as informacoes da musica em tokens e armazena-la no tipo
void musica_tok(Musica musica, char *musica_str);

// imprimir uma musica
void musica_print(Musica musica);

// desaloca musica
void musica_destroy(Musica musica);

// salva atributos da musica
char *musica_salva_string(char *string_in);
float musica_salva_float(char *float_str);
int musica_salva_inteiro(char *inteiro_str);
char **musica_salva_artistas(char *artistas_str, int *n_artistas);
char *musica_get_id(Musica musica);
Musica musica_add_idx_artistas(Musica musica, int *idx_artistas);
char **musica_get_lista_artistas(Musica musica);
int musica_get_n_artistas(Musica musica);
#endif