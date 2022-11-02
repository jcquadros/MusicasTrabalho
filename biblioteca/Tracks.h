#ifndef _TRACKS_H_
#define _TRACKS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct track *Track;

FILE* TrackAbreArquivo();
Track TrackCria(Track); // aloca a track
void TrackLe(Track, FILE*); // le do arquivo
void TrackAdiciona(Track); // adicionar uma musica a um vetor de musicas, logo **
void TrackImprime(Track); //imprime uma track

#endif 