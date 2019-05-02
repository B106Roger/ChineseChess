#pragma once
#include"GameBoard.h"
#include"RecordBoard.h"
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


	// member function
	void gameStart(void);
	void printFrame();
	void readAndSetBoard();
	void setCursor(int x, int y);
	
};

