#include <Artista.h>
#include <Menu.h>
#include <Musica.h>
#include <Playlist.h>
#include <Vector.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  // Abertura de arquivos
  FILE *file_artistas = artista_abre_arquivo(argc, argv);
  FILE *file_musicas = musica_abre_arquivo(argc, argv);

  // Gravacao dos dados
  Vector vetor_artista = inicializa_artista(file_artistas);
  Vector vetor_musica = inicializa_musica(file_musicas);
  Vector vetor_playlist = vector_read_playlists_bin();
  printf("Leitura de dados concluida\n");
  
  // Inicializacao de variaveis
  Playlist playlist;
  int seletor, idx_p, idx_m, loop = TRUE, k = 0;
  char linha[100];

  // PROGRAMA EM EXECUCAO
  while (loop)
  {
    imprime_menu();
    scanf("%s", linha); // uma forma de evitar que o programa quebre por causa de um erro do usuario
    seletor = atoi(linha);

    // Funcionalidades
    switch (seletor)
    {
    case (INVALIDO):
      printf("Opcao invalida! Por favor digite novamente sua escolha!\n");
      break;
    case (BUSCAR_MUSICA):
      vector_buscar_musicas(vetor_musica, vetor_artista);
      break;
    case (LISTAR_MUSICA):
      printf("Digite o índice da música a ser listada: ");
      scanf("%d", &idx_m);
      vector_listar_musica(idx_m, vetor_musica, vetor_artista); // lista todos os atributos da musica e dos artistas que a compoe
      break;
    case (CRIAR_PLAYLIST):
      playlist = playlist_create();         // cria uma playlist
      vector_add(vetor_playlist, playlist); // salva a playlist no vetor de playlists
      printf("\nPlaylist criada com sucesso!\n");
      break;
    case (LISTAR_PLAYLISTS):
      vector_lista_varias_playlists(vetor_playlist);
      break;
    case (LISTAR_UMA_PLAYLIST):
      printf("Digite o indice da playlist que deseja exibir: ");
      scanf("%d", &idx_p);
      vector_listar_playlist(idx_p, vetor_musica, vetor_playlist);
      break;
    case (ADICIONAR_MUSICA_PLAYLIST):
      printf("Digite o indice da musica a ser adicionada: ");
      scanf("%d", &idx_m);
      printf("Digite o indice da playlist que deseja adicionar a musica selecionada: ");
      scanf("%d", &idx_p);
      playlist = vector_get(vetor_playlist, idx_p); // recupera a playlist que sera alterada
      playlist_add(playlist, idx_m);                // adiciona a musica na playlist
      break;
    case (RECOMENDAR_MUSICA):
      printf("Digite o indice da playlist a ser recomendada: ");
      scanf("%d", &idx_p);
      printf("Digite o numero de músicas: ");
      scanf("%d", &k);
      vector_indicacoes_musicas(vetor_playlist, idx_p, k, vetor_musica);
      break;
    case (GERAR_RELATORIO):
      vector_gerar_relatorio(vetor_playlist, vetor_artista, vetor_musica);
      break;
    case (SAIR):
      printf("Salvando playlists e saindo...\n");
      vector_write_playlists_bin(vetor_playlist);
      loop = FALSE; // quebra o loop
      continue;
    default:
      printf("Opcao invalida! Por favor digite novamente sua escolha!\n");
      break;
    }
    tela_espera();
  }
  vector_destroy(vetor_playlist);
  vector_destroy(vetor_artista);
  vector_destroy(vetor_musica);
  return 0;
}
