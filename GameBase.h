#ifndef GameBase_H
#define GameBase_H

#include "board.h"
#include "common.h"
#include <memory>

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
	virtual enum players{ playerX, playerO, playerB, playerW, playerSudoku };
	unsigned int boardx;
	unsigned int boardy;
	unsigned int winNumMatch;
	unsigned int numTurns;
	unsigned int longestDisplayLength;
	unsigned int latestPiece;
	players playerTurn;
	array<string, num_player_types> moveList;
	static shared_ptr<GameBase> gameBasePtr;
	bool win();
	bool potentialWinRemains(const vector<string> &displays);
	bool getSave(game_type game);

public:
	GameBase(int x, int y, int winLength, players plyr);
	vector<game_piece> pieces;
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
	static void makeGame(int numArgs, char* args[]);
	static shared_ptr<GameBase> instance();
	virtual void save(game_type g, bool write);
	string gameToFile(game_type g);
};


#endif /* GameBase_H */
