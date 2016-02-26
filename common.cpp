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
		if (*p >= 65 && *p <= 90){
			*p += 32;
		}
	}
	return a;
}



