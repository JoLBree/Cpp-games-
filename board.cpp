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
int printBoard(const vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy, unsigned int longestLength, bool axes){
	// check if vector size == board game size
	if ((boardx)*(boardy) != pieces.size()){
		return diff_vector_board_sizes;
	}

	// print board
	for (int y = boardy - 1; y > 0; --y){
		if (axes){
			if (y == boardy - 1){
				cout << setw(longestLength) << " ";
			}
			else{
				cout << setw(longestLength) << y;
			}
		}
		for (unsigned int x = 1; x < boardx; ++x){
			int index = boardx * y + x;
			if (pieces[index].name.empty()){
				cout << setw(longestLength) << " ";
			}
			else{
				cout << setw(longestLength) << pieces[index].display;
			}
			cout << " "; // put a space between pieces
		}
		cout << setw(longestLength) << endl;
	}
	if (axes){
		cout << " ";
		for (unsigned int x = 1; x < boardx; ++x){
			if (x == boardy - 1 || x == 0){
				cout << setw(longestLength) << " ";
			}
			else{
				cout << setw(longestLength) << x;
			}
			cout << " ";

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