#ifndef TicTacToeGame_H
#define TicTacToeGame_H

#include "board.h"

using namespace std;

enum players{ playerX, playerO };

class TicTacToeGame{
private:
	unsigned int boardx;
	unsigned int boardy;
	unsigned int numTurns;
	vector<game_piece> pieces;
	friend ostream& operator<<(std::ostream &strm, const TicTacToeGame &ttt);
	players playerTurn;

public:
	TicTacToeGame();
	bool done();
	bool draw();
	bool isInner(const unsigned int &index);
	int prompt(unsigned int &x, unsigned int &y);
	int turn();
	int play();
};

//function prototypes
bool checkVertMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
bool checkHoriMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
bool checkUpRMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
bool checkUpLMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
string playerToName(players p);
string playerToDisplay(players p);
players rotate(players p);

#endif /* TicTacToeGame_H */