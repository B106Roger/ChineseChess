#pragma once
#include <vector>
#include<conio.h>
#include<Windows.h>
#include <iostream>
#include "WinBoard.h"

using namespace std;
class HintBoard
{
public:
	// constructor
	//HintBoard();
	HintBoard(int cursorX = 76, int cursorY = 1, int sizeX = 26, int sizeY = 32); // this is bigger one position
	//HintBoard(int cursorX, int cursorY, int sizeX, int sizeY);
	~HintBoard();

	// member function
	void printBoard();
	
	// when change order(black: 0/red: 1), call this
	void printHint1(int order);
	// when choose a chess, call this
	void printHint2(int order, int chessIndex);
	void hideHint2();
	// when General will be eaten, call this
	void printHint3(int order);
	void hideHint3();

	int winMenu(int order);
private:
	// data member
	vector<int> cursor;
	vector<int> size;
	vector<int> lowerBoardCursor;
	vector<int> lowerBoardSize;
	WinBoard winBoard;
	int order;
	//helper function
	void printLowerBoard();
};

