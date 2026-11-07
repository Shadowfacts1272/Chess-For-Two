#include <iostream>
#include "board.cpp"
#include "magic.h"


int main() {
    Board board;
    board.print();
    //rook_masks();
    //bishop_masks();
    //rook_premasks();
    //bishop_premasks();
    for (int i = 0; i < 64; i++) {
        //std::cout << std::hex << "{0x" << rook_magics[i].factor << ", " << std::dec << rook_magics[i].position << ", 0x" << std::hex << rook_premask[i] << "},\n";
    }
}