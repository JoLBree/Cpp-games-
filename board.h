#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "pieces.h"
	
// Enumerations
// these are both indices to the RelPos[] array in board.cpp, and enums to determine which pieces to print
enum boardPos{ L = 0, R = 1, bot = 2, botL = 3, botR = 4, top = 5, topL = 6, topR = 7, nonEdge};

struct board{
	unsigned int boardx;
	unsigned int boardy;
	std::vector<game_piece> pieces;
	board(int width, int height);
};

// Function prototypes
int readDimensions(std::ifstream &ifstrm, unsigned int &x, unsigned int &y);
int readPieces(std::ifstream &ifstrm, std::vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy);
int printBoard(const std::vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy, bool axes = "false");
int printNeighbors(const std::vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy);
boardPos getBoardPos(unsigned int index, unsigned int boardx, unsigned int boardy);
void printPiece(const game_piece &piece, unsigned int index, unsigned int boardx, bool semicolon = "true");

#endif /* BOARD_H */