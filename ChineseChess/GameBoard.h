#pragma once
#include<vector>
using namespace std;
class GameBoard
{
public:
	// constructor
	GameBoard();
	~GameBoard();

	// data member
	vector<vector<int>> chessBoard;
	vector<vector<int>> colorBoard;
	const int startX = 40;
	const int startY = 3;
	const int width = 17;
	const int height = 19;

	// member function
	void printBoard();
	void moveChess(int x, int y);
private:
	void printRow(int y);
	wstring getPrintedChar(int x, int y);
	int getPrintedColor(int x, int y);


};

