#include "Artista.h"

struct artista
{
    char *id;
    float seguidores;
    char *generos;
    char *nome_do_artista;
    int popularidade;
};

enum
{
    ID,
    SEGUIDORES,
    GENEROS,
    NOME_DO_ARTISTA,
    POPULARIDADE
} Artista_atributos;

FILE *artista_abre_arquivo(int argc, char **argv)
{
    char dir[100] = "data/artists_full.csv";
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
        printf("O diretorio de artistas '%s' nao existe!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return file;
}

Artista artista_create()
{
    return (Artista)calloc(1, sizeof(struct artista));
}

size_t artista_read(FILE *file, Artista artista)
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
    artista_tok(artista, linha); // quebra a string lida e salva no TAD Musica
    free(linha);
    return retorno_get;
}

void artista_tok(Artista artista, char *artista_str)
{
    char *token = NULL;
    for (int seletor = 0; seletor < QTD_ATRIBUTOS_ARTISTA; seletor++)
    {
        token = strsep(&artista_str, ";");
        // printf("i: %d token: %s\n",seletor, token);
        switch (seletor)
        {
        case (ID):
            artista->id = artista_salva_string(token);
            break;
        case (SEGUIDORES):
            artista->seguidores = artista_salva_float(token);
            break;
        case (GENEROS):
            artista->generos = artista_salva_string(token);
            break;
        case (NOME_DO_ARTISTA):
            artista->nome_do_artista = artista_salva_string(token);
            break;
        case (POPULARIDADE):
            artista->popularidade = artista_salva_inteiro(token);
            break;
        }
    }
}

char *artista_salva_string(char *string_in)
{
	char *string_out = strdup(string_in); // copia as informacoes de uma string para outra
	return string_out; // retorna seu ponteiro
}
float artista_salva_float(char *float_str)
{
	return atof(float_str); // converte para float
}
int artista_salva_inteiro(char *inteiro_str)
{
	return atoi(inteiro_str); // converte para inteiro
}



void artista_destroy(Artista artista)
{
	free(artista->id);
	free(artista->generos);
	free(artista->nome_do_artista);
	free(artista);
}
