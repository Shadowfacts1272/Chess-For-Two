#include <cstdint>
#include <iostream>

typedef uint64_t u64;

// Generate king and knight attack masks
void king_masks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u64 mask = 0;
            // North, south, east, west directions
            if (i + 1 < 8) mask |= (1ULL << ((i + 1) * 8 + j));
            if (i - 1 > -1) mask |= (1ULL << ((i - 1) * 8 + j));
            if (j + 1 < 8) mask |= (1ULL << (i * 8 + (j + 1)));
            if (j - 1 > -1) mask |= (1ULL << (i * 8 + (j - 1)));
            // Northeast, Southeast, Southwest, Northwest
            if (i + 1 < 8 && j + 1 < 8) mask |= (1ULL << ((i + 1) * 8 + (j + 1)));
            if (i - 1 > -1 && j + 1 < 8) mask |= (1ULL << ((i - 1) * 8 + (j + 1)));
            if (i - 1 > -1 && j - 1 > -1) mask |= (1ULL << ((i - 1) * 8 + (j - 1)));
            if (i + 1 < 8 && j - 1 > -1) mask |= (1ULL << ((i + 1) * 8 + (j - 1)));
            std::cout << "0x" << std::hex << mask << ", ";
        }
        std::cout << "\n";
    }
}

void knight_masks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u64 mask = 0;
            // noNoEa
            if (i + 2 < 8 && j + 1 < 8) mask |= (1ULL << ((i + 2) * 8 + (j + 1)));
            // noEaEa
            if (i + 1 < 8 && j + 2 < 8) mask |= (1ULL << ((i + 1) * 8 + (j + 2)));
            // soEaEa
            if (i - 1 > -1 && j + 2 < 8) mask |= (1ULL << ((i - 1) * 8 + (j + 2)));
            // soSoEa
            if (i - 2 > -1 && j + 1 < 8) mask |= (1ULL << ((i - 2) * 8 + (j + 1)));
            // soSoWe
            if (i - 2 > -1 && j - 1 > -1) mask |= (1ULL << ((i - 2) * 8 + (j - 1)));
            // soWeWe
            if (i - 1 > -1 && j - 2 > -1) mask |= (1ULL << ((i - 1) * 8 + (j - 2)));
            // noWeWe
            if (i + 1 < 8 && j - 2 > -1) mask |= (1ULL << ((i + 1) * 8 + (j - 2)));
            // noNoWe
            if (i + 2 < 8 && j - 1 > -1) mask |= (1ULL << ((i + 2) * 8 + (j - 1)));
            std::cout << "0x" << std::hex << mask << ", ";
        }
        std::cout << "\n";
    }
}

// Generate rook masks
void rook_masks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u64 mask = 0;
            // North, south, east, west directions
            for (int k = i + 1; k < 8; k++) {
                mask |= (1ULL << (k * 8 + j));
            }

            for (int k = i - 1; k > -1; k--) {
                mask |= (1ULL << (k * 8 + j));
            }

            for (int k = j + 1; k < 8; k++) {
                mask |= (1ULL << (i * 8 + k));
            }

            for (int k = j - 1; k > -1; k--) {
                mask |= (1ULL << (i * 8 + k));
            }
            std::cout << "0x" << std::hex << mask << ", ";
        }
        std::cout << "\n";
    }
}

// Generate bishop masks
void bishop_masks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u64 mask = 0;
            // Northeast
            for (int k = i + 1, l = j + 1; k < 8 && l < 8; k++, l++) {
                mask |= (1ULL << (k * 8 + l));
            }

            // Southeast
            for (int k = i - 1, l = j + 1; k > -1 && l < 8; k--, l++) {
                mask |= (1ULL << (k * 8 + l));
            }

            // Southwest
            for (int k = i - 1, l = j - 1; k > -1 && l > -1; k--, l--) {
                mask |= (1ULL << (k * 8 + l));
            }

            // Northwest
            for (int k = i + 1, l = j - 1; k < 8 && l > -1; k++, l--) {
                mask |= (1ULL << (k * 8 + l));
            }
            std::cout << "0x" << std::hex << mask << ", ";
        }
        std::cout << "\n";
    }
}

// Generate rook and bishop premasks (magic bitboards)
void rook_premasks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u64 mask = 0;
            // North, south, east, west directions
            for (int k = i + 1; k < 7; k++) {
                mask |= (1ULL << (k * 8 + j));
            }

            for (int k = i - 1; k > 0; k--) {
                mask |= (1ULL << (k * 8 + j));
            }

            for (int k = j + 1; k < 7; k++) {
                mask |= (1ULL << (i * 8 + k));
            }

            for (int k = j - 1; k > 0; k--) {
                mask |= (1ULL << (i * 8 + k));
            }
            std::cout << "0x" << std::hex << mask << ", ";
        }
        std::cout << "\n";
    }
}

void bishop_premasks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u64 mask = 0;
            // Northeast
            for (int k = i + 1, l = j + 1; k < 7 && l < 7; k++, l++) {
                mask |= (1ULL << (k * 8 + l));
            }

            // Southeast
            for (int k = i - 1, l = j + 1; k > 0 && l < 7; k--, l++) {
                mask |= (1ULL << (k * 8 + l));
            }

            // Southwest
            for (int k = i - 1, l = j - 1; k > 0 && l > 0; k--, l--) {
                mask |= (1ULL << (k * 8 + l));
            }

            // Northwest
            for (int k = i + 1, l = j - 1; k < 7 && l > 0; k++, l--) {
                mask |= (1ULL << (k * 8 + l));
            }
            std::cout << "0x" << std::hex << mask << ", ";
        }
        std::cout << "\n";
    }
}