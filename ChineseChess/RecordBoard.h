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
	static map<int, wstring> chessName;
	wstring RedNum(int Xpos);
	wstring BlkNum(int Xpos);
};

struct record
{
	int hunter;			// 移動者
	int startX;			// X起始點
	int startY;			// Y起始點
	int deltaX;			// 移動X
	int deltaY;			// 移動Y
	int prey;			// 被吃的人 nullable
};

map<int, wstring>RecordBoard::chessName = {
	pair<int,wstring>(1,L"將"),
	pair<int,wstring>(2,L"士"),
	pair<int,wstring>(3,L"象"),
	pair<int,wstring>(4,L"車"),
	pair<int,wstring>(5,L"馬"),
	pair<int,wstring>(6,L"包"),
	pair<int,wstring>(7,L"卒"),
	pair<int,wstring>(8,L"帥"),
	pair<int,wstring>(9,L"仕"),
	pair<int,wstring>(10,L"相"),
	pair<int,wstring>(11,L"車"),
	pair<int,wstring>(12,L"傌"),
	pair<int,wstring>(13,L"炮"),
	pair<int,wstring>(14,L"兵"),
};