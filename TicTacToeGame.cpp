#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "board.h"
#include "TicTacToeGame.h"
#include "common.h"

using namespace std;

//Outside your game class, declare and define an insertion operator (operator<<) that takes a
//reference to an ostream and a reference to a const game class object as parameters, and
//returns the ostream reference that was passed in(this allows the operator to be called
//repeatedly on the same ostream object as in cout << tictactoe_game << endl;).Inside your
//game class, declare the insertion operator to be a friend so that it can access the private
//member variables of the game object.The operator should print out the current state of the
//game board with 'X' or 'O' characters for squares that have pieces on them, and spaces for
//empty squares, with the horizontal and vertical coordinate axes labeled.For example, initial
//the board might be printed out as :

TicTacToeGame::TicTacToeGame() : GameBase(5, 5, playerX){
}


ostream& operator<<(ostream &strm, const TicTacToeGame &ttt) {
	printBoard(ttt.pieces, ttt.boardx, ttt.boardy, ttt.longestDisplayLength, true);
	return strm;
}


bool TicTacToeGame::done(){
	// check vertical match
	bool vertMatch = checkVertMatch(pieces, boardx, boardy, 3);
	bool horiMatch = checkHoriMatch(pieces, boardx, boardy, 3);
	bool upRMatch = checkUpRMatch(pieces, boardx, boardy, 3);
	bool upLMatch = checkUpLMatch(pieces, boardx, boardy, 3);
	return (vertMatch || horiMatch || upRMatch || upLMatch);
}

bool TicTacToeGame::draw(){
	for (unsigned int i = 0; i < pieces.size(); ++i){
		if (isInner(i) && pieces[i].display == " "){
			return false;
		}
	}
	if (done()){
		return false;
	}
	return true;
}



int TicTacToeGame::turn(){
	playerTurn = rotate(playerTurn);
	if (playerTurn == playerO){
		cout << "Player O, enter a coordinate" << endl;
	}
	else{
		cout << "Player X, enter a coordinate" << endl;
	}
	unsigned int x;
	unsigned int y;
	unsigned int index;
	bool validMove = false;
	while (!validMove){
		if (prompt(x, y) == quit){
			return quit;
		}
		else{
			index = boardx * y + x;
			if (isInner(index) && pieces[index].display == " "){
				validMove = true;
			}
			else{
				cout << "Unoccupied inner squares only, please" << endl;
			}
		}
	}
	pieces[index].name = playerToName(playerTurn);
	pieces[index].display = playerToDisplay(playerTurn);
	if (playerToDisplay(playerTurn).length() > longestDisplayLength){ // record longest string of display.
		longestDisplayLength = playerToDisplay(playerTurn).length();
	}
	/*cout << endl << *this << endl << endl;*/
	cout << endl << *this << endl;
	cout << "Player " << playerToName(playerTurn) << ": " << x << ", " << y << endl;
	++numTurns;
	return valid_move_made;
}

bool TicTacToeGame::isInner(const unsigned int &index){
	if (index > boardx && index < (boardx * boardy) - boardx && index % boardx != 0 && index % boardx != boardx - 1){
		return true;
	}
	return false;
}

bool checkVertMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch){
	for (unsigned int x = 0; x < boardx; ++x){
		int countMatch = 1;
		for (unsigned int y = 0; y < boardy; ++y){
			unsigned int index = boardx * y + x;
			unsigned int above = boardx * (y + 1) + x;
			if (index < pieces.size() && above < pieces.size()){
				if (pieces[index].display != " " && pieces[index].display == pieces[above].display){
					++countMatch;
				}
				else{
					countMatch = 1;
				}
			}
			if (countMatch == numMatch){
				return true;
			}
		}
	}
	return false;
}

bool checkHoriMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch){
	for (unsigned int y = 0; y < boardy; ++y){
		int countMatch = 1;
		for (unsigned int x = 0; x < boardx; ++x){
			unsigned int index = boardx * y + x;
			unsigned int next = boardx * y + (x + 1);
			if (index < pieces.size() && next < pieces.size()){
				if (pieces[index].display != " " && pieces[index].display == pieces[next].display){
					++countMatch;
				}
				else{
					countMatch = 1;
				}
			}
			if (countMatch == numMatch){
				return true;
			}
		}
	}
	return false;
}

bool checkUpRMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch){
	// check starting along x axis
	for (unsigned int x = 0; x < boardx - numMatch; ++x){
		unsigned int countMatch = 1;
		unsigned int i = x;
		unsigned int next = i + boardx + 1;
		while (countMatch != numMatch && next < pieces.size()){
			if (pieces[i].display != " " && pieces[i].display == pieces[next].display){
				++countMatch;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			else{
				countMatch = 1;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			if (countMatch == numMatch){
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
				return true;
			}
			i = next;
			next = i + boardx + 1;
		}
	}
	// check along y axis
	for (unsigned int y = boardx; y < (pieces.size() - (numMatch - 1)*(boardx + 1)); y += boardx){
		unsigned int countMatch = 1;
		unsigned int i = y;
		unsigned int next = i + boardx + 1;
		while (countMatch != numMatch && next < pieces.size()){
			if (pieces[i].display != " " && pieces[i].display == pieces[next].display){
				++countMatch;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			else{
				countMatch = 1;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			if (countMatch == numMatch){
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
				return true;
			}
			i = next;
			next = i + boardx + 1;
		}
	}
	return false;
}

bool checkUpLMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch){
	// check starting along x axis
	for (unsigned int x = numMatch - 1; x < boardx; ++x){
		unsigned int countMatch = 1;
		unsigned int i = x;
		unsigned int next = i + boardx - 1;
		while (countMatch != numMatch && next < pieces.size()){
			if (pieces[i].display != " " && pieces[i].display == pieces[next].display){
				++countMatch;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			else{
				countMatch = 1;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			if (countMatch == numMatch){
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
				return true;
			}
			i = next;
			next = i + boardx - 1;
		}
		//cout << "end stretch " << x << endl;
	}
	// check along y axis
	for (unsigned int y = 2 * boardx - 1; y < (pieces.size() - (numMatch - 1)*(boardx)); y += boardx){
		unsigned int countMatch = 1;
		unsigned int i = y;
		unsigned int next = i + boardx - 1;
		while (countMatch != numMatch && next < pieces.size()){
			if (pieces[i].display != " " && pieces[i].display == pieces[next].display){
				++countMatch;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			else{
				countMatch = 1;
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
			}
			if (countMatch == numMatch){
				//cout << "i is  " << i << " next is " << next << " count is " << countMatch << endl;
				return true;
			}
			i = next;
			next = i + boardx - 1;
		}
	}
	return false;
}

string playerToName(players p){
	switch (p){
	case playerO:
		return "Os";
	case playerX:
		return "Xs";
	default:
		return "invalid";
	}
}

string playerToDisplay(players p){
	switch (p){
	case playerO:
		return "O";
	case playerX:
		return "X";
	default:
		return " ";
	}
}

players rotate(players p){
	switch (p){
	case playerO:
		return playerX;
	case playerX:
		return playerO;
	}
}