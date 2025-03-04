#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>

#define ROWS 16
#define COLS 8
#define DEBUG 1

typedef struct
{
    int shape[4][4]; // Matriz fixa 4x4 para todas as peças
} PecaTetris;

extern PecaTetris pecas[7];

// Para testes
void print_piece(PecaTetris peca);
void update_game();

// Funcoes do jogo
void init_game();
void draw_board();
void place_piece(int linha, int coluna, PecaTetris peca);
int gerar_peca_aleatoria();
int check_piece_at_bottom(int *linha, int *coluna, PecaTetris peca, int *peca_atual);
void fix_piece(int *linha, int *coluna, PecaTetris peca);
void generate_next_piece(int *linha, int *coluna, int *peca_atual);
void remove_full_lines();

// Funcao de movimento horizontal
void move_piece_right(int *linha, int *coluna, PecaTetris peca);
void move_piece_left(int *linha, int *coluna, PecaTetris peca);
int can_move(int new_linha, int new_coluna, PecaTetris peca);

// Funcao de rotacao
void rotate_piece_right(int linha, int coluna, PecaTetris *peca);
void rotate_piece_left(int linha, int coluna, PecaTetris *peca);
void rotate_piece(int linha, int coluna, int new_matriz[4][4], PecaTetris *peca);

// Funcao de movimento vertical
void move_piece_down(int *linha, int *coluna, PecaTetris peca);
#endif