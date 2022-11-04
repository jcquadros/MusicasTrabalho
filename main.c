#include <stdio.h>
#include <stdlib.h>
#include "Musica.h"

int main(int argc, char **argv)
{	printf("Abriu\n");
	FILE *file = musica_abre_arquivo(argc, argv);
		printf("Abriu\n");
	Musica musica = musica_cria();
		printf("Abriu\n");
	int i=0;
	while(musica_ler(file,musica+i)!=EOF){
	printf("Abriu\n");
			musica_mostrar(musica+i);

			i++;
	}

	for(int a = 0; a<i; a++){
		musica_destroy(musica+a);
	}

	free(musica);
	fclose(file);
	return 0;
}
