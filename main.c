#include <stdio.h>
#include <stdlib.h>
#include <Musica.h>
#include <Vector.h>
#include <Artista.h>

int main(int argc, char **argv)
{
	FILE *file = artista_abre_arquivo(argc, argv);
	Vector vetor_artista = vector_create(ARTISTA);
	size_t retorno = 1;

	// INICIALIZA ARTISTA
    while (1)
    {
		// cria um artista
		Artista artista = artista_create();

		// le os dados de um artista
		retorno = artista_read(file,artista);
		
		// para a execucao assim que o arquivo acabar	
		if (retorno == EOF){
			free(artista);
			break;
		}
		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_artista, artista);

    }
	fclose(file);
	
	file = musica_abre_arquivo(argc, argv);
	Vector vetor_musica = vector_create(MUSICA);
	
	// INICIALIZA MUSICAS
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
	int len = vector_size(vetor_musica);
	for (int i = 0; i < len; i++)
    {
		musica_print(vector_get(vetor_musica, i));
	}
	
	vector_destroy(vetor_artista);
	vector_destroy(vetor_musica);
	fclose(file);
	return 0;
}
