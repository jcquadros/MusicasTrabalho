#include "Tracks.h"
typedef enum atributos{
	 	ID, NOME_DA_MUSICA, POPULARITY, DURACAO_MS, EXPLICT, ARTISTS, ID_ARTISTS, DATA_LANCAMENTO,
		DANCEABILITY, ENERGY, KEY, LOUNDNESS, MODE, SPECHINESS, ACOUSTINES, INSTRUMENTALNES,
		LIVENESS, VALENCE, TEMPO, TIME_ASSIGNATURE
};


struct track{
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

// Abre o arquivo de tracks ou finaliza o programa em caso de erro
FILE* TrackAbreArquivo(){
	FILE* f_tracks = fopen("data/tracks_5.csv", "r");
	
	if(f_tracks == NULL){
		printf("Erro ao abrir o arquivo de tracks\n");
		exit(EXIT_FAILURE);
	}
	
	return f_tracks;
}

void TrackLeEArmazena(Track track, FILE* file){

	size_t n_alocados = ALOC_INICIAL;
	char* linha = malloc(n_alocados * sizeof(char)); 
	size_t  tam ;
	
	//while(!feof(file)){
		tam = getline(&linha, &n_alocados, file); // le linha por linha
		printf("%s", linha);
		Track t= TrackCria(linha, tam);
		// cria track
		// adiciona track
	//}
	
	free(linha);
	free(track);
	fclose(file);
	
}
// A funcao divide a linha em partes que sao adicionadas ao struct de acordo com que eh quebrada com a funcao strtok
Track TrackCria(char* linha, size_t tamanho){ 
	Track track = (Track)calloc(1, sizeof(struct track)); // cria a track
	char * atributos;
    char* token;
 
  printf("%ld", tamanho);
	for(int seletor = 0; seletor < 20; seletor++){
		token = strtok_r(linha, ";", &linha);
		printf("i: %d token: %s\n",seletor, token);
		switch (seletor){
			case(ID):

			break;
			case(NOME_DA_MUSICA):
			break;
			case(POPULARITY):
			break;
			case(DURACAO_MS):
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



