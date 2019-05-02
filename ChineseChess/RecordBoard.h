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
	int hunter;        // 移動者
	int deltaX;        // 移動X
	int deltaY;        // 移動Y
	int prey;          // 被吃的人 nullable
};