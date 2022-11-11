#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
#include "Musica.h"
#include "Artista.h"
#include "Playlist.h"

struct vector
{
    VectorType *data; // dados armazenados
    int tipo;         // tipo de dados armazenados em data
    int n_alocados;   // numero de alocados
    int n_add;        // numero de adicionados
};

// aloca espaco e inicializa vetor para musicas e artistas
Vector vector_create(enum type tipo)
{
    Vector v = (Vector)calloc(1, sizeof(struct vector));
    v->n_alocados = 50;
    v->n_add = 0;
    v->tipo = tipo;
    v->data = (VectorType *)calloc(v->n_alocados, sizeof(VectorType));
    return v;
}

// adiciona um elemento ao final de um vector
void vector_add(Vector v, VectorType elem)
{
    if (v->n_add == v->n_alocados)
    {
        v->n_alocados *= 2;
        v->data = (VectorType *)realloc(v->data, v->n_alocados * sizeof(VectorType));
    }

    v->data[v->n_add] = elem; // armazena o elemento
    v->n_add++;
}

// retorna o elemento da posicao idx do vector
VectorType vector_get(Vector v, int idx)
{
    if (idx < 0 || idx >= v->n_add)
    {
        printf("Indice invalido '%d' para o vetor com tamanho '%d'.\n", idx, v->n_add);
        exit(1);
    }

    return v->data[idx];
}

// recupera o tamanho do vetor
int vector_size(Vector v)
{
    return v->n_add;
}

// encontra a posicao de um determinado elemento na lista
int vector_find_id(Vector v, char *id)
{
    char *item;
    int i;
    // encontrando um elemento do tipo artista pelo seu id
    if (v->tipo == ARTISTA)
    {
        Artista artista;
        for (i = 0; i < v->n_add; i++)
        {
            artista = vector_get(v, i);
            if (strcmp(id, artista_get_id(artista)) == STR_IGUAIS)
            { // se os ids forem iguais
                return i;
            }
        }
        // encontrando um elemento do tipo musica pelo seu id
    }
    else if (v->tipo == MUSICA)
    {
        Musica musica;
        for (i = 0; i < v->n_add; i++)
        {
            musica = vector_get(v, i);

            if (strcmp(id, musica_get_id(musica)) == STR_IGUAIS)
            { // se os ids forem iguais

                return i;
            }
        }
    }
    // caso nao seja encontrado nenhum elemento em comum retorna -1
    return -1;
}

// cria uma lista de indices dos artistas de uma musica
int *vector_cria_lista_artistas(VectorType musica, Vector artistas)
{
    char **lista_artistas = musica_get_lista_artistas(musica); // recupera a lista de ids dos artistas armazenadas em musica
    int n_artistas = musica_get_n_artistas(musica);            // recupera a quantidade de artistas da musica
    int *idx_artistas = (int *)malloc(n_artistas * sizeof(int));

    for (int i = 0; i < n_artistas; i++)
    {
        // rastreia o id desse artista
        idx_artistas[i] = vector_find_id(artistas, lista_artistas[i]); // armazena a posicao de cada artista
    }
    return idx_artistas;
}

// libera toda a memoria alocada em v
void vector_destroy(Vector v)
{
    int size = vector_size(v);
    if (v->tipo == MUSICA)
    {
        // destroi as musicas
        for (int i = 0; i < size; i++)
        {
            musica_destroy(v->data[i]);
        }
    }
    else if (v->tipo == ARTISTA)
    {
        // destroi os artistas
        for (int i = 0; i < size; i++)
        {
            artista_destroy(v->data[i]);
        }
    }else if(v->tipo == PLAYLIST){
        // destroi playlists
        for(int i=0; i< size; i++){
            playlist_destroy(v->data[i]);
        }
    }

    free(v->data);
    free(v);
}

void vector_print(Vector v){
    int size = vector_size(v);
    if(v->tipo == PLAYLIST){
        printf(">> Exibindo playlists:\n");
        Playlist playlist;
        for(int i=0; i<size; i++){  
            playlist = vector_get(v, i);
            printf("    PLAYLIST [%d] : %s | NUMERO DE MUSICAs : %d\n", i, playlist_get_nome(playlist), playlist_get_n_musicas(playlist));
        }
    }
}