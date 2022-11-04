#include "Musica.h"

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
};

FILE *musica_abre_arquivo(int argc, char **argv)
{
	char dir[100];
	// verifica se o diretorio foi informado como argumento
	if (argc > 1)
	{
		sprintf(dir, "%s", argv[1]);
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
		printf("O diretorio de musica'%s' nao existe!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

Musica musica_cria()
{
	return (Musica)calloc(900, sizeof(struct musica));// atencao
}

void musicas_ler_full(FILE *file, Musica musica)
{
	int i = 0;
	while (musica_ler(file, musica + i) != EOF)
	{
		musica_mostrar(musica + i);
		i++;
	}
}
size_t musica_ler(FILE *file, Musica musica)
{
	char *linha = NULL;
	size_t len = 0, retorno_get;
	// leitura de uma linha por vez ate o final do arquivo
	retorno_get = getline(&linha, &len, file);
	if (retorno_get == EOF)
	{
		free(linha);
		return (retorno_get);
	}
	// printf("linha: %s", linha);
	musica_tok(musica, linha, len); // quebra a string lida e salva no TAD Musica
	free(linha);
	return retorno_get;
}

// separar as musicas
void musica_tok(Musica musica, char *musica_str, size_t len)
{
	char *token = NULL;
	for (int seletor = 0; seletor < QTD_ATRIBUTOS_MUSICA; seletor++)
	{
		token = strsep(&musica_str, ";");
		// printf("i: %d token: %s\n",seletor, token);
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
			musica->artists = musica_salva_string(token);
			break;
		case (ID_ARTISTS):
			musica->id_artists = musica_salva_string(token);
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
	}
}

// imprimir uma musica
void musica_mostrar(Musica musica)
{
	printf("id: %s\n", musica->id);
	printf("nome: %s\n", musica->nome_da_musica);
	printf("pop: %d\n", musica->popularity);
	printf("duracao_ms: %d\n", musica->duracao_ms);
	printf("explict: %d\n", musica->explict);
	printf("artists: %s\n", musica->artists);
	printf("id_artists: %s\n", musica->id_artists);
	printf("data_lancamento: %s\n", musica->data_lancamento);
	printf("danceability: %f\n", musica->danceability);
	printf("energy: %f\n", musica->energy);
	printf("key: %d\n", musica->key);
	printf("loundness: %f\n", musica->loundness);
	printf("mode %d\n", musica->mode);
	printf("spechiness: %f\n", musica->speechiness);
	printf("acousticness: %f\n", musica->acousticness);
	printf("instrumentalness: %f\n", musica->instrumentalness);
	printf("livenes: %f\n", musica->liveness);
	printf("valenve: %f\n", musica->valence);
	printf("tempo: %f\n", musica->tempo);
	printf("time_assig %d\n", musica->time_assignature);
}
void musica_destroy(Musica musica)
{
	for (int i = 0; i < 900; i++)
	{
		musica_atributos_destroy(musica, i);
	}
	free(musica);
}
// destroi a posicao de uma musica
void musica_atributos_destroy(Musica musica, int idx)
{
	free((musica + idx)->id);
	free((musica + idx)->artists);
	free((musica + idx)->data_lancamento);
	free((musica + idx)->nome_da_musica);
	free((musica + idx)->id_artists);
}

/*Insercao de informacoes no struct*/
char *musica_salva_string(char *string_in)
{
	char *string_out = strdup(string_in);
	return string_out;
}
float musica_salva_float(char *float_str)
{
	return atof(float_str);
}
int musica_salva_inteiro(char *inteiro_str)
{
	return atoi(inteiro_str);
}
/* separa uma string a cada | em uma matriz dinamica - serve para organizar uma lista de
artistas ou seus ids a fim de encontra-los posteriormerte para o armazenamento no struct*/
/*char** musica_salva_artistas_str(char* artistas_str){
	char* token = artistas_str;
	char** artistas_out ; // alocar

	for(int i=0; token != NULL; i++) {
		strsep(&artistas_str, "|");
		artistas_out[i] = strdup(token);
		// realoca artistas
		puts(token);
		token = artistas_str;
	}
	return artistas_out;
}
*/