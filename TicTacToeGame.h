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
	virtual int turn();
	virtual void print() override{ cout << *this << endl; }; // it says insert *this into an ostream, unsure if this ostream should be cout
	//virtual enum players{ playerX, playerO, playerB, playerW };
	virtual string playerToName(players p);
	virtual string playerToDisplay(players p);
	virtual players rotate(players p);
	virtual bool save(game_type g, bool write){ return GameBase::save(tic_tac_toe, write); };

protected:
	friend ostream& operator<<(std::ostream &strm, const TicTacToeGame &ttt);
};


//function prototypes
bool checkVertMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
bool checkHoriMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
bool checkUpRMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
bool checkUpLMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);


#endif /* TicTacToeGame_H */