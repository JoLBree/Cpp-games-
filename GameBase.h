#ifndef GameBase_H
#define GameBase_H

#include "board.h"

using namespace std;



class GameBase{

private:
	void checkTop(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkBtm(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkRight(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkLeft(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkTopL(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkTopR(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkBtmL(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);
	void checkBtmR(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay = " ", const bool &matchSpace = false);

protected:
	virtual enum players{ playerX, playerO, playerB, playerW };
	unsigned int boardx;
	unsigned int boardy;
	unsigned int numTurns;
	unsigned int longestDisplayLength;
	unsigned int latestPiece;
	unsigned int winNumMatch;
	vector<game_piece> pieces;
	players playerTurn;
	bool win();
	bool potentialWinRemains(const vector<string> &displays);


public:
	GameBase(int x, int y, int winLength, players plyr);
	bool isInner(const unsigned int &index);
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	virtual string playerToName(players p) = 0;
	virtual string playerToDisplay(players p) = 0;
	virtual players rotate(players p) = 0;
	virtual int prompt(unsigned int &x, unsigned int &y);
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
