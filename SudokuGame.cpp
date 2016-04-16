#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "board.h"
#include "SudokuGame.h"
#include "common.h"
#include <set>

using namespace std;

SudokuGame::SudokuGame() : GameBase(sudoku_default_board_size + buffer_size, sudoku_default_board_size + buffer_size, sudoku_default_win_length, playerSudoku){
	getSave(sudoku);
}

ostream& operator<<(ostream &strm, const SudokuGame &sd) {
	printBoard(sd.pieces, sd.boardx, sd.boardy, sd.longestDisplayLength, sudoku_axes); //FIXME. implement print as sudoku_axes
	return strm;
}

int SudokuGame::turn(){
	//cout << "Enter a coodinate and a tile. eg: x,y 9" << endl;
	unsigned int x;
	unsigned int y;
	unsigned int tile;
	unsigned int index;
	bool validMove = false;
	while (!validMove){
		try{
			prompt(x, y, tile);
			index = boardx * y + x;
			if (isInner(index) && pieces[index].name == "name" && tile <= largest_sudoku_tile){
				validMove = true;
			}
			else{
				cout << "Place place a number 1-9 on a mutable tile" << endl;
			}
		}
		catch (processes quit){
			return quit;
		}
	}
	pieces[index].display = to_string(tile);
	if (pieces[index].display.length() > longestDisplayLength){ // record longest string of display.
		longestDisplayLength = pieces[index].display.length();
	}
	latestPiece = index;
	cout << endl << *this << endl;
	cout << "Latest move is " << x << "," << y << " <- " << pieces[index].display << endl;
	++numTurns;
	return valid_move_made;
}

void SudokuGame::prompt(unsigned int &x, unsigned int &y, unsigned int &tile){
	bool validInput = false;
	string s;
	unsigned int testx;
	unsigned int testy;
	unsigned int testTile;
	while (!validInput){
		cout << "Enter coordinates and number \"x,y #\" or \"quit\"" << endl;
		getline(cin, s);
		if (s == "quit"){
			throw quit;
		}
		istringstream iss(s);
		if (iss >> testx && iss.peek() == ',' && iss.ignore() && iss >> testy && iss >> testTile){
			unsigned int index = boardx * testy + testx;
			if (index < pieces.size() && testx < boardx && testy < boardy){
				x = testx;
				y = testy;
				tile = testTile;
				validInput = true;
			}
			else{
				cout << "Please enter a coordinate within the board" << endl;
			}
		}
	}
}

bool SudokuGame::done(){
	
	return (checkLines() && checkSquares());

	// for /// loop stuff
		// if piece is " " blank, return false
		// if nums.insert is false, return false
		// if nums.size() is 9, return true
}

bool SudokuGame::checkLines(){
	for (unsigned int x = 1; x < boardx - 1; ++x){
		set<string> nums;
		for (unsigned int y = 1; y < boardy-1; ++y){
			unsigned int index = boardx * y + x;
			if (index < pieces.size() && (pieces[index].display == " " || !(nums.insert(pieces[index].display).second))){ // no duplicates
				return false;
			}
		}
	}
	for (unsigned int y = 1; y < boardy - 1; ++y){
		set<string> nums;
		for (unsigned int x = 1; x < boardx - 1; ++x){
			unsigned int index = boardx * y + x;
			if (index < pieces.size() && (pieces[index].display == " " || !(nums.insert(pieces[index].display).second))){ // no duplicates
				return false;
			}
		}
	}
	return true;
}

bool SudokuGame::checkSquares(){
	for (unsigned int start = 0; start < square_starts.size(); ++start){
		set<string> nums;
		for (unsigned int miniY = 0; miniY < sudoku_square_length; ++miniY){
			for (unsigned int miniX = 0; miniX < sudoku_square_length; ++miniX){
				unsigned int index = square_starts[start] + miniX + boardx*miniY;
				if (index < pieces.size() && (pieces[index].display == " " || !(nums.insert(pieces[index].display).second))){ // no duplicates
					return false;
				}
			}
		}
	}
	return true;
}

string SudokuGame::playerToName(players p){
	switch (p){
	case playerSudoku:
		return "Player";
	default:
		return "invalid";
	}
}