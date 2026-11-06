#include "typedefs.h"

class Move {
private:
    u64 data;

public:
    Move move(int source, int target, int piece ) {
        data = source | (target << 6) | (piece << 12);
    }
};