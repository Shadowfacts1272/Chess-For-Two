#include <iostream>
#include "board.h"
#include "move.cpp"
#include "tables.h"
#include "magic.h"
#include "bitwise.h"
 

void Board::print() {
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

void Board::print_bitboard() {
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

void Board::print_bitboard(u64 bitboard) {
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

// Generate rook masks
u64 Board::classical_rook_attacks(int square, u64 occupancy) {
    int i = square % 8;
    int j = square / 8;
    u64 mask = 0;
    // North, south, east, west directions
    for (int k = i + 1; k < 8; k++) {
        mask |= (1ULL << (k * 8 + j));
        if ((1ULL << (k * 8 + j)) & occupancy) {
            break;
        }
    }

    for (int k = i - 1; k > -1; k--) {
        mask |= (1ULL << (k * 8 + j));
        if ((1ULL << (k * 8 + j)) & occupancy) {
            break;
        }
    }

    for (int k = j + 1; k < 8; k++) {
        mask |= (1ULL << (i * 8 + k));
        if ((1ULL << (i * 8 + k)) & occupancy) {
            break;
        }
    }

    for (int k = j - 1; k > -1; k--) {
        mask |= (1ULL << (i * 8 + k));
        if ((1ULL << (i * 8 + k)) & occupancy) {
            break;
        }
    }

    return mask;
}

// Generate bishop masks
u64 Board::classical_bishop_attacks(int square, u64 occupancy) {
    int i = square % 8;
    int j = square / 8;
    u64 mask = 0;
    // Northeast
    for (int k = i + 1, l = j + 1; k < 8 && l < 8; k++, l++) {
        mask |= (1ULL << (k * 8 + l));
        if ((1ULL << (k * 8 + l)) & occupancy) {
            break;
        }
    }

    // Southeast
    for (int k = i - 1, l = j + 1; k > -1 && l < 8; k--, l++) {
        mask |= (1ULL << (k * 8 + l));
        if ((1ULL << (k * 8 + l)) & occupancy) {
            break;
        }
    }

    // Southwest
    for (int k = i - 1, l = j - 1; k > -1 && l > -1; k--, l--) {
        mask |= (1ULL << (k * 8 + l));
        if ((1ULL << (k * 8 + l)) & occupancy) {
            break;
        }
    }

    // Northwest
    for (int k = i + 1, l = j - 1; k < 8 && l > -1; k++, l--) {
        mask |= (1ULL << (k * 8 + l));
        if ((1ULL << (k * 8 + l)) & occupancy) {
            break;
        }
    }

    return mask;
}

void Board::initialize_sliding_piece_attacks() {
    for (int i = 0; i < 64; i++) {
        // Handle rook permutations
        u64 curr_premask = rook_magics[i].premask;
        int mask_size = pop_count(curr_premask);
        int permutations = 1 << mask_size;
        u64 blockers = 0;
        for (int j = 0; j < permutations; j++) {
            int curr_permutation = j;
            // Takes permutation and maps each bit to fit onto the premask
            for (int k = 0; k < mask_size; k++) {
                u64 bit = (curr_permutation & (1ULL << k)) >> k;
                blockers |= bit << return_lsb(curr_premask);
            }

            lookup_table[rook_magics[i].shift + (blockers * rook_magics[i].magic >> 52)] = classical_rook_attacks(i, blockers);
            blockers = 0;
            curr_premask = rook_magics[i].premask;
        }

        // Handle bishop permutations
        curr_premask = bishop_magics[i].premask;
        mask_size = pop_count(curr_premask);
        permutations = 1 << mask_size;
        blockers = 0;
        for (int j = 0; j < permutations; j++) {
            int curr_permutation = j;
            // Takes permutation and maps each bit to fit onto the premask
            for (int k = 0; k < mask_size; k++) {
                u64 bit = (curr_permutation & (1ULL << k)) >> k;
                blockers |= bit << return_lsb(curr_premask);
            }

            lookup_table[bishop_magics[i].shift + (blockers * bishop_magics[i].magic >> 55)] = classical_bishop_attacks(i, blockers);
            blockers = 0;
            curr_premask = bishop_magics[i].premask;
        }
    }
}

u64 Board::rook_attacks(int square, u64 occupancy) {
    return lookup_table[rook_magics[square].shift + ((occupancy & rook_magics[square].premask) * rook_magics[square].magic >> 52)];
}

u64 Board::bishop_attacks(int square, u64 occupancy) {
    return lookup_table[bishop_magics[square].shift + ((occupancy & bishop_magics[square].premask) * bishop_magics[square].magic >> 55)];
}

u64 Board::queen_attacks(int square, u64 occupancy) {
    return rook_attacks(square, occupancy) | bishop_attacks(square, occupancy);
}