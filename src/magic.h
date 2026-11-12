#ifndef MAGIC_H
#define MAGIC_H

#include "typedefs.h"

// Magic bitboard numbers and implementation from https://www.talkchess.com/forum/viewtopic.php?t=60065&start=14

struct Magic {
	u64 magic;
	int shift;
	u64 premask;
};

extern u64 lookup_table[89524];
extern Magic bishop_magics[64];
extern Magic rook_magics[64];

#endif