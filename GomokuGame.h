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
	virtual void print() override{ cout << *this << endl; };
	virtual string playerToName(players p);
	virtual string playerToDisplay(players p);
	virtual players rotate(players p);
	virtual void save(game_type g, bool write){ return GameBase::save(gomoku, write); };
//
protected:
	friend ostream& operator<<(std::ostream &strm, const GomokuGame &ttt);
};


#endif /* GomokuGame_H */