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
#include "SudokuGame.h"
#include "UltiTTT.h"
#include <memory>

using namespace std;

shared_ptr<GameBase> GameBase::gameBasePtr = nullptr;

GameBase::GameBase(int x, int y, int winLength, players plyr)
	:boardx(x), boardy(y), winNumMatch(winLength), pieces(vector<game_piece>()), playerTurn(plyr), longestDisplayLength(2), latestPiece(0), numTurns(0){
	
	for (unsigned int i = 0; i < moveList.size(); ++i){
		moveList[i] = "moves: ";
	}

	unsigned int a = 0;
	for (unsigned int i = 0; i < boardx * boardy; ++i){
		pieces.push_back(game_piece());
	}
}

bool GameBase::getSave(game_type game){
	ifstream ifstrm;
	ifstrm.open(gameToFile(game));
	if (!ifstrm.is_open()){
		throw fail_to_open_file;
	}

	string a;
	string tempString;
	int tempInt;
	if (getline(ifstrm, a)){
		istringstream iss(a);
		if (iss >> tempString && tempString == "game:" && iss >> tempInt && tempInt == game){ // if have data
			if (getline(ifstrm, a) && a == "boardx:boardy:winNumMatch:numTurns:longestDisplayLength:latestPiece:playerTurn"){
				if (getline(ifstrm, a)){
					istringstream iss(a);
					unsigned int temp_boardx;
					unsigned int temp_boardy;
					unsigned int temp_winNumMatch;
					unsigned int temp_numTurns;
					unsigned int temp_longestDisplayLength;
					unsigned int temp_latestPiece;
					unsigned int temp_playerTurn;
					if (iss >> temp_boardx && iss >> temp_boardy && iss >> temp_winNumMatch && iss >> temp_numTurns && iss >> temp_longestDisplayLength && iss >> temp_latestPiece && iss >> temp_playerTurn){
						for (unsigned int i = 0; i < moveList.size(); ++i){
							if (getline(ifstrm, a)){
								unsigned int temp_player;
								string temp_moveList;
								istringstream iss(a);
								if (iss >> temp_player && getline(iss, temp_moveList)){
									moveList[temp_player] = temp_moveList;
								}
								else{
									throw bad_moves;
								}
							}							
							else{
								throw bad_moves;
							}
						}
						vector<game_piece> temp_pieces(temp_boardx*temp_boardy);
						if (getline(ifstrm, a) && a == "pieces:"){
							while (getline(ifstrm, a)){
								istringstream iss(a);
								unsigned int index;
								int mycolor;
								string myname;
								string mydisplay;
								if (iss >> index && iss >> mycolor && iss >> myname && iss >> mydisplay){
									piece_color c = piece_color(mycolor);
									if (c != invalid && index < temp_boardx* temp_boardy){
										temp_pieces[index].color = c;
										temp_pieces[index].name = myname;
										temp_pieces[index].display = mydisplay;
									}
									else{
										throw invalid_piece;
									}
								}
								else{
									throw invalid_piece;
								}
							}
							boardx = temp_boardx;
							boardy = temp_boardy;
							winNumMatch = temp_winNumMatch;
							numTurns = temp_numTurns;
							longestDisplayLength = temp_longestDisplayLength;
							latestPiece = temp_latestPiece;
							playerTurn = players(temp_playerTurn);
							pieces = temp_pieces;
							return true;
						}
						else{
							throw bad_board;
						}						
					}
					else{
						throw bad_board;
					}
				}
				else{
					throw bad_board;
				}
			}
			else{
				throw bad_board;
			}
		}
	} // do nothing, the default is fine
	return false;
}

shared_ptr<GameBase> GameBase::instance(){
	if (gameBasePtr == nullptr){
		throw gamebase_ptr_is_null;
	}
	return gameBasePtr;
}

string GameBase::gameToFile(game_type g){
	switch (g){
	case tic_tac_toe:
		return "tictactoe.txt";
	case gomoku:
		return "gomoku.txt";
	case sudoku:
		return "sudoku.txt";
	case ulti_ttt:
		return "ultiTTT.txt";
	default:
		return "dummy.txt";
	}
}

void GameBase::save(game_type g, bool write){
	ofstream ofs;
	ofs.open(gameToFile(g));
	if (write){
		ofs << "game: " << g << endl;
		ofs << "boardx:boardy:winNumMatch:numTurns:longestDisplayLength:latestPiece:playerTurn" << endl;
		ofs << boardx << " " << boardy << " " << winNumMatch << " " << numTurns << " " << longestDisplayLength << " " << latestPiece << " " << playerTurn << endl;
		for (unsigned int i = 0; i < moveList.size(); ++i){
			ofs << i << " " << moveList[i] << endl;
		}
		ofs << "pieces:" << endl;
		for (unsigned int i = 0; i < pieces.size(); ++i){
			if (pieces[i].display != " "){
				ofs << i << " " << pieces[i].color << " " << pieces[i].name << " " << pieces[i].display << endl;
			}
		}
	}
	else{
		ofs << "" << endl;
	}

}

void GameBase::makeGame(int numArgs, char* args[]){
	if (gameBasePtr != nullptr){
		throw gamebase_ptr_is_not_null;
	}

	if (numArgs >= expected_name_args && numArgs <= gomoku_win_length){
		string game_name = args[input_game_name];
		if (game_name == "TicTacToe" && numArgs == expected_name_args){
			TicTacToeGame * tttGame = new TicTacToeGame();
			gameBasePtr = make_shared<TicTacToeGame>(*tttGame);
		}
		else if (game_name == "UltimateTicTacToe" && numArgs == expected_name_args){
			UltiTTT * tttGame = new UltiTTT();
			gameBasePtr = make_shared<UltiTTT>(*tttGame);
		}
		else if (game_name == "Gomoku"){
			if (numArgs == expected_name_args){
				GomokuGame * gmGame = new GomokuGame();
				gameBasePtr = make_shared<GomokuGame>(*gmGame);
			}
			else if (numArgs == gomoku_board_size){
				istringstream iss(args[gomoku_board_size-1]);
				int boardSize;
				if (iss >> boardSize && boardSize >= min_board_size){
					GomokuGame * gmGame = new GomokuGame(boardSize);
					gameBasePtr = make_shared<GomokuGame>(*gmGame);
				} else{
					throw disallowed_board_size;
				}
			}
			else if (numArgs == gomoku_win_length){
				istringstream iss1(args[gomoku_board_size-1]);
				istringstream iss2(args[gomoku_win_length-1]);
				int boardSize;
				int winlength;
				if (iss1 >> boardSize && iss2 >> winlength && boardSize >= min_board_size && winlength >= min_win_length && boardSize >= winlength){
					GomokuGame * gmGame = new GomokuGame(boardSize, winlength);
					gameBasePtr = make_shared<GomokuGame>(*gmGame);
				} else{
					throw disallowed_board_size;
				}
			} else{
				throw wrong_usage;
			}
		}else if (game_name == "Sudoku" && numArgs == expected_name_args){
			SudokuGame * sdkGame = new SudokuGame();
			gameBasePtr = make_shared<SudokuGame>(*sdkGame);
		}		
		else{
			throw bad_game_name;
		}
	} else{
		throw wrong_usage;
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
		if (turn() == quit){
			cout << playerToName(playerTurn) << " has quit. " << numTurns << " turns were played." << endl;
			bool validInput = false;
			string s;
			while (!validInput){
				cout << "Save this game? Enter 'yes' or 'no'." << endl;
				cin >> s;
				if (s == "yes"){
					save(dummy_game, true);
					validInput = true;
				}
				else if (s == "no"){
					save(dummy_game, false);
					validInput = true;
				}
			}
			throw quit;
		}
		else if (done()){
			cout << playerToName(playerTurn) << " has won!" << endl;
			save(dummy_game, false);
			return success;
		}
		else if (draw()){
			cout << "No moves remain, the game is a draw. " << numTurns << " turns were played." << endl;
			save(dummy_game, false);
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
	if (vert >= winNumMatch || hori >= winNumMatch || fwdSlash >= winNumMatch || bkwdSlash >= winNumMatch){
		return true;
	}
	else{
		return false;
	}
}



bool GameBase::potentialWinRemains(const vector<string> &displays){
	for (unsigned int index = boardx; index < pieces.size() - boardx; ++index){
		if (isInner(index) && pieces[index].display == " "){ // for every possible move left on the board, check if one can lead to a win
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
		if (!matchSpace && pieces[index].display == pieces[above].display){
			++numMatch;
			checkTop(numMatch, above);
			return;
		}
		else if (matchSpace && (pieces[above].display == " " || pieces[above].display == matchDisplay)){
			++numMatch;
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
			checkBtm(numMatch, below);
			return;
		}
		else if (matchSpace && (pieces[below].display == " " || pieces[below].display == matchDisplay)){
			++numMatch;
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