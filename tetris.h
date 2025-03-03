#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>

#define ROWS 16
#define COLS 8


typedef struct {
    int shape[4][4];  // Representação da peça (4x4)
} PecaTetris;

extern PecaTetris pecas[7];

void init_game();
void update_game();
void draw_board();
void print_piece(PecaTetris peca);

#endif
