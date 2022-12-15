#include "Musica.h"
#include <ctype.h>
enum
{
  ID,
  NOME_DA_MUSICA,
  POPULARITY,
  DURACAO_MS,
  EXPLICT,
  ARTISTS,
  ID_ARTISTS,
  DATA_LANCAMENTO,
  DANCEABILITY,
  ENERGY,
  KEY,
  LOUNDNESS,
  MODE,
  SPECHINESS,
  ACOUSTINES,
  INSTRUMENTALNES,
  LIVENESS,
  VALENCE,
  TEMPO,
  TIME_ASSIGNATURE
} Musca_atributos;

// informacoes do tipo musica
struct musica
{
  char *id;
  char *nome_da_musica;
  int popularity;
  int duracao_ms;
  int explict;
  int n_artistas;
  int n_id_artistas;
  char **artists;
  char **id_artists;
  char *data_lancamento;
  float danceability;
  float energy; //
  int key;
  float loundness;
  int mode;               //
  float speechiness;      //
  float acousticness;     //
  float instrumentalness; //
  float liveness;         //
  float valence;          //
  float tempo;
  int time_assignature;
};

FILE *musica_abre_arquivo(int argc, char **argv)
{
  char dir[100] = "data/tracks_full.csv";
  // verifica se o diretorio foi informado como argumento
  if (argc > 2)
  {
    sprintf(dir, "%s", argv[2]);
  }
  else
  {
    printf("Diretorio nao informado!\n");
    exit(EXIT_FAILURE);
  }
  // verifica se o arquivo aberto eh valido
  FILE *file = fopen(dir, "r");

  if (file == NULL)
  {
    printf("O diretorio de musica'%s' nao existe!\n", argv[2]);
    exit(EXIT_FAILURE);
  }
  // descarta a primeira linha do arquivo
  char *linha = NULL;
  size_t len = 0;
  // leitura de uma linha por vez ate o final do arquivo
  getline(&linha, &len, file);
  free(linha);

  return file;
}

Musica musica_create() { return (Musica)calloc(1, sizeof(struct musica)); }

size_t musica_read(FILE *file, Musica musica)
{
  char *linha = NULL;
  size_t len = 0, retorno_get;
  // leitura de uma linha por vez ate o final do arquivo
  retorno_get = getline(&linha, &len, file);
  if (retorno_get == EOF)
  {
    free(musica);
    free(linha);
    return (retorno_get);
  }
  // printf("linha: %s", linha);
  musica_tok(musica, linha); // quebra a string lida e salva no TAD Musica
  free(linha);
  return retorno_get;
}

// separar as musicas
void musica_tok(Musica musica, char *musica_str)
{
  char *token = strsep(&musica_str, ";");
  ;
  for (int seletor = 0; token != NULL; seletor++)
  {
    switch (seletor)
    {
    case (ID):
      musica->id = musica_salva_string(token);
      break;
    case (NOME_DA_MUSICA):
      musica->nome_da_musica = musica_salva_string(token);
      break;
    case (POPULARITY):
      musica->popularity = musica_salva_inteiro(token);
      break;
    case (DURACAO_MS):
      musica->duracao_ms = musica_salva_inteiro(token);
      break;
    case (EXPLICT):
      musica->explict = musica_salva_inteiro(token);
      break;
    case (ARTISTS):
      musica->artists = musica_salva_artistas(token, &musica->n_artistas);
      break;
    case (ID_ARTISTS):
      musica->id_artists = musica_salva_artistas(token, &musica->n_id_artistas);
      break;
    case (DATA_LANCAMENTO):
      musica->data_lancamento = musica_salva_string(token);
      break;
    case (DANCEABILITY):
      musica->danceability = musica_salva_float(token);
      break;
    case (ENERGY):
      musica->energy = musica_salva_float(token);
      break;
    case (KEY):
      musica->key = musica_salva_inteiro(token);
      break;
    case (LOUNDNESS):
      musica->loundness = musica_salva_float(token);
      break;
    case (MODE):
      musica->mode = musica_salva_inteiro(token);
      break;
    case (SPECHINESS):
      musica->speechiness = musica_salva_float(token);
      break;
    case (ACOUSTINES):
      musica->acousticness = musica_salva_float(token);
      break;
    case (INSTRUMENTALNES):
      musica->instrumentalness = musica_salva_float(token);
      break;
    case (LIVENESS):
      musica->liveness = musica_salva_float(token);
      break;
    case (VALENCE):
      musica->valence = musica_salva_float(token);
      break;
    case (TEMPO):
      musica->tempo = musica_salva_float(token);
      break;
    case (TIME_ASSIGNATURE):
      musica->time_assignature = musica_salva_inteiro(token);
      break;
    }
    token = strsep(&musica_str, ";");
  }
}

// imprimir uma musica
void musica_print(Musica musica)
{
  printf("NOME: %s\n", musica_get_nome(musica));
  printf("ID: %s\n", musica_get_id(musica));
  printf("POPULARIDADE: %d\n", musica_get_popularidade(musica));
  printf("DURACAO MS: %d\n", musica_get_duracao(musica));
  printf("EXPLICT: %d\n", musica_get_explict(musica));
  printf("DATA DE LANCAMENTO: %s\n", musica_get_data_lancamento(musica));
  printf("DANCEABILITY: %.2f\n", musica_get_danceability(musica));
  printf("ENERGY: %.2f\n", musica_get_energy(musica));
  printf("KEY: %d\n", musica_get_key(musica));
  printf("LOUNDNESS: %.2f\n", musica_get_loundness(musica));
  printf("MODE: %d\n", musica_get_mode(musica));
  printf("SPECHINESS: %.2f\n", musica_get_spechiness(musica));
  printf("INSTRUMENTALNESS: %.2f\n", musica_get_instrumentalness(musica));
  printf("LIVENESS: %.2f\n", musica_get_liveness(musica));
  printf("TEMPO: %.2f\n", musica_get_tempo(musica));
  printf("TIME ASSIGNATURE: %d\n", musica_get_time_assignature(musica));
}

/*Insercao de informacoes no struct*/
// separa a lista de artistas a cada pipeline
char **musica_salva_artistas(char *artistas_str, int *artistas_len)
{
  int n_alocados = ALOCAR, n_add = 0;
  char **artistas_lista = (char **)malloc(n_alocados * sizeof(char *));
  char *token = strsep(&artistas_str, "|");
  // recebe uma string de artistas e separa a cada pipeline
  for (n_add = 0; token != NULL; n_add++)
  {
    if (n_add == n_alocados)
    {
      n_alocados *= 2;
      artistas_lista = realloc(artistas_lista, sizeof(char *) * n_alocados);
    }
    artistas_lista[n_add] = strdup(token); // salva o artista na lista
    token = strsep(&artistas_str, "|");
  }
  *artistas_len = n_add;
  return artistas_lista;
}
char *musica_salva_string(char *string_in)
{
  char *string_out = strdup(string_in); // copia as informacoes de uma string para outra
  return string_out;     // retorna seu ponteiro
}
float musica_salva_float(char *float_str)
{
  return atof(float_str); // converte para float
}
int musica_salva_inteiro(char *inteiro_str)
{
  return atoi(inteiro_str); // converte para inteiro
}

// recupera atributos de musica de orma individual
char *musica_get_nome(Musica musica) { return musica->nome_da_musica; }
int musica_get_popularidade(Musica musica) { return musica->popularity; }
int musica_get_duracao(Musica musica) { return musica->duracao_ms; }
int musica_get_explict(Musica musica) { return musica->explict; }
char *musica_get_data_lancamento(Musica musica){return musica->data_lancamento;}
float musica_get_danceability(Musica musica) { return musica->danceability; }
float musica_get_energy(Musica musica) { return musica->energy; }
int musica_get_key(Musica musica) { return musica->key; }
float musica_get_loundness(Musica musica) { return musica->loundness; }
int musica_get_mode(Musica musica) { return musica->mode; }
float musica_get_spechiness(Musica musica) { return musica->speechiness; }
float musica_get_instrumentalness(Musica musica){return musica->instrumentalness;}
float musica_get_valence(Musica musica){return musica->valence;}
float musica_get_acousticness(Musica musica){return musica->acousticness;}
float musica_get_liveness(Musica musica) { return musica->liveness; }
float musica_get_tempo(Musica musica) { return musica->tempo; }
int musica_get_time_assignature(Musica musica){return musica->time_assignature;}
char *musica_get_id(Musica musica) { return musica->id; }                          // recupera o id da musica
char **musica_get_lista_ids_artistas(Musica musica) { return musica->id_artists; } // recupera a lista com todos os ids dos artistas da musica
char *musica_get_nome_artista(Musica musica, int idx){return musica->artists[idx]; } // recupera o nome de um artista
int musica_get_n_artistas(Musica musica) { return musica->n_artistas; }     // recupera a quantidade de artistas da musica
int musica_get_n_ids_artistas(Musica musica) { return musica->n_artistas; } // recupera a quantidade de ids de artistas da musica

/*FUNCIONALIDADE BUSCAR MUSICA*/
// compara uma string com o nome de uma musica
int musica_compara(char *str_musica, Musica musica)
{
  char *retorno, *musica_comparada = strdup(musica_get_nome(musica));

  // transforma ambas as strings em minusculo
  musica_comparada = musica_transforma_minusculo(musica_comparada);
  str_musica = musica_transforma_minusculo(str_musica);
  retorno = strstr(musica_comparada, str_musica); // compara
  free(musica_comparada);

  if (retorno != NULL)
  {
    return ENCONTROU; // encontrou semelhanca
  }
  else
  {
    return NAO_ENCONTROU; // nao encontrou semelhanca
  }
}
// compara id de uma musica com uma string
int musica_compara_id(char *str_musica, Musica musica)
{
  char *retorno, *musica_comparada = strdup(musica_get_id(musica));
  retorno = strstr(musica_comparada, str_musica); // compara
  free(musica_comparada);

  if (retorno != NULL)
  {
    return ENCONTROU; // encontrou semelhanca
  }
  else
  {
    return NAO_ENCONTROU; // nao encontrou semelhanca
  }
}
// transforma todos os caracteres de uma string em minusculo
char *musica_transforma_minusculo(char *str)
{
  for (int i = 0; str[i]; i++)
  {
    str[i] = tolower(str[i]);
  }
  return str;
}
// realiza uma chamada para a abertura do navegador no linux
void musica_abrir_spotify(Musica musica)
{
  char escolha;
  printf("Abrir música no spotify ? [s] ");
  scanf("%*c%c", &escolha);

  if (escolha == 's')
  {
    char link[300];
    sprintf(link, "firefox https://open.spotify.com/track/%s",musica_get_id(musica));
    system(link);
  }
}
// desaloca uma musica
void musica_destroy(Musica musica)
{
  free(musica->id);
  for (int i = 0; i < musica->n_artistas; i++)
  {
    free(musica->artists[i]);
  }
  for (int i = 0; i < musica->n_id_artistas; i++)
  {
    free(musica->id_artists[i]);
  }
  free(musica->artists);
  free(musica->id_artists);
  free(musica->data_lancamento);
  free(musica->nome_da_musica);
  free(musica);
}