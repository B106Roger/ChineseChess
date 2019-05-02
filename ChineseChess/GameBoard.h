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
	
	// member function
	void printBoard();
};

