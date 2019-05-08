#pragma once
#include "GameBoard.h"
#include "RecordBoard.h"
#include "HintBoard.h"
#include "EscBoard.h"
#include "MenuBoard.h"
#include "WinBoard.h"
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include <time.h>
using namespace std;

enum MODE { MenuMode = 0, GameMode, EscMode, ExitMode ,BackMode, ForwardMode };

class ChineseChess
{
public:
	// constructor
	ChineseChess();
	~ChineseChess();

	// data member
	int mode;                 // [  MenuMode , GameMode , EscMode , ReplayMode , ExitMode ]
	// int subMode
	int order = 0;
	bool gameOver;
	const int startX = 0;
	const int startY = 0;
	const int width = 65;
	const int height = 35;
	static GameBoard gameBoard;
	static RecordBoard recordBoard;
	static HintBoard hintBoard;
	static EscBoard escBoard;
	static MenuBoard maenuBoard;
	static WinBoard winBoard;
	vector<int> subWindow;   // X,Y,width,height
	//static ReadFileBoard fileBoard;
	static string fileName;
	// member function
	void gameLoop(void);
	void gameStart(void);
	void printFrame();
	void printFrame(int xpos, int ypos, int xsize, int ysize, wstring title = L"");

	int smallWindow(wstring title);
	int fileWindow();
	int readAndSetBoard(string name);
	void newGame();
	void saveGame(int finished);
	// 0 黑, 1 藍, 2 綠, 3淺藍, 4 紅, 5 紫, 6土黃, 7 白灰, 8 灰, 9 亮藍,10亮綠, 11亮淺藍, 12淺紅, 13淺粉, 14淺黃 15 白
	static void SetColor(int fontColor = 7, int backgroundColor = 0);
	static void setCursor(int x, int y);
	void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1
};