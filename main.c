#include "tetris.h"

int main() {
    init_game();
    draw_board();
    
    printf("\nExibindo a peça T:\n");
    print_piece(pecas[2]);

    return 0;
}
