#include "tetris.h"

int main()
{
    int linha = 1, coluna = 0; // Posição inicial da peça "T"
    pecas[2].sentido = 1;
    init_game();
    draw_board();

    printf("\nPosicionando a peça inicial...\n");
    place_piece(linha, coluna, pecas[2]);
    draw_board();

    printf("\nMovendo para a direita...\n");
    move_piece_right(&linha, &coluna, pecas[2]); // Move para direita
    draw_board();

    printf("\nMovendo para a direita...\n");
    move_piece_left(&linha, &coluna, pecas[2]); // Move para direita
    draw_board();

    printf("\nMovendo para a direita...\n");
    move_piece_left(&linha, &coluna, pecas[2]); // Move para direita
    draw_board();

    printf("\nMovendo para a direita...\n");
    move_piece_left(&linha, &coluna, pecas[2]); // Move para direita
    draw_board();

    printf("\nMovendo para a direita...\n");
    move_piece_right(&linha, &coluna, pecas[2]); // Move para direita
    draw_board();

    return 0;
}
