#pragma once
#include <vector>

using namespace std;
class EscBoard
{
public:
	EscBoard(int cursorX = 48, int cursorY = 7, int sizeX = 12, int sizeY = 11, int iniMode = 0);
	~EscBoard();
	int escMenu();
	void printBoard();
	void printWord();

private:
	vector<int> cursor;
	vector<int> size;
	int mode;
	bool breakOut;
};

