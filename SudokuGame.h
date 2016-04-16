#ifndef SudokuGame_H
#define SudokuGame_H

#include "board.h"
#include "common.h"
#include "GameBase.h"
#include <iostream>

using namespace std;


class SudokuGame : public GameBase{
public:

	SudokuGame();
	virtual bool done();
	virtual bool draw(){ return false; };
	virtual int turn();
	virtual void print() override{ cout << *this << endl; }; // it says insert *this into an ostream, unsure if this ostream should be cout
	virtual void prompt(unsigned int &x, unsigned int &y, unsigned int &tile);
	virtual string playerToName(players p);
	virtual string playerToDisplay(players p){ return ""; };
	virtual players rotate(players p){ return p; };
	virtual bool save(game_type g, bool write){ return GameBase::save(sudoku, write); };

	bool checkLines();
	bool checkSquares();

protected:
	friend ostream& operator<<(std::ostream &strm, const SudokuGame &ttt);
};


#endif /* SudokuGame_H */