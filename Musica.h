#ifndef _MUSICAS_H_
#define _MUSICAS_H_
#define ALOCAR 100
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct musica *Musica;
typedef enum musica_atributos Musica_atributos;


FILE* musica_abre_arquivo(int argc, char** argv);
// ler arquivo de musica
size_t musica_ler(FILE* file, Musica musica);
Musica musica_init(char* linha);
// separar as musicas
void musica_tok(Musica musica, char* musica_str, size_t len);
// alocar musica e retornar seu ponteiro
//struct vector musica_add(Musica* musica,);
// salvar musica no vetor de musica
// imprimir uma musica
void rect_mostrar(Musica musica);
void musica_destroy(Musica musica);
#endif