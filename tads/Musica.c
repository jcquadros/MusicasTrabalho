#include "Musica.h"
#include <ctype.h>
enum
{
	ID,
	NOME_DA_MUSICA,
	POPULARITY,
	DURACAO_MS,
	EXPLICT,
	ARTISTAS,
	ID_ARTISTAS,
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
	int popularity, duracao_ms, explict, n_artistas, key, mode, time_assignature;
	char **artistas;
	char **id_artistas;
	int *idx_artistas;
	char *data_lancamento;
	float danceability, energy, loundness, speechiness, acousticness,
		instrumentalness, liveness, valence, tempo;
};
// abre o arquivo de musica.csv 
FILE *musica_abre_arquivo(int argc, char **argv)
{
	char dir[100] = "data/tracks_2.csv";
	// verifica se o diretorio foi informado como argumento
	// if (argc > 1)
	// {
	// 	sprintf(dir, "%s", argv[1]);
	// }
	// else
	// {
	// 	printf("Diretorio nao informado!\n");
	// 	exit(EXIT_FAILURE);
	// }
	// verifica se o arquivo aberto eh valido
	FILE *file = fopen(dir, "r");

	if (file == NULL)
	{
		printf("O diretorio de musica'%s' nao existe!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

Musica musica_create()
{
	return (Musica)calloc(1, sizeof(struct musica));
}

size_t musica_read(FILE *file, Musica musica)
{
	char *linha = NULL;
	size_t len = 0, retorno_get;
	retorno_get = getline(&linha, &len, file); // le uma linha
	if (retorno_get == EOF)
	{
		free(musica);
		free(linha);
		return (retorno_get);
	}
	musica_tok(musica, linha); // separa a string linha e salva os dados da musica
	free(linha);
	return retorno_get;
}

// separa os atributos e os armazena em uma musica
void musica_tok(Musica musica, char *musica_str)
{
	char *token = strsep(&musica_str, ";");
	for (int seletor = 0; token!=NULL; seletor++)
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
		case (ARTISTAS):
			musica->artistas = musica_salva_artistas(token, &musica->n_artistas);
			break;
		case (ID_ARTISTAS):
			musica->id_artistas = musica_salva_artistas(token, &musica->n_artistas);
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
char *musica_salva_string(char *string_in)
{
	char *string_out = strdup(string_in); // copia as informacoes de uma string para outra
	return string_out;					  // retorna seu ponteiro
}
float musica_salva_float(char *float_str)
{
	return atof(float_str); // converte para float
}
int musica_salva_inteiro(char *inteiro_str)
{
	return atoi(inteiro_str); // converte para inteiro
}

// separa novamente a string de artistas a cada pipeline e salva seus valores
char **musica_salva_artistas(char *artistas_str, int *n_artistas)
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
	*n_artistas = n_add; // resgata o numero de artistas
	return artistas_lista;
}

Musica musica_add_idx_artistas(Musica musica, int *idx_artistas)
{
	musica->idx_artistas = idx_artistas; // salva os indices dos artistas
	return musica;
}

// recupera atributos de musica de orma individual
char *musica_get_nome(Musica musica)
{
	return musica->nome_da_musica;
}
int musica_get_popularidade(Musica musica)
{
	return musica->popularity;
}
int musica_get_duracao(Musica musica)
{
	return musica->duracao_ms;
}
int musica_get_explict(Musica musica)
{
	return musica->explict;
}
int *musica_get_indices(Musica musica)
{
	return musica->idx_artistas;
}
char *musica_get_data_lancamento(Musica musica)
{
	return musica->data_lancamento;
}
float musica_get_danceability(Musica musica)
{
	return musica->danceability;
}
float musica_get_energy(Musica musica)
{
	return musica->energy;
}
int musica_get_key(Musica musica)
{
	return musica->key;
}
float musica_get_loundness(Musica musica)
{
	return musica->loundness;
}
int musica_get_mode(Musica musica)
{
	return musica->mode;
}
float musica_get_spechiness(Musica musica)
{
	return musica->speechiness;
}
float musica_get_instrumentalness(Musica musica)
{
	return musica->instrumentalness;
}
float musica_get_liveness(Musica musica)
{
	return musica->liveness;
}
float musica_get_tempo(Musica musica)
{
	return musica->tempo;
}
int musica_get_time_assignature(Musica musica)
{
	return musica->time_assignature; 
}
char *musica_get_id(Musica musica)
{
	return musica->id; // recupera o id da musica
}
char **musica_get_lista_artistas(Musica musica)
{
	return musica->id_artistas; // recupera a lista de id dos artistas
}
int musica_get_n_artistas(Musica musica)
{
	return musica->n_artistas; // recupera a quantidade de artistas da lista
}


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
		return 1; // encontrou semelhanca
	}
	else
	{
		return 0; // nao encontrou semelhanca
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
// faz uma chamada de abertura do firefox 
void musica_abrir_spotify(Musica musica)
{
	char escolha;
	printf("Abrir música no spotify ? [s/n] ");
	scanf("%*c%c", &escolha);

	if (escolha == 's')
	{
		char link[300];
		sprintf(link, "firefox https://open.spotify.com/track/%s", musica_get_id(musica));
		system(link);
	}
}


// desaloca uma musica
void musica_destroy(Musica musica)
{
	free(musica->id);
	for (int i = 0; i < musica->n_artistas; i++)
	{
		free(musica->artistas[i]);
		free(musica->id_artistas[i]);
	}
	free(musica->artistas);
	free(musica->id_artistas);
	free(musica->idx_artistas);
	free(musica->data_lancamento);
	free(musica->nome_da_musica);
	free(musica);
}