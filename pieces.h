#ifndef PIECES_H
#define PIECES_H

#include <string>

// Enumeration of piece_color
enum piece_color{red, black, white, blue, invalid, no_color};

// Declaration of game_piece
struct game_piece{
	piece_color color;
	std::string name;
	std::string display;
	game_piece(piece_color c = no_color, std::string n = "", std::string d = " ");
};

// Function prototypes
std::string colorToStr(piece_color a);
piece_color stringToClr(std::string a);
std::string toString(game_piece);
std::ostream& operator<<(std::ostream &strm, const game_piece &gp);


#endif /* PIECES_H */
