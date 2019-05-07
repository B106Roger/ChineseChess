#pragma once
#include <vector>

using namespace std;
class WinBoard
{
public:
	WinBoard(int cursorX = 34, int cursorY = 15, int sizeX = 24, int sizeY = 5, int iniMode = 1);
	~WinBoard();
	int winMenu(int order);
	void printBoard();
	void printWord();

private:
	vector<int> cursor;
	vector<int> size;
	int mode; // 0:回主選單 / 1:儲存紀錄
	int winner;
};

