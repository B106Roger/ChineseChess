#pragma once
#include <vector>

using namespace std;
class EscBoard
{
public:
	EscBoard(int cursorX = 44, int cursorY = 7, int sizeX = 12, int sizeY = 11, int iniMode = 0);
	~EscBoard();
	int escMenu();
	void printBoard();
	void printWord();

private:
	vector<int> cursor;       // 視窗左上角x,y座標
	vector<int> size;         // 視窗長寬
	int mode;                 // 0 繼續遊戲; 1 重新開始; 2 我方投降; 3 儲存遊戲; 4 回主選單
};

