#ifndef _VECTOR_H_
#define _VECTOR_H_
#define STR_IGUAIS 0
#define NAO_ENCONTRADO -1
#define ALOCAR 100
#include <stdio.h>
#include <stdlib.h>

typedef enum type
{
    MUSICA,
    ARTISTA,
    PLAYLIST,
    INT,
    FLOAT,
    CHAR,
    MUSICA_SHARED,
    ARTISTA_SHARED,
} Type;

typedef void *VectorType;

typedef struct vector *Vector;
/*FUNCOES GERAIS*/
// aloca espaco e inicializa um vector para musicas e artistas
Vector vector_create(enum type tipo);
Vector inicializa_artista(FILE *file_artistas);
Vector inicializa_musica(FILE *file_musicas);

// adiciona um elemento ao final de um vector
void vector_add(Vector v, VectorType elem);

// retorna o elemento da posicao idx do vector
VectorType vector_get(Vector v, int idx);

// recupera  o tamanho do vetor
int vector_size(Vector v);

// libera toda a memoria alocada em v
void vector_destroy(Vector v);

/*FUNCOES DE MUSICA e ARTISTA*/
/*FUNCIONALIDADE DE BUSCA*/
void vector_buscar_musicas(Vector vetor_musica, Vector vetor_artista); 
// busca musicas com titulo igual, as salva em uma lista e retorna o tamanho
int vector_busca_musicas(Vector vetor_musica,char *linha,int **lista_musicas);
void vector_print_lista_musicas(int *lista_musicas, int  lista_tamanho, Vector vetor_musica, Vector vetor_artista);
/*FUNCIONALIDADE DE LISTAR UMA MUSICA*/
int *vector_cria_lista_artistas(VectorType musica, Vector artistas);
void vector_listar_musica(int idx_m, Vector vetor_musica, Vector vetor_artista);
// encontra a posicao de determinado elemento da lista
int vector_find_id(Vector v, char *id);

/*------FUNCOES DE PLAYLIST------*/
/*LISTAR VARIAS PLAYLISTS*/
void vector_lista_varias_playlists(Vector v);
/*LISTAR UMA PLAYLIST*/
void vector_listar_playlist(int idx_m, Vector vetor_musica,Vector vetor_playlist);
Vector vector_read_playlists_bin(); // carrega o arquivo binario
void vector_write_playlists_bin(Vector vetor_playlists); // armazena as playlists em um arquivo binario

void vector_ordenar_artistas(Vector vetor_artistas, Vector vetor_qtd);

void vector_gerar_relatorio(Vector vetor_playlist, Vector vetor_artistas, Vector vetor_musicas);

void vector_indicacoes_musicas(Vector vetor_playlist, int idx_playlist, int n_musicas, Vector vetor_musicas);

#endif
