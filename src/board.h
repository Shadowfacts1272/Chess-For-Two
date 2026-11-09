#include "move.cpp"
#include "tables.h"
#include "magic.h"
#include "bitwise.h"

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
    void print();
    void print_bitboard();
    void print_bitboard(u64 bitboard);
    
    void initialize_sliding_piece_attacks();
    u64 classical_rook_attacks(int square, u64 occupancy);
    u64 classical_bishop_attacks(int square, u64 occupancy);
    u64 rook_attacks(int square, u64 occupancy);
    u64 bishop_attacks(int square, u64 occupancy);
    u64 queen_attacks(int square, u64 occupancy);
};