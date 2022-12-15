#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef enum menu {
   INVALIDO, BUSCAR_MUSICA, LISTAR_MUSICA, CRIAR_PLAYLIST, LISTAR_PLAYLISTS, LISTAR_UMA_PLAYLIST, ADICIONAR_MUSICA_PLAYLIST, RECOMENDAR_MUSICA, GERAR_RELATORIO, SAIR

}Menu;

void imprime_menu();
void tela_espera();