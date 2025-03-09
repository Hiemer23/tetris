#include "tetris.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

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

/**
 * @brief Verifica se uma tecla foi pressionada sem bloquear a execução.
 *
 * @return int Retorna 1 se uma tecla foi pressionada, ou 0 caso contrário.
 */
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Salva as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Desativa modo canônico e o echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Define o STDIN como não bloqueante
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Tenta ler um caractere
    ch = getchar();

    // Restaura as configurações originais do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    // Restaura o modo bloqueante
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin); // Devolve o caractere lido para o buffer
        return 1;
    }

    return 0;
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

void delay_1_ms()
{
    // Aguarda 1 milissegundo
    usleep(1000);
    limpaTela();
}

int main()
{
    int linha = 0, coluna = 3;                // Posição inicial da peça
    int peca_atual = number_aleatory_peace(); // Gera a primeira peça aleatória
    PecaTetris peca = pecas[peca_atual];

    init_game();
    draw_board();

    place_piece(linha, coluna, peca);
    limpaTela();
    draw_board();

    while (1)
    {
        char tecla;

        if (game_over()) // Verifica se o jogo acabou
        {
            printf("\nGame Over!\n");
            break;
        }

        if (kbhit())
        {
            tecla = get_key();

            if (tecla == 'h')
            {
                limpaTela();
                move_piece_left(&linha, &coluna, peca);
                draw_board();
            }
            else if (tecla == 'l')
            {
                limpaTela();
                move_piece_right(&linha, &coluna, peca);
                draw_board();
            }

            else if (tecla == 'k')
            {
                limpaTela();
                rotate_piece_right(linha, coluna, &peca);
                draw_board();
            }

            else if (tecla == 'j')
            {
                limpaTela();
                move_piece_down(&linha, &coluna, &peca, &peca_atual);
                draw_board();
            }

            else if (tecla == 'q')
            {
                printf("\nSaindo do jogo...\n");
                break;
            }
        }
        delay_1_ms();
        update_game(&linha, &coluna, &peca, &peca_atual);
        //check_piece_at_bottom(&linha, &coluna, peca, &peca_atual);
    }

    return 0;
}