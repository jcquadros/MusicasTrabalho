#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct playlist *Playlist;
Playlist playlist_malloc();
// aloca espaco para uma playlist e seu nome
Playlist playlist_create();
char *playlist_nome_create();
// imprime uma playlist
void playlist_print(Playlist playlist);
// adiciona uma musica na playlist
void playlist_add(Playlist playlist, int idx_musica);
// desaloca um aplaylist
void playlist_destroy(Playlist playlist);
// funcoes auxiliares para recuperacao de valores internos da playlist
char* playlist_get_nome(Playlist playlist);
int playlist_get_musica(Playlist playlist, int idx);
int playlist_get_n_musicas(Playlist playlist);
void playlist_write_bin(FILE *f, Playlist playlist);
Playlist playlist_read_bin(FILE *f, Playlist playlist);
FILE * playlist_abre_arquivo();
#endif