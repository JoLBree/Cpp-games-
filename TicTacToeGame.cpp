#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "common.h"

using namespace std;

TicTacToeGame::TicTacToeGame() : GameBase(tictactoe_default_board_size + buffer_size, tictactoe_default_board_size + buffer_size, tictactoe_default_win_length, playerX){
	getSave(tic_tac_toe);	
}


ostream& operator<<(ostream &strm, const TicTacToeGame &ttt) {
	printBoard(ttt.pieces, ttt.boardx, ttt.boardy, ttt.longestDisplayLength, norm_axes);
	// FIXME print successively
	return strm;
}


bool TicTacToeGame::done(){
	// check vertical match
	bool vertMatch = checkVertMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	bool horiMatch = checkHoriMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	bool upRMatch = checkUpRMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	bool upLMatch = checkUpLMatch(pieces, boardx, boardy, tictactoe_default_win_length);
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
	cout << "Player " << playerToName(playerTurn) << " " << moveList[playerTurn] << endl;
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
			// FIXME quit
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
	latestPiece = index; // record piece just put down
	cout << endl << *this << endl;
	moveList[playerTurn] += (to_string(x) + ", " + to_string(y) + "; ");
	++numTurns;
	return valid_move_made;
}

bool checkVertMatch(const vector<game_piece> &pieces, const unsigned int &boardx, const unsigned int &boardy, const unsigned int &numMatch){
	for (unsigned int x = 0; x < boardx; ++x){
		int countMatch = 1;
		for (unsigned int y = 0; y < boardy; ++y){
			unsigned int index = boardx * y + x;
			unsigned int above = boardx * (y + 1) + x;
			if (index < pieces.size() && above < pieces.size()){
				if (pieces[index].display != " " && pieces[index].display != "-" && pieces[index].display == pieces[above].display){
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
			}
			else{
				countMatch = 1;
			}
			if (countMatch == numMatch){
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
			}
			else{
				countMatch = 1;
			}
			if (countMatch == numMatch){
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
			}
			else{
				countMatch = 1;
			}
			if (countMatch == numMatch){
				return true;
			}
			i = next;
			next = i + boardx - 1;
		}
	}
	// check along y axis
	for (unsigned int y = 2 * boardx - 1; y < (pieces.size() - (numMatch - 1)*(boardx)); y += boardx){
		unsigned int countMatch = 1;
		unsigned int i = y;
		unsigned int next = i + boardx - 1;
		while (countMatch != numMatch && next < pieces.size()){
			if (pieces[i].display != " " && pieces[i].display == pieces[next].display){
				++countMatch;
			}
			else{
				countMatch = 1;
			}
			if (countMatch == numMatch){
				return true;
			}
			i = next;
			next = i + boardx - 1;
		}
	}
	return false;
}

string TicTacToeGame::playerToName(players p){
	switch (p){
	case playerO:
		return "Os";
	case playerX:
		return "Xs";
	default:
		return "invalid";
	}
}

string TicTacToeGame::playerToDisplay(players p){
	switch (p){
	case playerO:
		return "O";
	case playerX:
		return "X";
	default:
		return " ";
	}
}

TicTacToeGame::players TicTacToeGame::rotate(players p){
	switch (p){
	case playerO:
		return playerX;
	case playerX:
		return playerO;
	default:
		return p;
	}
}