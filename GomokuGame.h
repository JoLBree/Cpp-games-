#ifndef GomokuGame_H
#define GomokuGame_H

#include "board.h"
#include "common.h"
#include "GameBase.h"

using namespace std;


class GomokuGame : public GameBase{
public:
	
	GomokuGame(unsigned int size = gomoku_default_board_size, unsigned int winLength = gomoku_default_win_length);
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print() override{ cout << *this << endl; }; // it says insert *this into an ostream, unsure if this ostream should be cout
	virtual string playerToName(players p);
	virtual string playerToDisplay(players p);
	virtual players rotate(players p);
//
protected:
	friend ostream& operator<<(std::ostream &strm, const GomokuGame &ttt);
};


//function prototypes
//bool checkVertMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
//bool checkHoriMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
//bool checkUpRMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);
//bool checkUpLMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch);


#endif /* GomokuGame_H */