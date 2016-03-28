// Common.cpp : Common functions across programs


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "common.h"

using namespace std;


int usage(char program_name[], string info){
	cout << "usage issue: " << program_name << " " << info << endl;
	return wrong_usage;
}

string makeLower(string a){	
	char * p;
	for (unsigned int i = 0; i < a.size(); ++i){
		p = &a[i];
		if (*p >= ascii_upper_letters_start && *p <= ascii_upper_letters_end){
			*p += ascii_upper_lower_difference;
		}
	}
	return a;
}


