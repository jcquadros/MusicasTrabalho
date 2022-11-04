#include <stdio.h>
#include <stdlib.h>
#include "tads/Musica.h"
#include "tads/Vector.h"

int main(int argc, char **argv)
{

	FILE *file = musica_abre_arquivo(argc, argv);
	Vector vetor_musica = vector_create(MUSICA);
	size_t retorno = 1;
    while (1)
    {
		// cria uma musica
		Musica musica = musica_create();

		// le os dados de uma musica
		retorno = musica_read(file, musica);
		// para a execucao assim que o arquivo acabar

		if (retorno == EOF){
			free(musica);
			break;
		}


		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_musica, musica);

    }
	// int len = vector_size(vetor_musica);
	// teste de exibicao de musica
	// for(int i=0; i<len; i++){
	// 	musica_print(vector_get(vetor_musica, i));
	// }
	vector_destroy(vetor_musica);
	fclose(file);
	return 0;
}
