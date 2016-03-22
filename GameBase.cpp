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

using namespace std;

GameBase::GameBase(int x, int y, players plyr)
	:boardx(x), boardy(y), pieces(vector<game_piece>()), playerTurn(plyr), longestDisplayLength(0), numTurns(0){
	bool flip = false;
	for (unsigned int i = 0; i < boardx * boardy; ++i){
		pieces.push_back(game_piece());
		/*if (i == 77){
			pieces.push_back(game_piece(red, "x", "O"));
			flip = !flip;
		}
		else{
			pieces.push_back(game_piece());
		}*/
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
			return quit;
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

GameBase* GameBase::makeGame(int numArgs, char* args[]){
	// check that only one argument
	if (numArgs == expected_args){
		//return usage(args[program_name], "game_name (eg TicTacToe)");
		string game_name = args[input_game_name];
		if (game_name == "TicTacToe"){
			//return usage(argv[program_name], "game_name (eg TicTacToe)");
			return new TicTacToeGame();
		}
	}
	
	return 0;
	
	//int outcome = ttt.play();
	//return outcome;
}