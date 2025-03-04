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
    int linha = 1, coluna = 0;                 // Posição inicial da peça
    int peca_atual = gerar_peca_aleatoria();   // Gera a primeira peça aleatória

    init_game();
    draw_board();

    printf("\nPosicionando a peça inicial...\n");
    place_piece(linha, coluna, pecas[peca_atual]);
    limpaTela();
    draw_board();

    while (1)
    {
        char tecla = get_key();

        if (tecla == 'h')
        {
            limpaTela();
            move_piece_left(&linha, &coluna, pecas[peca_atual]);
            draw_board();
        }
        else if (tecla == 'l')
        {
            limpaTela();
            move_piece_right(&linha, &coluna, pecas[peca_atual]);
            draw_board();
        }

        else if (tecla == 'k')
        {
            limpaTela();
            rotate_piece_right(linha, coluna, &pecas[peca_atual]);
            draw_board();
        }

        else if (tecla == 'j')
        {
            limpaTela();
            move_piece_down(&linha, &coluna, pecas[peca_atual]);
            draw_board();
        }
        
        else if (tecla == 'q')
        {
            printf("\nSaindo do jogo...\n");
            break;
        }
        
        check_piece_at_bottom(&linha, &coluna, pecas[peca_atual], &peca_atual);
        
    }

    return 0;
}