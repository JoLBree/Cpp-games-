// board.cpp : parses board + piece definitions, prints boards and each piece's neighbor
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "common.h"
#include "board.h"
#include <iomanip>

using namespace std;

board::board(int width, int height)
	: boardx(width), boardy(height), pieces(vector<game_piece>()){
	for (unsigned int i = 0; i < boardx * boardy; ++i){
		pieces.push_back(game_piece());
	}
}

// Part 11
int readDimensions(ifstream &ifstrm, unsigned int &x, unsigned int &y){
	string a;
	if (!getline(ifstrm, a)){
		return cannot_read_line;
	}
	istringstream iss(a);
	if (iss >> x && iss >> y){
		return success;
	}
	else{
		return cannot_extract_dimensions;
	}
}

// Part 12
int readPieces(ifstream &ifstrm, vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy){
	string a;
	bool some_valid_piece = false;
	while (getline(ifstrm, a)){
		istringstream iss(a);
		string mycolor;
		string myname;
		string mydisplay;
		unsigned int horiPos;
		unsigned int vertPos;
		if (iss >> mycolor && iss >> myname && iss >> mydisplay && iss >> horiPos && iss >> vertPos){
			mycolor = makeLower(mycolor);
			piece_color c = stringToClr(mycolor);
			if (c != invalid && horiPos <= boardx && vertPos <= boardy){
				int index = boardx * vertPos + horiPos;
				pieces[index].color = c; // this is reliant on pieces.cpp being included in header.cpp
				pieces[index].name = myname;
				pieces[index].display = mydisplay;
				some_valid_piece = true;
			}
		}
	}

	if (some_valid_piece){
		return success;
	}
	else{
		return no_good_piece_defns;
	}
}

// Part 13
int printBoard(const vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy, unsigned int longestLength, axes_type axes){
	// check if vector size == board game size
	unsigned int xcounter = 0;
	unsigned int ycounter = 0;
	if ((boardx)*(boardy) != pieces.size()){
		return diff_vector_board_sizes;
	}

	// print board
	for (int y = boardy - 2; y > 0; --y){
		if (axes == norm_axes){
			cout << setw(longestLength) << y;
			//cout << setw(longestLength) << y << setw(longestLength) << "||";
		}
		else if (axes == sudoku_axes){
			cout << setw(longestLength) << y << setw(longestLength) << "||";
		}
		for (unsigned int x = 1; x < boardx-1; ++x){
			int index = boardx * y + x;
			//if (pieces[index].name.empty()){
			if (pieces[index].display == " "){
				cout << setw(longestLength) << " ";
			}
			else{
				cout << setw(longestLength) << pieces[index].display;
			}
			if (axes == sudoku_axes){
				if (xcounter == 2){
					cout << setw(longestLength) << "||";
				}
				else{
					cout << setw(longestLength) << "|";
				}
				++xcounter;
				if (xcounter == 3){
					xcounter = 0;
				}
			}
		}
		if (axes == sudoku_axes){
		cout << endl;
			for (unsigned int i = 0; i < axes_parts; ++i){
				if (i % 2 == 0){
					if (ycounter == 2){
						cout << setw(longestLength) << "=";
					}
					else{
						cout << setw(longestLength) << "-";
					}
				}
				else{
					if (i % 6 == 1){
						cout << setw(longestLength) << "||";
					}
					else{
						cout << setw(longestLength) << "|";
					}
				}
			}
			++ycounter;
			if (ycounter == 3){
				ycounter = 0;
			}
		}

		cout << endl;
	}
	if (axes == norm_axes || axes == sudoku_axes){
		cout << setw(longestLength) << " ";
		for (unsigned int x = 1; x < boardx; ++x){
			if (axes == sudoku_axes){
				cout << setw(longestLength) << " ";
			}
			if (x == boardy - 1){
				cout << setw(longestLength) << " ";
			}
			else{
				cout << setw(longestLength) << x;
			}
			//cout << " ";

		}
	}
	return success;
}


// Determine if piece is near any edge(s)
boardPos getBoardPos(unsigned int index, unsigned int boardx, unsigned int boardy){
	if ((int)index - (int)boardx < 0){ // bottom. Casting required to enable correct subtraction
		if (index % boardx == 0){ // left
			return botL;
		}
		else if (index % boardx == boardx - 1){ // right
			return botR;
		}
		else{
			return bot;
		}

	}
	else if (index + boardx >= boardx*boardy){ // top
		if (index % boardx == 0){ // left
			return topL;
		}
		else if (index % boardx == boardx - 1){ // right
			return topR;
		}
		else{
			return top;
		}
	}
	else if (index % boardx == 0){ // left
		return L;
	}
	else if (index % boardx == boardx - 1){ // right
		return R;
	}
	else{
		return nonEdge;
	}

}

void printPiece(const game_piece &piece, unsigned int index, unsigned int boardx, bool semicolon){
	if (!piece.name.empty()){
		unsigned int piecey = index / boardx;
		unsigned int piecex = index % boardx;
		cout << piecex << "," << piecey << " " << colorToStr(piece.color) << " " << piece.name;
		if (semicolon){
			cout << "; ";
		}
	}
}