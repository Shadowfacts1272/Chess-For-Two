#include <iostream>
#include "move.cpp"
#include "tables.h"

enum Square {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
};

enum Piece {
    WP,
    BP,
    WN,
    BN,
    WB,
    BB,
    WR,
    BR,
    WQ,
    BQ,
    WK,
    BK,
    E
};

class Board {
private:
    u64 bitboards[13];
    int piece_list[64] = {
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
        E, E, E, E, E, E, E, E,
    };
    
public:
    void print() {
        static const char* unicode_pieces[13] = {"♙", "♟", "♘", "♞", "♗", "♝", "♖", "♜", "♕", "♛", "♔", "♚", "."};
        for (int i = 0; i < 8; i++) {
            std::cout << (i ^ 7) + 1 << " ";
            for (int j = 0; j < 8; j++) {
                // Print so a1 is at bottom left corner and a8 is top left
                int square_state = piece_list[(i * 8 + j) ^ 56];
                std::cout << unicode_pieces[square_state] << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "  a b c d e f g h\n";
    }

    void print_bitboard() {
        for (int i = 0; i < 8; i++) {
            std::cout << (i ^ 7) + 1 << " ";
            for (int j = 0; j < 8; j++) {
                // Print so a1 is at bottom left corner and a8 is top left
                int square_state = piece_list[(i * 8 + j) ^ 56];
                std::cout << ((square_state == E) ? 0 : 1) << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "  a b c d e f g h\n";
    }

    void print_bitboard(u64 bitboard) {
        for (int i = 0; i < 8; i++) {
            std::cout << (i ^ 7) + 1 << " ";
            for (int j = 0; j < 8; j++) {
                // Print so a1 is at bottom left corner and a8 is top left
                int square = (i * 8 + j) ^ 56;
                u64 square_mask = bitboard & (1ULL << square);
                std::cout << ((bitboard >> square) & 1) << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "  a b c d e f g h\n";
    }

    u64 get_rook_attacks(int square, u64 occupancy);
    u64 get_bishop_attacks(int square, u64 occupancy);
};
