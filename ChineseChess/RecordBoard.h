#pragma once
#include<string>
#include<vector>
using namespace std;

struct record;
class RecordBoard
{
public:
	// constructor
	RecordBoard();
	~RecordBoard();

	// data member
	vector<string> msgBoard;
	vector<record> detailBoard;
	const int startX;
	const int startY;
	const int width;
	const int height;

	// member function
	void printBoard();
};

struct record
{
	int hunter;        // 仮以��
	int deltaX;        // 仮以X
	int deltaY;        // 仮以Y
	int prey;          // �Q�Y�困H nullable
};