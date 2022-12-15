#include "Playlist.h"
#define ALOCAR 100

struct playlist
{
    char *nome;   // nome da playlist
    int *musicas; // listas de musicas da playlist
    int n_add;
    int n_alocados;
};

Playlist playlist_malloc() { return (Playlist)malloc(sizeof(struct playlist)); }
// aloca espaco para uma playlist
Playlist playlist_create()
{

    Playlist playlist = (Playlist)malloc(sizeof(struct playlist));
    playlist->nome = playlist_nome_create();
    playlist->n_alocados = ALOCAR;
    playlist->musicas = (int *)malloc(playlist->n_alocados * sizeof(int));
    playlist->n_add = 0;
    return playlist;
}
// cria um nome
char *playlist_nome_create()
{
    char nome_temp[200];
    printf("Digite o nome da nova playlist: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome_temp);
    setbuf(stdin, NULL);
    char *nome = strdup(nome_temp);
    return nome;
}
// funcoes auxiliares para recuperacao de valores internos da playlist
char *playlist_get_nome(Playlist playlist) { return playlist->nome; }
int playlist_get_n_musicas(Playlist playlist) { return playlist->n_add; }
int playlist_get_musica(Playlist playlist, int idx)
{
    return playlist->musicas[idx];
}
void playlist_print(Playlist playlist)
{
    printf("NOME: %s\n", playlist->nome);
    printf("MUSICAS: ");
    for (int i = 0; i < playlist->n_add; i++)
    {
        printf("[%d] ", playlist->musicas[i]);
    }
    printf("\n\n");
}
// adiciona uma musica na playlist
void playlist_add(Playlist playlist, int idx_musica)
{
    int musica_esta_contida = 0;
    // verifica se existe uma musica repetida
    for (int i = 0; i < playlist->n_add; i++)
    {
        if (playlist->musicas[i] == idx_musica)
        {
            musica_esta_contida = 1;
        }
    }

    if (!musica_esta_contida)
    {
        if (playlist->n_alocados == playlist->n_add)
        {
            playlist->n_alocados *= 2;
            playlist->musicas =
                (int *)realloc(playlist->musicas, playlist->n_alocados * sizeof(int));
        }
        playlist->musicas[playlist->n_add] = idx_musica;
        playlist->n_add++;
    }
    else
    {
        printf("Essa musica já foi adicionada à playlist! Escolha outra!\n");
    }
}
// desaloca a plalist
void playlist_destroy(Playlist playlist)
{
    free(playlist->nome);
    free(playlist->musicas);
    free(playlist);
}

void playlist_write_bin(FILE *f, Playlist playlist)
{
    int n = strlen(playlist->nome) + 1; // nome + \0
    fwrite(&n, 1, sizeof(int), f);
    fwrite(playlist->nome, n, sizeof(char), f);
    fwrite(&playlist->n_add, 1, sizeof(int), f);
    fwrite(playlist->musicas, playlist->n_add, sizeof(int), f);
}

Playlist playlist_read_bin(FILE *f, Playlist playlist)
{
    int n = 0; // tamanho
    fread(&n, 1, sizeof(int), f);
    playlist->nome = (char *)calloc(n, sizeof(char));
    fread(playlist->nome, n, sizeof(char), f);
    fread(&playlist->n_add, 1, sizeof(int), f);
    playlist->n_alocados = playlist->n_add;
    playlist->musicas = (int *)calloc(playlist->n_alocados, sizeof(int));
    fread(playlist->musicas, playlist->n_add, sizeof(int), f);
    return playlist;
}

FILE *playlist_abre_arquivo()
{
    FILE *f = fopen("bin/playlists.bin", "r");
    if (f == NULL)
    {
        printf("Nao foi possivel abrir o arquivo de playlists\n");
    }
    return f;
}