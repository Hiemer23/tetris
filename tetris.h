#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>

#define ROWS 16
#define COLS 8
#define DEBUG 1

typedef struct
{

    int shape[2][4]; // Representação da peça (2x4)
    int sentido;     // horizontal = 0, vertical = 1

} PecaTetris;

extern PecaTetris pecas[7];

void init_game();
void update_game();
void draw_board();
void print_piece(PecaTetris peca);
void place_piece(int linha, int coluna, PecaTetris peca);
void move_piece_right(int *linha, int *coluna, PecaTetris peca);
int can_move(int new_linha, int new_coluna, PecaTetris peca);
void move_piece_left(int *linha, int *coluna, PecaTetris peca);

#endif