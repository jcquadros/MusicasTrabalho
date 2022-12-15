#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

void imprime_menu(){
    printf("\n-------------------------------------------\n");
    printf("--------------------MENU-------------------\n");
    printf(">> 1 >> Buscar musica\n");
    printf(">> 2 >> Listar musica\n");
    printf(">> 3 >> Criar playlist\n");
    printf(">> 4 >> Listar playlists\n");
    printf(">> 5 >> Listar uma playlist\n");
    printf(">> 6 >> Adicionar uma musica na playlist\n");
    printf(">> 7 >> Recomendar musica\n");
    printf(">> 8 >> Gerar relatorio\n");
    printf(">> 9 >> Sair\n");
    printf("-------------------------------------------\n");
    printf("-------------------------------------------\n\n");
    printf(">>");


}
void tela_espera(){
    printf("Pressione qualquer tecla para continuar...");
    getchar();
    getchar();
}