#pragma once
#include "GameBoard.h"
#include "RecordBoard.h"
#include "HintBoard.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include<Windows.h>
using namespace std;

class ChineseChess
{
public:
	// constructor
	ChineseChess();
	~ChineseChess();


	// data member
	int mode;
	int order;
	bool gameOver;
	const int frameWidth;   // 45 actual 135
	const int frameHeight;  // 40 actual 40
	GameBoard gameBoard;
	RecordBoard recordBoard;
	HintBoard hintBoard;


	// member function
	void gameStart(void);
	void printFrame();
	void readAndSetBoard();
	static void setCursor(int x, int y);
	static void SetColor(int f = 7, int b = 0);
};

