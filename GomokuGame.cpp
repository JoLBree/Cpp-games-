#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "board.h"
#include "GomokuGame.h"
#include "common.h"

using namespace std;


GomokuGame::GomokuGame(unsigned int size, unsigned int winLength) : GameBase(size + buffer_size, size + buffer_size, winLength, playerB){
}


ostream& operator<<(ostream &strm, const GomokuGame &gg) {
	printBoard(gg.pieces, gg.boardx, gg.boardy, gg.longestDisplayLength, true);
	return strm;
}

bool GomokuGame::done(){
	return win();
}

bool GomokuGame::draw(){
	vector<string> displays{ playerToDisplay(playerB), playerToDisplay(playerW) };
	playerTurn = rotate(playerTurn);
	return !potentialWinRemains(displays);
}

string GomokuGame::playerToName(players p){
	switch (p){
	case playerB:
		return "Black Stone";
	case playerW:
		return "White Stone";
	default:
		return "invalid";
	}
}

string GomokuGame::playerToDisplay(players p){
	switch (p){
	case playerB:
		return "B";
	case playerW:
		return "W";
	default:
		return " ";
	}
}

GomokuGame::players GomokuGame::rotate(players p){
	switch (p){
	case playerB:
		return playerW;
	case playerW:
		return playerB;
	default:
		return p;
	}
}

int GomokuGame::turn(){
	if (playerTurn == playerB){
		cout << "Player "+playerToName(playerB)+" , enter a coordinate" << endl;
	}
	else{
		cout << "Player " + playerToName(playerW) + " , enter a coordinate" << endl;
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
	latestPiece = index;
	/*cout << endl << *this << endl << endl;*/
	cout << endl << *this << endl;
	cout << "Player " << playerToName(playerTurn) << ": " << x << ", " << y << endl;
	++numTurns;
	return valid_move_made;
}

