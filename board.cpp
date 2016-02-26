// board.cpp : parses board + piece definitions, prints boards and each piece's neighbor
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "common.h"
#include "board.h"

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
int printBoard(const vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy, bool axes){
	// check if vector size == board game size
	if ((boardx)*(boardy) != pieces.size()){
		return diff_vector_board_sizes;
	}

	// print board
	for (int y = boardy - 1; y >= 0; --y){
		if (axes){
			cout << y;
		}
		for (unsigned int x = 0; x < boardx; ++x){
			int index = boardx * y + x;
			if (pieces[index].name.empty()){
				cout << " ";
			}
			else{
				cout << pieces[index].display;
			}
		}
		cout << endl;
	}
	if (axes){
		cout << " ";
		for (unsigned int x = 0; x < boardx; ++x){
			cout << x;
		}
	}
	return success;
}


// Extra credit
int printNeighbors(const vector<game_piece> &pieces, unsigned int boardx, unsigned int boardy){

	if ((boardx)*(boardy) != pieces.size()){
		return diff_vector_board_sizes;
	}

	int relPos[] = { -1, 1, -(int)boardx, -(int)boardx - 1, -(int)boardx + 1, (int)boardx, (int)boardx - 1, (int)boardx + 1 }; // casting required to negate and subtract boardx

	for (unsigned int y = 0; y < boardy; ++y){
		for (unsigned int x = 0; x < boardx; ++x){
			int index = boardx * y + x;
			if (!pieces[index].name.empty()){
				printPiece(pieces[index], index, boardx, false);
				cout << " : ";
				switch (getBoardPos(index, boardx, boardy)){
					cout << " hi ";
				case botL: // print pieces according to whether the piece is near any edge
					for (unsigned int i = 0; i < 8; ++i){
						if (i != bot && i != L && i != botL && i != topL && i != botR){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				case bot:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != bot && i != botR && i != botL){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				case botR:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != bot && i != R && i != botR && i != topR && i != botL){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				case L:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != topL && i != L && i != botL){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				case R:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != topR && i != R && i != botR){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				case topL:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != top && i != topR && i != topL && i != L && i != botL){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
							cout << "; ";
						}
					}
					break;
				case top:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != top && i != topR && i != topL){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				case topR:
					for (unsigned int i = 0; i < 8; ++i){
						if (i != top && i != topR && i != topL && i != R && i != botR){
							printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
						}
					}
					break;
				default:
					for (unsigned int i = 0; i < 8; ++i){
						printPiece(pieces[index + relPos[i]], index + relPos[i], boardx);
					}
				}
				cout << endl;
			}
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