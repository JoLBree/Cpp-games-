#ifndef GameBase_H
#define GameBase_H

#include "board.h"

using namespace std;

enum players{ playerX, playerO };

class GameBase{
protected:
	unsigned int boardx;
	unsigned int boardy;
	unsigned int numTurns;
	unsigned int longestDisplayLength;
	vector<game_piece> pieces;
	players playerTurn;

public:
	GameBase(int x, int y, players plyr);
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	int prompt(unsigned int &x, unsigned int &y);
	int play();
	static GameBase* makeGame(int numArgs, char* args[]);
};

//Add a static method to the base class that takes an integer and an array of pointers to 
//char(the same types as are given to argc and argv in your program's main function signature) 
//and returns a pointer to an object of your base class. The method should check that exactly one argument
//has been passed to the program (in addition to the program's name), and if so that the string in argv[1] 
//is "TicTacToe".If so, the method should use the new operator to dynamically default construct an object 
//of your derived TicTacToe game class, and return the address of that object; otherwise, the method should 
//return a singlular pointer(i.e., a pointer whose value is 0), indicating that no object was constructed.


#endif /* GameBase_H */