#include "tetris.h"

static int board[ROWS][COLS];

PecaTetris pecas[7] = {
    // Peça "I"
    {{{0, 0, 0, 0}, 
      {1, 1, 1, 1}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}}},

    // Peça "O"
    {{{0, 0, 0, 0}, 
      {0, 1, 1, 0}, 
      {0, 1, 1, 0}, 
      {0, 0, 0, 0}}},

    // Peça "T"
    {{{0, 0, 0, 0}, 
      {1, 1, 1, 0}, 
      {0, 1, 0, 0}, 
      {0, 0, 0, 0}}},

    // Peça "L"
    {{{0, 0, 0, 0}, 
      {1, 1, 1, 0}, 
      {1, 0, 0, 0}, 
      {0, 0, 0, 0}}},

    // Peça "J"
    {{{0, 0, 0, 0}, 
      {1, 1, 1, 0}, 
      {0, 0, 1, 0}, 
      {0, 0, 0, 0}}},

    // Peça "S"
    {{{0, 0, 0, 0}, 
      {0, 1, 1, 0}, 
      {1, 1, 0, 0}, 
      {0, 0, 0, 0}}},

    // Peça "Z"
    {{{0, 0, 0, 0}, 
      {1, 1, 0, 0}, 
      {0, 1, 1, 0}, 
      {0, 0, 0, 0}}}
};


void init_game() {
    printf("Iniciando Tetris...\n");

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
}

void draw_board() {
    printf("Tabuleiro (%d x %d) \n", ROWS, COLS);
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
void print_piece(PecaTetris peca) {
    printf("Peça:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", peca.shape[i][j]);
        }
        printf("\n");
    }
}
