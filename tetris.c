#include "tetris.h"

static int board[ROWS][COLS]; // x eh coluna(direita e esquerda), y eh linha(cima e baixo)

PecaTetris pecas[7] = {
    {// Peça "T"
     {
         {0, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}}},
    {// Peça "Z"
     {
         {0, 0, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}}},
    {// Peça "I"
     {
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}}},
    {// Peça "L"
     {
         {0, 0, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 1, 0}}},
    {// Peça "J"
     {
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}}},
    {// Peça "S"
     {
         {0, 0, 0, 0},
         {0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0}}},
    {// Peça "O"
     {
         {0, 0, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}}}};

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
    for (int i = 0; i < 4; i++)
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

    for (int i = 0; i < 4; i++) // responsavel pela peca sentido linha
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

void remove_piece(int linha, int coluna, PecaTetris peca)
{
    for (int i = 0; i < 4; i++)
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

int can_move(int linha, int coluna, PecaTetris peca)
{

    for (int i = 0; i < 4; i++)
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

void rotate_piece_right(int linha, int coluna, PecaTetris *peca)
{
    int nova_peca[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            nova_peca[j][3 - i] = peca->shape[i][j];
        }
    }
    rotate_piece(linha, coluna, nova_peca, peca);
}

void rotate_piece_left(int linha, int coluna, PecaTetris *peca)
{
    int nova_peca[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            nova_peca[3 - j][i] = peca->shape[i][j];
        }
    }
    rotate_piece(linha, coluna, nova_peca, peca);
}

void rotate_piece(int linha, int coluna, int new_matriz[4][4], PecaTetris *peca)
{

    PecaTetris pecaAux;
    // Cria uma cópia temporária para verificação
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            pecaAux.shape[i][j] = new_matriz[i][j];
        }
    }

    if (can_move(linha, coluna, pecaAux))
    {
        // Apaga a peça da posição atual
        remove_piece(linha, coluna, *peca);

        // Copia a matriz rotacionada para a peça original
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                peca->shape[i][j] = new_matriz[i][j];
            }
        }

        // Coloca a peça na nova posição
        place_piece(linha, coluna, *peca);
    }
}

void move_piece_down(int *linha, int *coluna, PecaTetris peca)
{
    int nova_linha = *linha + 1;

    // Verifica se a peça pode se mover para baixo (se a linha não está fora do tabuleiro e não há outra peça no caminho)
    if (can_move(nova_linha, *coluna, peca)) // A função can_move agora verifica se a nova posição é válida
    {
        // Apaga a peça da posição atual
        remove_piece(*linha, *coluna, peca);

        // Atualiza a posição da peça
        *linha = nova_linha;

        // Coloca a peça na nova posição
        place_piece(*linha, *coluna, peca);
    }
}

// Função para gerar uma peça aleatória
int gerar_peca_aleatoria()
{
    return rand() % 7; // Gera um número entre 0 e 6
}

int check_piece_at_bottom(int *linha, int *coluna, PecaTetris peca, int *peca_atual)
{

    // Verifique se há outra peça abaixo dela (posição da peça no tabuleiro)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (peca.shape[i][j] == 1)
            {
                if (board[*linha + i + 1][*coluna + j] == 2 || (*linha + i) >= 15) // Se houver uma peça fixa abaixo
                {
                    fix_piece(linha, coluna, peca);
                    generate_next_piece(linha, coluna, peca_atual);
                    return 1;
                }
            }
        }
    }

    return 0; // A peça não atingiu o fundo
}

void generate_next_piece(int *linha, int *coluna, int *peca_atual)
{
    *peca_atual = gerar_peca_aleatoria();
    // Define a posição inicial da nova peça
    *linha = 0;  // Começa do topo
    *coluna = 3; // Começa no meio do tabuleiro
}

void fix_piece(int *linha, int *coluna, PecaTetris peca)
{
    // Adiciona a peça no tabuleiro, tornando-a fixa
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (peca.shape[i][j] == 1)
            {
                board[*linha + i][*coluna + j] = 2; // Marca a posição com 2, indicando que está fixa
            }
        }
    }
}