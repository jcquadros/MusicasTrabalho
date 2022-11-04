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
Musica musica_cria();

// ler arquivo de musica
void musicas_ler_full(FILE* file, Musica musica);
size_t musica_ler(FILE *file, Musica musica);

// separar as musicas
void musica_tok(Musica musica, char *musica_str, size_t len);

// imprimir uma musica
void musica_mostrar(Musica musica);

// desaloca varioas musicas
void musica_destroy(Musica musica);
void musica_atributos_destroy(Musica musica, int idx);
// salva atributos da musica
char *musica_salva_string(char *string_in);
float musica_salva_float(char *float_str);
int musica_salva_inteiro(char *inteiro_str);
// musica->artista_lista = musica_seta_artistas(musica, artists, id_artists);
char **musica_salva_artistas_str(char *artistas_str);
#endif