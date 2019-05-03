#pragma once
#include<string>
#include<vector>
#include<map>
using namespace std;

struct record;
class RecordBoard
{
public:
	// constructor
	RecordBoard();
	~RecordBoard();

	// data member
	vector<wstring> msgBoard;
	vector<record> detailBoard;
	const int startX;
	const int startY;
	const int width;
	const int height;

	// member function
	void printBoard();
	void writeMsg(record);
private:
	static map<int, wstring> nameMap;
	wstring RedNum(int Xpos);
	wstring BlkNum(int Xpos);
};

struct record
{
	int hunter;			// 移動者
	int Xpos;			// X起始點
	int Ypos;			// Y起始點
	int whosTurn;		// 黑方or紅方 黑:0 紅:1
	int deltaX;			// 移動X
	int deltaY;			// 移動Y
	int prey;			// 被吃的人 nullable
};