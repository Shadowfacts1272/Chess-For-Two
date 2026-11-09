#ifndef BITWISE_H
#define BITWISE_H

#include "typedefs.h"

inline int pop_count(u64 bitboard) {
    return __builtin_popcountll(bitboard);
}

inline int get_lsb(u64 bitboard) {
    return __builtin_ctzll(bitboard);
}

inline void clear_lsb(u64 &bitboard) {
    bitboard &= bitboard - 1;
} 

inline void set_bit(u64 &bitboard, int square) {
    bitboard |= 1ULL << square;
}

inline void clear_bit(u64 &bitboard, int square) {
    bitboard &= ~(1ULL << square);
}

inline void toggle_bit(u64 &bitboard, int square) {
    bitboard ^= 1ULL << square;
}

inline int return_lsb(u64 &bitboard) {
    int lsb = get_lsb(bitboard);
    clear_lsb(bitboard);
    return lsb;
}

#endif