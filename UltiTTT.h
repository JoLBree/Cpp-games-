#ifndef UltiTTT_H
#define UltiTTT_H

#include "board.h"
#include "common.h"
#include "GameBase.h"
#include "TicTacToeGame.h"
#include <iostream>

using namespace std;


class UltiTTT : public GameBase{

private:
	TicTacToeGame miniTTTs[num_mini_ttts];
	bool activeBoards[num_mini_ttts];
	unsigned int latestBoard;
	unsigned int nextBoard;

public:
	UltiTTT();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print() override{ cout << *this << endl; };
	virtual void prompt(unsigned int &boardNum, unsigned int &x, unsigned int &y);
	virtual string playerToName(players p);
	virtual string playerToDisplay(players p);
	virtual players rotate(players p);
	virtual void save(game_type g, bool write){ return GameBase::save(ulti_ttt, false); };
	unsigned int boardNumToIndex(unsigned int boardNum);
	unsigned int indexToBoardNum(unsigned int index);

protected:
	friend ostream& operator<<(std::ostream &strm, const UltiTTT &ttt);
};


#endif /* SudokuGame_H */