#include "tetris.h"

static int board[ROWS][COLS]; // x eh coluna(direita e esquerda), y eh linha(cima e baixo)

PecaTetris pecas[7] = {

    // Peça "T"
    {{{1, 1, 1, 0},
      {0, 1, 0, 0}},
     0},

    // Peça "Z"
    {{{1, 1, 0, 0},
      {0, 1, 1, 0}},
     0},

    // Peça "I"
    {{{0, 0, 0, 0},
      {1, 1, 1, 1}},
     0},

    // Peça "L"
    {{{1, 1, 1, 0},
      {1, 0, 0, 0}},
     0},

    // Peça "J"
    {{{1, 1, 1, 0},
      {0, 0, 1, 0}},
     0},

    // Peça "S"
    {{{0, 1, 1, 0},
      {1, 1, 0, 0}},
     0},

    // Peça "O"
    {{{1, 1, 0, 0},
      {1, 1, 0, 0}},
     0}};

void init_game()
{
    printf("Iniciando Tetris...\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = 0;
        }
    }
}

void draw_board()
{
    printf("Tabuleiro:\n    1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < ROWS; i++)
    {
        if (i < 9)
        {
            printf("%d - ", i + 1);
        }
        else
        {
            printf("%d -", i + 1);
        }

        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 1)
            {
                printf("█ "); // Bloco preenchido
            }
            else if (board[i][j] == 0)
            {
                printf(". "); // Espaço vazio
            }
            else if (board[i][j] == 2)
            {
                printf("[]"); // Espaço Ja preenchido e fixo
            }
        }
        printf("\n");
    }
}

void print_piece(PecaTetris peca) // Funcao de teste das pecas
{
    printf("Peça:\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", peca.shape[i][j]);
        }
        printf("\n");
    }
}

void place_piece(int linha, int coluna, PecaTetris peca)
{
    if (peca.sentido == 0) // Horizontal
    {
        for (int i = 0; i < 2; i++) // responsavel pela peca sentido linha
        {
            for (int j = 0; j < 4; j++) // responsavel pela peca sentido coluna
            {
                if (peca.shape[i][j] == 1)
                {
                    int board_linha = linha + i;
                    int board_coluna = coluna + j;

                    // Verifica se está dentro dos limites do tabuleiro
                    if (board_linha >= 0 && board_linha < ROWS && board_coluna >= 0 && board_coluna < COLS)
                    {
                        board[board_linha][board_coluna] = 1;
                    }
                }
            }
        }
    }
    else if (peca.sentido == 1) // Vertical
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (peca.shape[i][j] == 1)
                {
                    int board_linha = linha + j;
                    int board_coluna = coluna + i;

                    // Verifica se está dentro dos limites do tabuleiro
                    if (board_linha >= 0 && board_linha < ROWS && board_coluna >= 0 && board_coluna < COLS)
                    {
                        board[board_linha][board_coluna] = 1;
                    }
                }
            }
        }
    }
}

void remove_piece(int linha, int coluna, PecaTetris peca)
{
    if (peca.sentido == 0) // Horizontal
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (peca.shape[i][j] == 1)
                {
                    int board_linha = linha + i;
                    int board_coluna = coluna + j;

                    // Verifica se está dentro dos limites do tabuleiro
                    if (board_linha >= 0 && board_linha < ROWS && board_coluna >= 0 && board_coluna < COLS)
                    {
                        board[board_linha][board_coluna] = 0;
                    }
                }
            }
        }
    }
    else if (peca.sentido == 1) // Vertical
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (peca.shape[i][j] == 1)
                {
                    int board_linha = linha + j;
                    int board_coluna = coluna + i;

                    // Verifica se está dentro dos limites do tabuleiro
                    if (board_linha >= 0 && board_linha < ROWS && board_coluna >= 0 && board_coluna < COLS)
                    {
                        board[board_linha][board_coluna] = 0;
                    }
                }
            }
        }
    }
}

int can_move(int linha, int coluna, PecaTetris peca)
{
    if (peca.sentido == 0) // Horizontal
    {

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (peca.shape[i][j] == 1)
                {
                    int board_linha = linha + i;
                    int board_coluna = coluna + j;

                    // Verifica se está dentro dos limites do tabuleiro
                    if (board_linha < 0 || board_linha >= ROWS || board_coluna < 0 || board_coluna >= COLS)
                    {
#ifdef DEBUG
                        printf("\nMovimento Invalido\n");
#endif
                        return 0; // Movimento inválido
                    }

                    // Verifica se a posição está ocupada
                    if (board[board_linha][board_coluna] == 2)
                    {
#ifdef DEBUG
                        printf("\nMovimento Invalido\n");
#endif
                        return 0; // Movimento inválido
                    }
                }
            }
        }
    }

    else if (peca.sentido == 1) // Vertical
    {

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (peca.shape[i][j] == 1)
                {
                    int board_linha = linha + j;
                    int board_coluna = coluna + i;

                    // Verifica se está dentro dos limites do tabuleiro
                    if (board_linha < 0 || board_linha >= ROWS || board_coluna < 0 || board_coluna >= COLS)
                    {
#ifdef DEBUG
                        printf("\nMovimento Invalido\n");
#endif
                        return 0; // Movimento inválido
                    }

                    // Verifica se a posição está ocupada
                    if (board[board_linha][board_coluna] == 2)
                    {
#ifdef DEBUG
                        printf("\nMovimento Invalido\n");
#endif
                        return 0; // Movimento inválido
                    }
                }
            }
        }
    }

    return 1; // Movimento válido
}

void move_piece_right(int *linha, int *coluna, PecaTetris peca)
{
    int new_linha = *linha + 0;
    int new_coluna = *coluna + 1;

    if (can_move(new_linha, new_coluna, peca))
    {
        // Apaga a peça da posição atual
        remove_piece(*linha, *coluna, peca);

        // Atualiza posição
        *linha = new_linha;
        *coluna = new_coluna;

        // Coloca a peça na nova posição
        place_piece(*linha, *coluna, peca);
    }
}

void move_piece_left(int *linha, int *coluna, PecaTetris peca)
{
    int new_linha = *linha + 0;
    int new_coluna = *coluna - 1;

    if (can_move(new_linha, new_coluna, peca))
    {
        // Apaga a peça da posição atual
        remove_piece(*linha, *coluna, peca);

        // Atualiza posição
        *linha = new_linha;
        *coluna = new_coluna;

        // Coloca a peça na nova posição
        place_piece(*linha, *coluna, peca);
    }
}