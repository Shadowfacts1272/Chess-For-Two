#include <iostream>
#include "board.h"

int main() {
    Board board;
    board.initialize_sliding_piece_attacks();
    //rook_masks();
    //bishop_masks();
    //rook_premasks();
    //bishop_premasks();
    for (int i = 0; i < 64; i++) {
        //std::cout << std::hex << "{0x" << rook_magics[i].factor << ", " << std::dec << rook_magics[i].position << ", 0x" << std::hex << rook_premask[i] << "},\n";
    }

    board.print_bitboard(board.rook_attacks(h8, 0x4180800000000000));
    board.print_bitboard(board.bishop_attacks(d4, 0x1200000040000));
    //board.print_bitboard(bishop_attack(d4, 0x1109200802200));
    // g++ -std=c++20 main.cpp
} 