// Lab2.cpp : Defines the entry point for the console application.
//

/*
* Errors: end of file found before left brace
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "TicTacToeGame.h"
#include "common.h"

using namespace std;

int main(int argc, char* argv[])
{
	// check that only one argument
	if (argc != expected_args){
		return usage(argv[program_name], "game_name (eg TicTacToe)");
	}
	else{
		string game_name = argv[input_game_name];
		if (game_name != "TicTacToe"){
			return usage(argv[program_name], "game_name (eg TicTacToe)");
		}
	}

	TicTacToeGame ttt = TicTacToeGame();
	int outcome = ttt.play();
	return outcome;
}



