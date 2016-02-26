// Pieces.cpp : Pieces for game board

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "common.h"
#include "pieces.h"

using namespace std;

// Part 8
string colorToStr(piece_color a){
	switch (a){
	case red:
		return "red";
	case black:
		return "black";
	case white:
		return "white";
	case blue:
		return "blue";
	case no_color:
		return "no_color";
	default:
		return "invalid";
	}
}

// Part 9
piece_color stringToClr(string a){
	if (a == "red"){
		return piece_color::red;
	}
	else if (a == "black"){
		return piece_color::black;
	}
	else if (a == "white"){
		return piece_color::white;
	}
	else if (a == "blue"){
		return piece_color::blue;
	}
	else if (a == "" || a == " " || a == "\t"){
		return piece_color::no_color;
	}
	else{
		return piece_color::invalid;
	}
}

game_piece::game_piece(piece_color c, string n, string d){
	color = c;
	name = n;
	display = d;
}

std::ostream& operator<<(std::ostream &strm, const game_piece &gp) {
	return strm << colorToStr(gp.color) << " " << gp.name;
}