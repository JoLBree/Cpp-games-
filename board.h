#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "pieces.h"
#include "common.h"
	
// Function prototypes
int printBoard(const std::vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy, unsigned int longestLength, axes_type ax = norm_axes);

#endif /* BOARD_H */