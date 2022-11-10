#include <stdio.h>
#include <stdlib.h>
#include <Musica.h>
#include <Vector.h>
#include <Artista.h>
#include <Menu.h>
Vector inicializa_artista(FILE *file_artistas){
	Vector vetor_artista = vector_create(ARTISTA);
	size_t retorno = 1;
	// INICIALIZA ARTISTAS
	while (feof(file_artistas))
	{
		// cria um artista
		Artista artista = artista_create();

		// le os dados de um artista
		retorno = artista_read(file_artistas, artista);
		
		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_artista, artista);
	}
	fclose(file_artistas);
	rerurn vetor_artista;
}

Vector inicializa_musica(FILE *file_musicas){
	Vector vetor_musica = vector_create(MUSICA);
	size_t retorno = 1;
	// INICIALIZA MUSICAS
	while (feof(file_musicas))
	{
		// cria uma musica
		Musica musica = musica_create();

		// le os dados de uma musica
		retorno = musica_read(file_musicas, musica);

		// adiciona o indice dos artistas participantes na composicao da musica
		musica_add_idx_artistas(musica, vector_cria_lista_artistas(musica, vetor_artista));

		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_musica, musica);
	}
	fclose(file_musicas);
	return vetor_musica;

}

int main(int argc, char **argv)
{
	// Abertura de arquivos
	FILE *file_artistas = artista_abre_arquivo(argc, argv);
	FILE *file_musicas = musica_abre_arquivo(argc, argv);
	// Gravacao dos dados
	Vector vector_artista = inicializa_artista(file_artistas);
	Vector vetor_musica = inicializa_musica(file_musicas);

	// Variaveis da parte principal do programa
	int seletor, loop = TRUE;
    	char linha[10];

	// PROGRAMA EM EXECUCAO
	while(loop){
		imprime_menu();
		scanf("%s", linha); // leitura em string para reduzir falhas no programa por causa erros do usuario
		seletor = atoi(linha);
		switch (seletor)
		{
		case (INVALIDO):
		    printf("Opcao invalida! Por favor digite novamente sua escolha!\n");
		    break;
		case (BUSCAR_MUSICA):
				// escaneia a musica
				// chama uma funcao
		    break;
		case (LISTAR_MUSICA):
		    break;
		case (CRIAR_PLAYLIST):
		    break;
		case (LISTAR_PLAYLISTS):
		    break;
		case (LISTAR_UMA_PLAYLIST):
		    break;
		case (ADICIONAR_MUSICA_PLAYLIST):
		    break;
		case (RECOMENDAR_MUSICA):
		    break;
		case (GERAR_RELATORIO):
		    break;
		case (SAIR):
		    loop = FALSE; // quebra o loop
		    continue;
		default:
		    printf("Opcao invalida! Por favor digite novamente sua escolha!\n");
		    break;
		}
		tela_espera();
    	}
	vector_destroy(vetor_artista);
	vector_destroy(vetor_musica);
	return 0;
}
