#ifndef _MUSICAS_H_
#define _MUSICAS_H_
/*Numeros magicos*/
#define ENCONTROU 1
#define NAO_ENCONTROU 0
#define ALOCAR 100
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

// separar as informacoes da musica em tokens e armazena no tipo musica
void musica_tok(Musica musica, char *musica_str);

// imprimir uma musica
void musica_print(Musica musica);



// salva atributos da musica
char **musica_salva_artistas(char *artistas_str, int *artistas_len);
char *musica_salva_string(char *string_in);
float musica_salva_float(char *float_str);
int musica_salva_inteiro(char *inteiro_str);
char *musica_get_id(Musica musica);
// funcao auxiliar para recuperacao dos valores a seguir
char **musica_get_lista_ids_artistas(Musica musica);
int musica_get_n_ids_artistas(Musica musica);
int musica_get_n_artistas(Musica musica);
char *musica_get_nome(Musica musica);
int musica_get_popularidade(Musica musica);
int musica_get_duracao(Musica musica);
int musica_get_explict(Musica musica);
char *musica_get_data_lancamento(Musica musica);
float musica_get_danceability(Musica musica);
float musica_get_energy(Musica musica);
int musica_get_key(Musica musica);
float musica_get_loundness(Musica musica);
int musica_get_mode(Musica musica);
float musica_get_spechiness(Musica musica);
float musica_get_instrumentalness(Musica musica);
float musica_get_liveness(Musica musica);
float musica_get_tempo(Musica musica);
int musica_get_time_assignature(Musica musica);
char* musica_get_nome_artista(Musica musica, int idx);
float musica_get_valence(Musica musica);
float musica_get_acousticness(Musica musica);
//compara uma música com uma string
int musica_compara(char *str_musica,Musica musica);
int musica_compara_id(char *str_musica, Musica musica);
char *musica_transforma_minusculo(char *str);
//abre uma musica no spotify
void musica_abrir_spotify(Musica musica);
// desaloca musica
void musica_destroy(Musica musica);
#endif
