#ifndef _MUSICAS_H_
#define _MUSICAS_H_
/*Numeros magicos*/
#define ALOCAR 100
#define QTD_ATRIBUTOS_MUSICA 20
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//typedef struct musica *Musica;

typedef struct musica
{
	char *id;
	char *nome_da_musica;
	int popularity;
	int duracao_ms;
	int explict;
	// Artista* artistas_lista;
	char *artists;
	char *id_artists;
	char *data_lancamento;
	float danceability;
	float energy; //
	int key;
	float loundness;
	int mode;				//
	float speechiness;		//
	float acousticness;		//
	float instrumentalness; //
	float liveness;			//
	float valence;			//
	float tempo;
	int time_assignature;
}*Musica;

typedef enum musica_atributos Musica_atributos;

FILE *musica_abre_arquivo(int argc, char **argv);
// ler arquivo de musica
size_t musica_ler(FILE *file, Musica musica);
Musica musica_init(char *linha);
// separar as musicas
void musica_tok(Musica musica, char *musica_str, size_t len);
// alocar musica e retornar seu ponteiro
// struct vector musica_add(Musica* musica,);
// salvar musica no vetor de musica
// imprimir uma musica
void musica_mostrar(Musica musica);
void musica_destroy(Musica musica);
char *musica_salva_string(char *string_in);
float musica_salva_float(char *float_str);
int musica_salva_inteiro(char *inteiro_str);
// musica->artista_lista = musica_seta_artistas(musica, artists, id_artists);
char **musica_salva_artistas_str(char *artistas_str);
Musica musica_cria();
#endif