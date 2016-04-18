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
		else if (axes == sudoku_axes || axes == ulti_ttt_axes){
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
			if (axes == sudoku_axes || axes == ulti_ttt_axes){
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
		if (axes == sudoku_axes || axes == ulti_ttt_axes){
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
	if (axes == norm_axes || axes == sudoku_axes || axes == ulti_ttt_axes){
		cout << setw(longestLength) << " ";
		for (unsigned int x = 1; x < boardx; ++x){
			if (axes == sudoku_axes || axes == ulti_ttt_axes){
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
