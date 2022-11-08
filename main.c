#include <stdio.h>
#include <stdlib.h>
#include <Musica.h>
#include <Vector.h>
#include <Artista.h>

int main(int argc, char **argv)
{
	// Abertura de arquivos
	FILE *file_artistas = artista_abre_arquivo(argc, argv);
	FILE *file_musicas = musica_abre_arquivo(argc, argv);
	// Alocacao de memoria dos vetores
	Vector vetor_musica = vector_create(MUSICA);
	Vector vetor_artista = vector_create(ARTISTA);
	size_t retorno = 1; // indica o final do arquivo

	// INICIALIZA ARTISTA
    while (1)
    {
		// cria um artista
		Artista artista = artista_create();

		// le os dados de um artista
		retorno = artista_read(file_artistas,artista);

		// para a execucao assim que o arquivo acabar
		if (retorno == EOF){
			free(artista);
			break;
		}
		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_artista, artista);

    }
	fclose(file_artistas);


	// INICIALIZA MUSICAS
    while (1)
    {
		// cria uma musica
		Musica musica = musica_create();

		// le os dados de uma musica
		retorno = musica_read(file_musicas, musica);

		// para a execucao assim que o arquivo acabar
		if (retorno == EOF){
			free(musica);
			break;
		}
		// adiciona o indice dos artistas participantes na composicao da musica
		musica_add_idx_artistas(musica,vector_cria_lista_artistas(musica,vetor_artista));

		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_musica, musica);

    }
	fclose(file_musicas);

	vector_destroy(vetor_artista);
	vector_destroy(vetor_musica);
	return 0;
}
