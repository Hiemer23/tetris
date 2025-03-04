#include "tetris.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Função para capturar entrada sem precisar pressionar Enter
char get_key()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Função para limpar a tela no Windows ou Linux
void limpaTela()
{

#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux / Mac
#endif
}

int main()
{
    int linha = 1, coluna = 0;
#define PECA_DEFINIDA 4
    init_game();
    draw_board();

    printf("\nPosicionando a peça inicial...\n");
    place_piece(linha, coluna, pecas[PECA_DEFINIDA]);
    limpaTela();
    draw_board();

    while (1)
    {
        char tecla = get_key();

        if (tecla == 'h')
        {
            limpaTela();
            move_piece_left(&linha, &coluna, pecas[PECA_DEFINIDA]);
            draw_board();
        }
        else if (tecla == 'l')
        {
            limpaTela();
            move_piece_right(&linha, &coluna, pecas[PECA_DEFINIDA]);
            draw_board();
        }

        else if (tecla == 'k')
        {
            limpaTela();
            rotate_piece_right(linha, coluna, &pecas[PECA_DEFINIDA]);
            draw_board();
        }

        else if (tecla == 'j')
        {
            limpaTela();
            rotate_piece_left(linha, coluna, &pecas[PECA_DEFINIDA]);
            draw_board();
        }


        else if (tecla == 'q')
        {
            printf("\nSaindo do jogo...\n");
            break;
        }
        }

    return 0;
}