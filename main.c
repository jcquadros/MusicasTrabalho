#include <stdio.h>
#include <stdlib.h>
#include "Musica.h"

int main(int argc, char** argv) {
	FILE* file = musica_abre_arquivo(argc, argv);
	Musica musica;
	while(musica_ler(file,musica)!=EOF){
	}
	return 0;
}
