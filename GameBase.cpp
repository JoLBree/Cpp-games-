#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "board.h"
#include "TicTacToeGame.h"
#include "common.h"
#include "GameBase.h"
#include "GomokuGame.h"

using namespace std;

GameBase* GameBase::makeGame(int numArgs, char* args[]){
	if (numArgs >= expected_name_args && numArgs <= gomoku_win_length){
		string game_name = args[input_game_name];
		if (game_name == "TicTacToe" && numArgs == expected_name_args){
			return new TicTacToeGame();
		}
		else if (game_name == "Gomoku"){
			if (numArgs == expected_name_args){
				return new GomokuGame();
			}
			else if (numArgs == gomoku_board_size){
				istringstream iss(args[gomoku_board_size-1]);
				int boardSize;
				if (iss >> boardSize && boardSize >= min_board_size){
					return new GomokuGame(boardSize);
				}			
			}
			else if (numArgs == gomoku_win_length){
				istringstream iss1(args[gomoku_board_size-1]);
				istringstream iss2(args[gomoku_win_length-1]);
				int boardSize;
				int winlength;
				if (iss1 >> boardSize && iss2 >> winlength && boardSize >= min_board_size && winlength >= min_win_length && boardSize >= winlength){
					return new GomokuGame(boardSize, winlength);
				}
			}
			
		}
	}
	throw wrong_usage;
	//return 0; // this has to return a GameBase. 0 is the only non-GameBase that can be returned, and is returned if the args are poorly formatted
}


GameBase::GameBase(int x, int y, int winLength, players plyr)
	:boardx(x), boardy(y), winNumMatch(winLength), pieces(vector<game_piece>()), playerTurn(plyr), longestDisplayLength(2), latestPiece(0), numTurns(0){
	bool flip = false;
	unsigned int a = 0;
	for (unsigned int i = 0; i < boardx * boardy; ++i){
		pieces.push_back(game_piece());
	}
}

int GameBase::prompt(unsigned int &x, unsigned int &y){
	bool validInput = false;
	string s;
	unsigned int testx;
	unsigned int testy;
	while (!validInput){
		cout << "Enter coordinates \"x,y\" or \"quit\"" << endl;
		cin >> s;
		if (s == "quit"){
			return quit;
		}
		istringstream iss(s);
		if (iss >> testx && iss.peek() == ',' && iss.ignore() && iss >> testy){
			unsigned int index = boardx * testy + testx;
			if (index < pieces.size() && testx < boardx && testy < boardy){
				x = testx;
				y = testy;
				validInput = true;
			}
			else{
				cout << "Please enter a coordinate within the board" << endl;
			}
		}
	}
	return enter_coords_done;
}

int GameBase::play(){
	print();
	while (true){
		//cout << "hey" << endl;
		if (turn() == quit){
			cout << playerToName(playerTurn) << " has quit. " << numTurns << " turns were played." << endl;
			throw quit;
		}
		else if (done()){
			cout << playerToName(playerTurn) << " has won!" << endl;
			return success;
		}
		else if (draw()){
			cout << "No moves remain, the game is a draw. " << numTurns << " turns were played." << endl;
			return game_draw;
		}
	}
}


bool GameBase::isInner(const unsigned int &index){
	if (index > boardx && index < (boardx * boardy) - boardx && index % boardx != 0 && index % boardx != boardx - 1){
		return true;
	}
	return false;
}

bool GameBase::win(){
//bool GameBase::win(const unsigned int &winNumMatch){
	//cout << "latest piece is " << latestPiece << endl;
	unsigned int vert = 1;
	unsigned int hori = 1;
	unsigned int fwdSlash = 1;
	unsigned int bkwdSlash = 1;
	checkTop(vert, latestPiece);
	checkBtm(vert, latestPiece);
	checkLeft(hori, latestPiece);
	checkRight(hori, latestPiece);
	checkBtmL(fwdSlash, latestPiece);
	checkTopR(fwdSlash, latestPiece);
	checkBtmR(bkwdSlash, latestPiece);
	checkTopL(bkwdSlash, latestPiece);
	//cout << "win vert is " << vert << " hori is " << hori << endl;
	if (vert >= winNumMatch || hori >= winNumMatch || fwdSlash >= winNumMatch || bkwdSlash >= winNumMatch){
		return true;
	}
	else{
		return false;
	}
}

bool GameBase::potentialWinRemains(const vector<string> &displays){
	for (unsigned int index = boardx; index < pieces.size() - boardx; ++index){
		//cout << "index is " << index << endl;
		if (isInner(index) && pieces[index].display == " "){ // for every possible move left on the board, check if one can lead to a win
			//cout << "enter index is " << index << endl;
			for (vector<string>::const_iterator i = displays.begin(); i != displays.end(); ++i) {
				unsigned int vert = 1;
				checkTop(vert, index, *i, true);
				checkBtm(vert, index, *i, true);
				if (vert >= winNumMatch){
					return true;
				}
				unsigned int hori = 1;
				checkLeft(hori, index, *i, true);
				checkRight(hori, index, *i, true);
				if (hori >= winNumMatch){
					return true;
				}
				unsigned int fwdSlash = 1;
				checkBtmL(fwdSlash, latestPiece);
				checkTopR(fwdSlash, latestPiece);
				if (fwdSlash >= winNumMatch){
					return true;
				}
				unsigned int bkwdSlash = 1;
				checkBtmR(bkwdSlash, latestPiece);
				checkTopL(bkwdSlash, latestPiece);
				if (bkwdSlash >= winNumMatch){
					return true;
				}
			}
		}
	}
	return false;
}

void GameBase::checkTop(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int above = boardx + index;
	if (isInner(above)){
		//cout << " above is " << above << " and index is " << index;
		if (!matchSpace && pieces[index].display == pieces[above].display){
			++numMatch;
			//cout << "is this triggering " << matchSpace << endl;
			checkTop(numMatch, above);
			return;
		}
		else if (matchSpace && (pieces[above].display == " " || pieces[above].display == matchDisplay)){
			++numMatch;
			//cout << "numMatch is " << numMatch << " winNumMatch is " << winNumMatch << endl;
			if (numMatch >= winNumMatch){
				return;
			}
			checkTop(numMatch, above, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkBtm(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int below = index - boardx;
	if (isInner(below)){
		if (!matchSpace && pieces[index].display == pieces[below].display){
			++numMatch;
			//cout << "is this triggering " << matchDisplay << endl;
			checkBtm(numMatch, below);
			return;
		}
		else if (matchSpace && (pieces[below].display == " " || pieces[below].display == matchDisplay)){
			++numMatch;
			//cout << "numMatch is " << numMatch << " winNumMatch is " << winNumMatch << endl;
			if (numMatch >= winNumMatch){
				return;
			}
			checkBtm(numMatch, below, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkRight(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int right = index + 1;
	if (isInner(right)){
		if (pieces[index].display == pieces[right].display){
			++numMatch;
			checkRight(numMatch, right);
			return;
		}
		else if (matchSpace && (pieces[right].display == " " || pieces[right].display == matchDisplay)){
			++numMatch;
			if (numMatch >= winNumMatch){
				return;
			}
			checkRight(numMatch, right, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkLeft(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int left = index - 1;
	if (isInner(left)){
		if (pieces[index].display == pieces[left].display){
			++numMatch;
			checkLeft(numMatch, left);
			return;
		}
		else if (matchSpace && (pieces[left].display == " " || pieces[left].display == matchDisplay)){
			++numMatch;
			if (numMatch >= winNumMatch){
				return;
			}
			checkLeft(numMatch, left, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkTopL(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int topL = index + boardx - 1;
	if (isInner(topL)){
		if (pieces[index].display == pieces[topL].display){
			++numMatch;
			checkTopL(numMatch, topL);
			return;
		}
		else if (matchSpace && (pieces[topL].display == " " || pieces[topL].display == matchDisplay)){
			++numMatch;
			if (numMatch >= winNumMatch){
				return;
			}
			checkTopL(numMatch, topL, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkTopR(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int topR = index + boardx + 1;
	if (isInner(topR)){
		if (pieces[index].display == pieces[topR].display){
			++numMatch;
			checkTopR(numMatch, topR);
			return;
		}
		else if (matchSpace && (pieces[topR].display == " " || pieces[topR].display == matchDisplay)){
			++numMatch;
			if (numMatch >= winNumMatch){
				return;
			}
			checkTopR(numMatch, topR, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkBtmL(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int btmL = index - boardx - 1;
	if (isInner(btmL)){
		if (pieces[index].display == pieces[btmL].display){
			++numMatch;
			checkBtmL(numMatch, btmL);
			return;
		}
		else if (matchSpace && (pieces[btmL].display == " " || pieces[btmL].display == matchDisplay)){
			++numMatch;
			if (numMatch >= winNumMatch){
				return;
			}
			checkBtmL(numMatch, btmL, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}

void GameBase::checkBtmR(unsigned int &numMatch, const unsigned int &index, const string &matchDisplay, const bool &matchSpace){
	unsigned int btmR = index - boardx + 1;
	if (isInner(btmR)){
		if (pieces[index].display == pieces[btmR].display){
			++numMatch;
			checkBtmR(numMatch, btmR);
			return;
		}
		else if (matchSpace && (pieces[btmR].display == " " || pieces[btmR].display == matchDisplay)){
			++numMatch;
			if (numMatch >= winNumMatch){
				return;
			}
			checkBtmR(numMatch, btmR, matchDisplay, matchSpace);
			return;
		}
		return;
	}
	return;
}