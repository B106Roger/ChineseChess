#pragma once
#include<vector>


using namespace std;
class MenuBoard
{
public:
	MenuBoard(int cursorX = 54, int cursorY = 20, int sizeX = 12, int arg_width = 9, int arg_height = 0);
	~MenuBoard();
	int mainMenu();
	void printBoard();
	void printSelect();


private:
	vector<int> cursor;   // 0 => xPost, 1 => yPos
	vector<int> size;     // 0 => width, 1 => height
	int mode;
	bool breakOut;
	// 0. 雙人遊戲  1. 繼續遊戲(讀取棋盤)  2. 重播棋局  3. 離開遊戲 	
};
