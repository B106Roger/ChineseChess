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
	void printBoard(int mode = 0);
	
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
	vector<int> cursor;             // 視窗左上角x,y座標
	vector<int> size;               // 視窗長寬
	vector<int> lowerBoardCursor;   // 視窗下方部分左上角x,y座標
	vector<int> lowerBoardSize;     // 視窗下方部分長寬
	WinBoard winBoard;
	int order;
	//helper function
	void printLowerBoard(int mode = 0);
};

