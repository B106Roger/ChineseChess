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
	int movingChess(int x, int y);
	void resetColorBoard(void);
	void resetChessBoard(void);
	bool isGeneral(int order); // 偵測order方(0黑1紅)是否被將軍
private:
	void printRow(int y);
	wstring getPrintedChar(int x, int y);
	void moveKnight(int x, int y);
	void moveElephant(int x, int y);
	void moveHorse(int x, int y);
	void moveGeneral(int x, int y);
	void moveTank(int x, int  y);
	void moveCannon(int x, int y);
	void moveSolider(int x, int y);
	void moveChessWithoutPrintBoard(int x, int y); // 給isGeneral()使用
};

