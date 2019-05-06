#pragma once
#include "GameBoard.h"
#include "RecordBoard.h"
#include "HintBoard.h"
#include "EscBoard.h"
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
	int mode;                 // [ GameMode , MainMenuMode , EscMode , BackMode, ForwardMode ]
	// int subMode
	int order = 0;
	bool gameOver;
	const int frameWidth;   // 45 actual 135
	const int frameHeight;  // 40 actual 40
	static const int startX = 0;
	static const int startY = 0;
	const int width = 65;
	const int height = 35;
	static GameBoard gameBoard;
	static RecordBoard recordBoard;
	static HintBoard hintBoard;
	static EscBoard escBoard;

	// member function
	void gameStart(void);
	void printFrame();
	void readAndSetBoard();
	static void setCursor(int x, int y);
	// 0 黑, 1 藍, 2 綠, 4 紅, 5 紫, 7 白灰, 8 灰, 9 藍, 15 白, 12 紅
	static void SetColor(int fontColor = 7, int backgroundColor = 0);
	void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1
};

