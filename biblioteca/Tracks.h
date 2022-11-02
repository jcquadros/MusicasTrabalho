#ifndef _TRACKS_H_
#define _TRACKS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALOC_INICIAL 1000
typedef struct track *Track;
typedef enum atributos Atributos;
void TrackLeEArmazena(Track track, FILE* file);
FILE* TrackAbreArquivo();
Track TrackCria(char* linha, size_t tamanho);
#endif 