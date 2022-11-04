#include <stdio.h>
#include <stdlib.h>
#include "Musica.h"
#include "Vector.h"

int main(int argc, char **argv)
{	

	FILE *file = musica_abre_arquivo(argc, argv);
	Vector vetor_musica = vector_create();
	
	// Musica musica = musica_cria();

	// musicas_ler_full(file, musica);
	// musica_destroy(musica);

	size_t retorno = 1;
    while (retorno != EOF)
    { 
		// cria uma musica
		Musica musica = musica_cria();

		// le os dados do retangulo
		retorno = musica_ler(file, musica);

		// adiciona o retangulo no fim do vector
		vector_add(vetor_musica, musica);
		// vector_mostra
		// vector_destroy


    }


	fclose(file);
	return 0;
}
