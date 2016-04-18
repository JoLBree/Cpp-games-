#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameBase.h"
#include "UltiTTT.h"
#include "common.h"
#include <iomanip>

using namespace std;

UltiTTT::UltiTTT() : GameBase(ulti_ttt_default_board_size + buffer_size, ulti_ttt_default_board_size + buffer_size, ulti_ttt_default_win_length, playerX){
	for (unsigned int i = 0; i < num_mini_ttts; ++i){
		miniTTTs[i] = *(new TicTacToeGame());
		activeBoards[i] = true;
	}
}

ostream& operator<<(ostream &strm, const UltiTTT &uttt) {
	unsigned int xcounter = 0;
	unsigned int ycounter = 0;
	for (unsigned int a = 0; a < ulti_ttt_x_axes_width; ++a){
		cout << setw(uttt.longestDisplayLength) << "="; //FIXME
	}
	cout << endl;
	for (int bigY = ulti_ttt_default_board_size - 1; bigY >= 0; --bigY){ // for every row in the big board
		for (int y = ulti_ttt_default_board_size; y > 0; --y){
			cout << setw(uttt.longestDisplayLength) << y << setw(uttt.longestDisplayLength) << "||";
			for (int bigX = 0; bigX < ulti_ttt_default_board_size; ++bigX){
				unsigned int bigBoardNum = bigY * ulti_ttt_default_board_size + bigX;
				for (int x = 0; x < ulti_ttt_default_board_size; ++x){
					int index = uttt.boardx * y + x +1;
					/*if (index == uttt.latestPiece){
						cout << "index is " << index << endl;
					}*/
					cout << setw(uttt.longestDisplayLength) << uttt.miniTTTs[bigBoardNum].pieces[index].display;
					if (xcounter == 2){
						cout << setw(uttt.longestDisplayLength) << "||";
					}
					++xcounter;
					if (xcounter == 3){
						xcounter = 0;
					}
				}
			}
			cout << endl;
			if (ycounter == 2){
				for (unsigned int a = 0; a < ulti_ttt_x_axes_width; ++a){
					cout << setw(uttt.longestDisplayLength) << "="; //FIXME
				}	
				cout << endl;
			}
			++ycounter;
			if (ycounter == 3){
				ycounter = 0;
			}
		}
	}
	cout << setw(uttt.longestDisplayLength) << " " << setw(uttt.longestDisplayLength) << "||";
	for (int bigX = 0; bigX < ulti_ttt_default_board_size; ++bigX){
		for (int smallX = 1; smallX <= ulti_ttt_default_board_size; ++smallX){
			cout << setw(uttt.longestDisplayLength) << smallX;
		}
		cout << setw(uttt.longestDisplayLength) << "||";
	}


	return strm;
}


bool UltiTTT::done(){
	if (miniTTTs[latestBoard].done()){
		pieces[boardNumToIndex(latestBoard)].display = playerToDisplay(playerTurn);
	}
	else if (miniTTTs[latestBoard].draw()){
		pieces[boardNumToIndex(latestBoard)].display = "-";
	}
	bool vertMatch = checkVertMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	bool horiMatch = checkHoriMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	bool upRMatch = checkUpRMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	bool upLMatch = checkUpLMatch(pieces, boardx, boardy, tictactoe_default_win_length);
	return (vertMatch || horiMatch || upRMatch || upLMatch);
}

bool UltiTTT::draw(){
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

int UltiTTT::turn(){
	playerTurn = rotate(playerTurn);
	cout << "Player " << playerToName(playerTurn) << " " << moveList[playerTurn] << endl;
	if (playerTurn == playerO){
		cout << "Player O, enter a coordinate" << endl;
	}
	else{
		cout << "Player X, enter a coordinate" << endl;
	}
	unsigned int boardNum;
	unsigned int x;
	unsigned int y;
	unsigned int index;
	bool validMove = false;
	while (!validMove){
		try{
			prompt(boardNum, x, y); // selected board is active, and coordinates are within the board
			index = boardx * y + x;
			if (isInner(index) && miniTTTs[boardNum].pieces[index].display == " "){
				validMove = true;
			}
			else{
				cout << "Unoccupied inner squares only, please" << endl;
			}
		}
		catch (processes quit){
			return quit;
		}
	}
	miniTTTs[boardNum].pieces[index].display = playerToDisplay(playerTurn);
	if (pieces[index].display.length() > longestDisplayLength){ // record longest string of display.
		longestDisplayLength = pieces[index].display.length();
	}
	latestPiece = index;
	latestBoard = boardNum;
	nextBoard = indexToBoardNum(index);
	if (pieces[index].display != " "){ // if sent to already won board
		for (unsigned int i = 0; i < num_mini_ttts; ++i){
			activeBoards[i] = true;
		}
	}
	else{
		for (unsigned int i = 0; i < num_mini_ttts; ++i){
			if (i == nextBoard){
				activeBoards[i] = true;
			}
			else{
				activeBoards[i] = false;
			}
		}
	}
	cout << endl << *this << endl;
	moveList[playerTurn] += (to_string(x) + "," + to_string(y) + "->" + to_string(latestBoard) + "; ");
	++numTurns;
	return valid_move_made;
}


void UltiTTT::prompt(unsigned int &boardNum, unsigned int &x, unsigned int &y){
	bool validInput = false;
	string s;
	unsigned int testx;
	unsigned int testy;
	unsigned int testBoardNum;
	while (!validInput){
		if (activeBoards[0] && activeBoards[1]){ // more than one board is active, ie all boards are active
			cout << "Enter any board number (0-8) and coordinates \"# x,y\" or \"quit\"" << endl;
		}
		else{
			cout << "Enter board number " << nextBoard << " and coordinates: \"" << nextBoard << " x,y\" or \"quit\"" << endl;
		}
		getline(cin, s);
		if (s == "quit"){
			throw quit;
		}
		istringstream iss(s);
		if (iss >> testBoardNum && iss >> testx && iss.peek() == ',' && iss.ignore() && iss >> testy){
			unsigned int index = boardx * testy + testx;
			if (testBoardNum < num_mini_ttts && activeBoards[testBoardNum]){
				if (index < pieces.size() && testx < boardx && testy < boardy){ // since there are two nested games, the size, boardx etc. are the same
					x = testx;
					y = testy;
					boardNum = testBoardNum;
					validInput = true;
				}
				else{
					cout << "Please enter a coordinate within the board" << endl;
				}
			}
			else{
				cout << "Please enter an active board" << endl;
			}

		}
	}
}


string UltiTTT::playerToName(players p){
	switch (p){
	case playerO:
		return "Os";
	case playerX:
		return "Xs";
	default:
		return "invalid";
	}
}

string UltiTTT::playerToDisplay(players p){
	switch (p){
	case playerO:
		return "O";
	case playerX:
		return "X";
	default:
		return " ";
	}
}

UltiTTT::players UltiTTT::rotate(players p){
	switch (p){
	case playerO:
		return playerX;
	case playerX:
		return playerO;
	default:
		return p;
	}
}

unsigned int UltiTTT::boardNumToIndex(unsigned int boardNum){
	switch (boardNum){
	case 0:
		return boardx + 1;
	case 1:
		return boardx + 2;
	case 2:
		return boardx + 3;
	case 3:
		return 2 * boardx + 1;
	case 4:
		return 2 * boardx + 2;
	case 5:
		return 2 * boardx + 2;
	case 6:
		return 3 * boardx + 1;
	case 7:
		return 3 * boardx + 2;
	case 8:
		return 3 * boardx + 3;
	default:
		throw invalid_boardNum;
	}
}

unsigned int UltiTTT::indexToBoardNum(unsigned int index){
	if (index == boardx + 1){
		return 0;
	}
	else if (index == boardx + 2){
		return 1;
	}
	else if (index == boardx + 3){
		return 2;
	}
	else if (index == 2 * boardx + 1){
		return 3;
	}
	else if (index == 2 * boardx + 2){
		return 4;
	}
	else if (index == 2 * boardx + 3){
		return 5;
	}
	else if (index == 3 * boardx + 1){
		return 6;
	}
	else if (index == 3 * boardx + 2){
		return 7;
	}
	else if (index == 3 * boardx + 3){
		return 8;
	}
	throw invalid_index_to_boardNum;
}