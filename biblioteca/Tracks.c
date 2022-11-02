#include "Tracks.h"

int n_alocados = 100; // numero inicial de tracks alocadas
const int n_data = 11; // total de caracteres + \0 

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

void TrackLe(Track track , FILE* file){
	//setlocale(LC_ALL,"Portuguese_Brazil");
    int maxl = 1000;
    char *line = malloc(maxl * sizeof(char));
    if(!line){
        printf("Memory not allocated!!\n");
        exit(EXIT_FAILURE);
    } 
	
	while (fgets(line, maxl, file)) {

        while(line[strlen(line) - 1] != '\n' && line[strlen(line) - 1] != '\r'){
            char *tmp = realloc (line, 2 * maxl * sizeof(char));

            fseek(file,0,SEEK_SET);          //or wherever you want to seek to
            if (tmp) {
                line = tmp;
                maxl *= 2;
                fgets(line, maxl, file);
            }
            else{
                printf("Not enough memory for this line!!\n");
                exit(EXIT_FAILURE);
            }
        }
        printf("%s",line);     //just to check
    }
 }


