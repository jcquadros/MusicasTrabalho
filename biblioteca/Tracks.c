#include "Musica.h"

enum{
	 	ID, NOME_DA_MUSICA, POPULARITY, DURACAO_MS, EXPLICT, ARTISTS, ID_ARTISTS, DATA_LANCAMENTO,
		DANCEABILITY, ENERGY, KEY, LOUNDNESS, MODE, SPECHINESS, ACOUSTINES, INSTRUMENTALNES,
		LIVENESS, VALENCE, TEMPO, TIME_ASSIGNATURE
}Musca_atributos;

// informacoes do tipo musica
struct musica{
	int id;
	char* nome_da_musica;
	int popularity;
	int duracao_ms;
	int explict;
	char** artists;
	char** id_artists;
	char* data_lancamento;
	float danceability;
	float energy; //
	int key;
	float loundness; 
	int mode; //
	float speechiness; //
	float acousticness; //
	float instrumentalness; //
	float liveness; //
	float valence; //
	float tempo;
	int time_assignature;
};

FILE* musica_abre_arquivo(int argc, char** argv){
    char dir[100];
	// verifica se o diretorio foi informado como argumento
    if(argc>1){
		sprintf(dir, "%s", argv[1]);	
	}else{
		printf("Diretorio nao informado!\n");
		exit(EXIT_FAILURE);
	}
    // verifica se o arquivo aberto eh valido
	FILE* file = fopen(dir, "r");

    if(file == NULL){
        printf("O diretorio de musica'%s' nao existe!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return file;
}
// ler arquivo de musica
size_t musica_ler(FILE* file, Musica musica){
    char* linha = NULL;
	size_t len = 0, retorno_get;
    // leitura de uma linha por vez ate o final do arquivo
	retorno_get = getline(&linha, &len, file);
	if(retorno_get == EOF){
        return(retorno_get);
    }
    printf("linha: %s", linha);
    musica_tok(musica, linha, len);
	return retorno_get;
}
// separar as musicas
void musica_tok(Musica musica, char* musica_str, size_t len){
	char * atributos;
    char* token;
	for(int seletor = 0; seletor < 20; seletor++){
		token = strtok_r(musica_str, ";", &musica_str);
        if(token == NULL){
            break;
        }
		printf("i: %d token: %s\n",seletor, token);
		switch (seletor){
			case(ID):
                // musica_salva_string(musica->id, token);
			break;
			case(NOME_DA_MUSICA):
                //musica_salva_string(musica->nome_da_musica, token);
			break;
			case(POPULARITY):
                //musica_salva_inteiro(musica->popularity, token);
			break;
			case(DURACAO_MS):
                //
			break;
			case(EXPLICT):
			break;
			case(ARTISTS):
			break;
			case(ID_ARTISTS):
			break;
			case(DATA_LANCAMENTO):
			break;
			case(DANCEABILITY):
			break;
			case(ENERGY):
			break;
			case(KEY):
			break;
			case(LOUNDNESS):
			break;
			case(MODE):
			break;
			case(SPECHINESS):
			break;
			case(ACOUSTINES):
			break;
			case(INSTRUMENTALNES):
			break;
			case(LIVENESS):
			break;
			case(VALENCE):
			break;
			case(TEMPO):
			break;
			case(TIME_ASSIGNATURE):
			break;
		}
		
	}
}
// alocar musica e retornar seu ponteiro
//struct vector musica_add(Musica* musica,);
// salvar musica no vetor de musica
// imprimir uma musica
void rect_mostrar(Musica musica);
void musica_destroy(Musica musica);
