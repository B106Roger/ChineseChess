#pragma once
#include <vector>
//#include<conio.h>
//#include<Windows.h>
//#include <iostream>
#include "ChineseChess.h"
using namespace std;
class HintBoard
{
public:
	// constructor
	HintBoard();
	HintBoard(int cursorX = 86, int cursorY = 2, int sizeX = 42, int sizeY = 35);
	
	~HintBoard();


	// data member
	vector<int> cursor;
	vector<int> size;
	

	// member function
	void printBoard();

};

