#pragma once
#include"GameBoard.h"
#include"RecordBoard.h"
using namespace std;

class ChineseChess
{
public:
	int mode;
	int order;
	bool gameOver;
	GameBoard gameBoard;
	RecordBoard recordBoard;
	ChineseChess();
	~ChineseChess();

	void gameStart(void);
};

