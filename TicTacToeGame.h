#ifndef TicTacToeGame_H
#define TicTacToeGame_H

#include "board.h"
#include "GameBase.h"

using namespace std;


class TicTacToeGame : public GameBase{
public:
	TicTacToeGame();
	virtual bool done();
	virtual bool draw();
	bool isInner(const unsigned int &index);
	virtual int turn();
	virtual void print() override{ cout << *this << endl; }; // it says insert *this into an ostream, unsure if this ostream should be cout

protected:
	friend ostream& operator<<(std::ostream &strm, const TicTacToeGame &ttt);
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