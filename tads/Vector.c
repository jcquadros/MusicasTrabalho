#include "Vector.h"
#include "Artista.h"
#include "Musica.h"
#include "Playlist.h"
#include <math.h>

struct vector
{
  VectorType *data; // dados armazenados
  int tipo;         // tipo de dados armazenados em data
  int n_alocados;   // numero de alocados
  int n_add;        // numero de adicionados
};

/*FUNCOES GERAIS*/
Vector inicializa_artista(FILE *file_artistas)
{
  printf("Lendo artistas...\n");
  char *linha = NULL;
  size_t len = 0;
  Artista artista;
  Vector vetor_artista = vector_create(ARTISTA);
  // leitura
  while (getline(&linha, &len, file_artistas) != EOF)
  {
    artista = artista_create();         // alocacao
    artista_tok(artista, linha);        // separacao da string e inserção no artista
    vector_add(vetor_artista, artista); // salvar no vetor
  }
  free(linha);
  fclose(file_artistas);
  return vetor_artista;
}
Vector inicializa_musica(FILE *file_musicas)
{
  printf("Lendo musicas...\n");
  char *linha = NULL;
  size_t len = 0;
  Musica musica;
  Vector vetor_musica = vector_create(MUSICA);
  // leitura
  while (getline(&linha, &len, file_musicas) != EOF)
  {
    musica = musica_create();         // alocacao
    musica_tok(musica, linha);        // separacao da string e inserção na musica
    vector_add(vetor_musica, musica); // salvar no vetor
  }
  free(linha);
  fclose(file_musicas);
  return vetor_musica;
}
// aloca espaco e inicializa vetor para musicas e artistas
Vector vector_create(enum type tipo)
{
  Vector v = (Vector)calloc(1, sizeof(struct vector));
  v->n_alocados = ALOCAR; // numero pardrao de alocagem inicial
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
int vector_size(Vector v) { return v->n_add; }

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
  }
  else if (v->tipo == PLAYLIST)
  {
    // destroi playlists
    for (int i = 0; i < size; i++)
    {
      playlist_destroy(v->data[i]);
    }
  }

  free(v->data);
  free(v);
}

/*------FUNCOES DE MUSICA------*/
// /*FUNCIONALIDADE DE BUSCA*/
// busca musicas chamado na main
void vector_buscar_musicas(Vector vetor_musica, Vector vetor_artista)
{
  char linha[100];
  int *lista_musicas = NULL, lista_tamanho = 0;
  printf("Busque por uma musica :");
  setbuf(stdin, NULL);
  scanf("%[^\n]", linha);
  setbuf(stdin, NULL);

  lista_tamanho = vector_busca_musicas(vetor_musica, linha, &lista_musicas);             // encontra os indices das musicas
  if (!lista_tamanho){
    printf("\nNenhuma musica foi encontrada!\n");
  }
  vector_print_lista_musicas(lista_musicas, lista_tamanho, vetor_musica, vetor_artista); // imprime a lista de musicas
}

// encontra o indice das musicas cujo nome tenha semelhanca com a frase buscada
int vector_busca_musicas(Vector vetor_musica, char *linha, int **lista_musicas)
{
  int i, musicas_add = 0, musicas_alocadas = ALOCAR;
  Musica musica_comparada;
  int tamanho = vector_size(vetor_musica);
  int *musicas_iguais = (int *)malloc(musicas_alocadas * sizeof(int));
  for (i = 0; i < tamanho; i++)
  {
    musica_comparada = vector_get(vetor_musica, i); // Pega uma música
    if (musica_compara(linha, musica_comparada))
    { // se o nome buscado estiver contido na musica comparada
      if (musicas_alocadas == musicas_add)
      {
        musicas_alocadas *= 2;
        musicas_iguais = (int *)realloc(musicas_iguais, musicas_alocadas * sizeof(int));
      }
      musicas_iguais[musicas_add] = i; // salvo seu indice na lista
      musicas_add++;
    }
  }

  *lista_musicas = musicas_iguais; // salva a lista de musicas
  return musicas_add;              // Esse é o tamanho da lista
}

// imprime todas as musicas contidas na lista
void vector_print_lista_musicas(int *lista_musicas, int lista_tamanho, Vector vetor_musica, Vector vetor_artista)
{

  Musica musica;
  int numero_artistas;
  for (int i = 0; i < lista_tamanho; i++)
  {
    musica = vector_get(vetor_musica, lista_musicas[i]);                                                        // recupero uma das musicas da lista
    numero_artistas = musica_get_n_artistas(musica);                                                            // quantidade de artistas
    printf("[%d] : %s | ID: %s | ARTISTAS:", lista_musicas[i], musica_get_nome(musica), musica_get_id(musica)); // imprime indice, id, titulo, nome_artistas

    // imprime os nomes dos artistas
    for (int j = 0; j < numero_artistas; j++)
    {
      printf(" [%s]", musica_get_nome_artista(musica, j));
    }
    printf("\n");
  }

  free(lista_musicas);
}

/*FUNCIONALIDADE DE LISTAR UMA MUSICA*/

// procura os indices dos artistas contidos dentro em uma musica
int *vector_cria_lista_artistas(VectorType musica, Vector artistas)
{
  char **lista_artistas = musica_get_lista_ids_artistas(musica); // recupera a lista de ids dos artistas armazenadas em musica
  int n_ids_artistas = musica_get_n_ids_artistas(musica);        // recupera a quantidade de artistas da musica
  int *idx_artistas = (int *)malloc(n_ids_artistas * sizeof(int));

  for (int i = 0; i < n_ids_artistas; i++)
  {
    // rastreia o id desse artista
    idx_artistas[i] = vector_find_id(artistas, lista_artistas[i]); // armazena a posicao de cada artista
  }
  return idx_artistas; // lista de indices de artistas de uma musica
}
// lista todos os atributos de uma musica e seus artistas
void vector_listar_musica(int idx_m, Vector vetor_musica, Vector vetor_artista)
{
  Musica musica = vector_get(vetor_musica, idx_m);
  Artista artista;
  musica_print(musica);
  int *lista_artistas = vector_cria_lista_artistas(musica, vetor_artista); // lista de indices dos artistas
  int numero_artistas = musica_get_n_artistas(musica);

  if (lista_artistas[0] != NAO_ENCONTRADO)
  { // se uma musica nao tiver artistas
    for (int i = 0; i < numero_artistas; i++)
    {
      printf("\nARTISTA: [%d]\n", i + 1);
      artista = vector_get(vetor_artista, lista_artistas[i]);
      artista_print(artista);
    }
    printf("\n");
    musica_abrir_spotify(musica);
  }
  else
  {
    printf("\nNao existem artistas para essa musica!\n");
  }

  free(lista_artistas);
}

// encontra a posicao de um determinado elemento na lista a partir do seu id
int vector_find_id(Vector v, char *id)
{
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
  return NAO_ENCONTRADO;
}

/*------FUNCOES DE PLAYLIST------*/
/*LISTAR VARIAS PLAYLISTS*/
void vector_lista_varias_playlists(Vector v)
{
  int size = vector_size(v);
  printf("Exibindo playlists:\n");
  Playlist playlist;
  for (int i = 0; i < size; i++)
  {
    playlist = vector_get(v, i);
    printf("    PLAYLIST [%d] : %s | NUMERO DE MUSICAs : %d\n", i, playlist_get_nome(playlist), playlist_get_n_musicas(playlist));
  }
}
/*LISTAR UMA PLAYLIST*/
void vector_listar_playlist(int idx_m, Vector vetor_musica, Vector vetor_playlist)
{
  Playlist playlist = vector_get(vetor_playlist, idx_m);
  printf("PLAYLIST [%d] : %s\nMUSICAS:\n", idx_m, playlist_get_nome(playlist));
  int numero_musicas_p = playlist_get_n_musicas(playlist);
  for (int i = 0; i < numero_musicas_p; i++)
  {
    printf("    [%s]\n", musica_get_nome(vector_get(vetor_musica, playlist_get_musica(playlist, i))));
  }
  printf("\n");
}

/*LEITURA E ARMAZENAMENTO DE PLAYLISTS EM BINARIO*/
Vector vector_read_playlists_bin()
{
  printf("Lendo playlists...\n");
  FILE *f = playlist_abre_arquivo();
  Vector vetor_playlist = vector_create(PLAYLIST);
  Playlist playlist;
  if (f != NULL)
  {
    int n; // tamanho do vetor_playlist
    fread(&n, 1, sizeof(int), f);
    vetor_playlist->data = realloc(vetor_playlist->data, n * sizeof(VectorType));
    vetor_playlist->n_alocados = n;
    for (int i = 0; i < n; i++)
    {
      playlist = playlist_malloc();
      playlist = playlist_read_bin(f, playlist);
      vector_add(vetor_playlist, playlist);
    }
    fclose(f);
  }
  return vetor_playlist;
}

void vector_write_playlists_bin(Vector vetor_playlists)
{
  FILE *f = fopen("bin/playlists.bin", "w");
  int size = vector_size(vetor_playlists);
  fwrite(&size, 1, sizeof(int), f); // grava o tamanho do vetor_playlists
  if (f != NULL)
  {
    for (int i = 0; i < size; i++)
    {
      playlist_write_bin(f, vetor_playlists->data[i]);
    }
  }
  fclose(f);
}

void vector_gerar_relatorio(Vector vetor_playlist, Vector vetor_artistas, Vector vetor_musicas)
{

  printf("Gerando Relatório...\n");
  Vector vetor_musicas_playlist = vector_create(MUSICA_SHARED);
  Vector vetor_artistas_playlist = vector_create(ARTISTA_SHARED);

  int playlist = 0, musica = 0, id, artista = 0, i, j, n_musicas_playlist, n_alocados_musicas = 50, n_alocados_artistas = 50, n_adicionados_musicas = 0, n_adicionados_artistas = 0;
  int *poteiro_artistas_lista = NULL;
  int *lista_qtd_musicas = (int *)calloc(n_alocados_musicas, sizeof(int));
  int *lista_qtd_artistas = (int *)calloc(n_alocados_musicas, sizeof(int));
  Musica musica1;
  Artista artista1;

  j = vector_size(vetor_playlist);

  // listando as musicas nas playlists e contando a quantidade de vezes que aparecem

  for (playlist = 0; playlist < j; playlist++)
  {
    n_musicas_playlist = playlist_get_n_musicas(vector_get(vetor_playlist, playlist));
    for (musica = 0; musica < n_musicas_playlist; musica++)
    {
      musica1 = vector_get(vetor_musicas, playlist_get_musica(vector_get(vetor_playlist, playlist), musica));
      id = -1;
      for (i = 0; i < vector_size(vetor_musicas_playlist); i++)
      {
        if (musica_compara_id(musica_get_id(musica1), vetor_musicas_playlist->data[i]) == 1)
        { // mudei
          id = i;
        }
      }
      if (id == -1)
      {
        vector_add(vetor_musicas_playlist, musica1);

        lista_qtd_musicas[n_adicionados_musicas] = 1;
        if (n_adicionados_musicas == n_alocados_musicas)
        {
          n_alocados_musicas *= 2;
          lista_qtd_musicas = (int *)realloc(lista_qtd_musicas, n_alocados_musicas * sizeof(int));
        }

        n_adicionados_musicas = n_adicionados_musicas + 1;
        // se não tiver no vetor qtd musicas
      }
      else
      {
        lista_qtd_musicas[id] = lista_qtd_musicas[id] + 1;
        // se já tiver no vetor qtd musicass
      }
    }
  }

  // listando os artistas nas playlists e contando a quantidade de vezes que aparecem
  for (playlist = 0; playlist < vector_size(vetor_playlist); playlist++)
  {
    n_musicas_playlist = playlist_get_n_musicas(vector_get(vetor_playlist, playlist));
    for (musica = 0; musica < n_musicas_playlist; musica++)
    {
      musica1 = vector_get(vetor_musicas, playlist_get_musica(vector_get(vetor_playlist, playlist), musica));
      free(poteiro_artistas_lista); // mudei
      poteiro_artistas_lista = vector_cria_lista_artistas(musica1, vetor_artistas);
      for (artista = 0; artista < musica_get_n_artistas(musica1); artista++)
      {
        artista1 = vector_get(vetor_artistas, poteiro_artistas_lista[artista]);
        id = -1;
        for (i = 0; i < vector_size(vetor_artistas_playlist); i++)
        {
          if (artista_compara(artista_get_nome(artista1), vetor_artistas_playlist->data[i]) == 1)
          {
            id = i;
          }
        }
        if (id == -1)
        {
          vector_add(vetor_artistas_playlist, artista1);
          lista_qtd_artistas[n_adicionados_artistas] = 1;
          if (n_adicionados_artistas == n_alocados_artistas)
          {
            n_alocados_artistas *= 2;
            lista_qtd_artistas = (int *)realloc(lista_qtd_artistas, n_alocados_artistas * sizeof(int));
          }
          n_adicionados_artistas = n_adicionados_artistas + 1;

          // se não tiver no vetor qtd artistas
        }
        else
        {
          lista_qtd_artistas[id] = lista_qtd_artistas[id] + 1;
          // se já tiver no vetor qtd artistas
        }
      }
    }
  }

  int aux;
  // Ordenar musicas

  for (i = 0; i < vector_size(vetor_musicas_playlist); i++)
  {
    for (j = i + 1; j < vector_size(vetor_musicas_playlist); j++)
    {
      if (lista_qtd_musicas[j] > lista_qtd_musicas[i])
      {
        aux = lista_qtd_musicas[j];
        lista_qtd_musicas[j] = lista_qtd_musicas[i];
        lista_qtd_musicas[i] = aux;
        musica1 = vetor_musicas_playlist->data[j];
        vetor_musicas_playlist->data[j] = vetor_musicas_playlist->data[i];
        vetor_musicas_playlist->data[i] = musica1;
      }
    }
  }

  // Ordenar artista

  for (i = 0; i < vector_size(vetor_artistas_playlist); i++)
  {
    for (j = i + 1; j < vector_size(vetor_artistas_playlist); j++)
    {
      if (lista_qtd_artistas[j] > lista_qtd_artistas[i])
      {
        aux = lista_qtd_artistas[j];
        lista_qtd_artistas[j] = lista_qtd_artistas[i];
        lista_qtd_artistas[i] = aux;
        artista1 = vetor_artistas_playlist->data[j];
        vetor_artistas_playlist->data[j] = vetor_artistas_playlist->data[i];
        vetor_artistas_playlist->data[i] = artista1;
      }
    }
  }

  FILE *pfile_musicas;
  FILE *pfile_artistas;

  pfile_musicas = fopen("musicas_playlist.txt", "w");
  pfile_artistas = fopen("artistas_playlist.txt", "w");

  // Escrever o arquivos txt musica

  for (musica = 0; musica < vector_size(vetor_musicas_playlist); musica++)
  {
    fprintf(pfile_musicas, "%d %s\n", lista_qtd_musicas[musica], musica_get_nome(vetor_musicas_playlist->data[musica]));
    printf("%d %s\n", lista_qtd_musicas[musica], musica_get_nome(vetor_musicas_playlist->data[musica]));
  }

  // Escrever o arquivo txt artista

  for (artista = 0; artista < vector_size(vetor_artistas_playlist); artista++)
  {
    fprintf(pfile_artistas, "%d %s\n", lista_qtd_artistas[artista], artista_get_nome(vetor_artistas_playlist->data[artista]));
  }

  fclose(pfile_musicas);
  fclose(pfile_artistas);

  // Destruir os vetores

  vector_destroy(vetor_musicas_playlist);
  vector_destroy(vetor_artistas_playlist);
  free(lista_qtd_artistas);
  free(lista_qtd_musicas);
  free(poteiro_artistas_lista);
}

void vector_indicacoes_musicas(Vector vetor_playlist, int idx_playlist, int n_musicas, Vector vetor_musicas)
{

  // Pegando a playlist a ser recomendada
  Playlist playlist = vector_get(vetor_playlist, idx_playlist);
  Vector vetor_musicas_playlist = vector_create(MUSICA_SHARED);
  int i = 0, n_musicas_playlist = 0, j = 0;
  float media_caracteristicas[8] = {0, 0, 0, 0, 0, 0, 0, 0}, soma_danceability = 0, soma_energy = 0, soma_mode = 0, soma_speechiness = 0, soma_acousticness = 0,
        soma_instrumentalness = 0, soma_liveness = 0, soma_valence = 0;
  Musica musica;
  float *distancia_euclidiana_musicas = (float *)calloc(vector_size(vetor_musicas), sizeof(float));
  int *indice_musicas = (int *)calloc(vector_size(vetor_musicas), sizeof(int));
  float soma_euclidiana = 0, raiz_soma_euclidiana = 0;

  n_musicas_playlist = playlist_get_n_musicas(playlist);

  printf("Calculando a media da playlist\n");
  // Calculando a media da playlist
  for (j = 0; j < n_musicas_playlist; j++)
  {
    musica = vector_get(vetor_musicas, playlist_get_musica(playlist, j));
    soma_danceability = soma_danceability + musica_get_danceability(musica);
    soma_energy = soma_energy + musica_get_energy(musica);
    soma_mode = soma_mode + musica_get_mode(musica);
    soma_speechiness = soma_speechiness + musica_get_spechiness(musica);
    soma_acousticness = soma_acousticness + musica_get_acousticness(musica);
    soma_instrumentalness = soma_instrumentalness + musica_get_instrumentalness(musica);
    soma_liveness = soma_liveness + musica_get_liveness(musica);
    soma_valence = soma_valence + musica_get_valence(musica);
  }

  media_caracteristicas[0] = soma_danceability / n_musicas_playlist;
  media_caracteristicas[1] = soma_energy / n_musicas_playlist;
  media_caracteristicas[2] = soma_mode / n_musicas_playlist;
  media_caracteristicas[3] = soma_speechiness / n_musicas_playlist;
  media_caracteristicas[4] = soma_acousticness / n_musicas_playlist;
  media_caracteristicas[5] = soma_instrumentalness / n_musicas_playlist;
  media_caracteristicas[6] = soma_liveness / n_musicas_playlist;
  media_caracteristicas[7] = soma_valence / n_musicas_playlist;

  printf("Calculando a distancia de cada musica\n");
  // Calculando a distancia de cada musica

  for (int i = 0; i < vector_size(vetor_musicas); i++)
  {
    musica = vector_get(vetor_musicas, i);
    vector_add(vetor_musicas_playlist, musica);
    soma_euclidiana = pow((musica_get_danceability(musica) - media_caracteristicas[0]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_energy(musica) - media_caracteristicas[1]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_mode(musica) - media_caracteristicas[2]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_spechiness(musica) - media_caracteristicas[3]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_acousticness(musica) - media_caracteristicas[4]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_instrumentalness(musica) - media_caracteristicas[5]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_liveness(musica) - media_caracteristicas[6]), 2);
    soma_euclidiana = soma_euclidiana + pow((musica_get_valence(musica) - media_caracteristicas[7]), 2);
    raiz_soma_euclidiana = sqrt(soma_euclidiana);
    distancia_euclidiana_musicas[i] = raiz_soma_euclidiana;
    indice_musicas[i] = i;
  }

  printf("Ordenando as musicas por similaridade\n");
  // Ordenando

  double aux;
  int indice;

  for (i = 0; i < n_musicas; i++)
  {
    for (j = i + 1; j < vector_size(vetor_musicas); j++)
    {
      if (distancia_euclidiana_musicas[j] < distancia_euclidiana_musicas[i])
      {
        aux = distancia_euclidiana_musicas[j];
        distancia_euclidiana_musicas[j] = distancia_euclidiana_musicas[i];
        distancia_euclidiana_musicas[i] = aux;
        musica = vetor_musicas_playlist->data[j];
        vetor_musicas_playlist->data[j] = vetor_musicas_playlist->data[i];
        vetor_musicas_playlist->data[i] = musica;
        indice = indice_musicas[j];
        indice_musicas[j] = indice_musicas[i];
        indice_musicas[i] = indice;
      }
    }
  }

  // printando as musicas mais parecidas

  int numero_artistas = 0;

  for (i = 0; i < n_musicas; i++)
  {
    musica = vector_get(vetor_musicas_playlist, i);
    numero_artistas = musica_get_n_artistas(musica); // quantidade de artistas
    printf("[%d] : %s | ID: %s | ARTISTAS:", indice_musicas[i],
           musica_get_nome(musica), musica_get_id(musica)); // imprime indice, id, titulo, nome_artistas
    // imprime os nomes dos artistas
    for (int j = 0; j < numero_artistas; j++)
    {
      printf(" [%s]", musica_get_nome_artista(musica, j));
    }
    printf("\n");
  }

  vector_destroy(vetor_musicas_playlist);
  free(distancia_euclidiana_musicas);
  free(indice_musicas);
}