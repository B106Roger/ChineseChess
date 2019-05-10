﻿#pragma once
#include<string>
#include<vector>
#include<map>
#include<Windows.h>
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
	bool regret(vector<vector<int>>& chessBoard);
	bool reduction(vector<vector<int>>& chessBoard);
	void resetRecordBoard();
	void setRecord(int x, int y, const vector<vector<int>>& chessBoard, const vector<vector<int>>& colorBoard);		//從chinessChess呼叫傳資料給recordBoard
	void saveRecord(string fileName, int finished);
	void rebaseRecord();
private:
	static map<int, wstring> nameMap;
	wstring RedNum(int Xpos);
	wstring BlkNum(int Xpos);
	void writeDetail(record);
	wstring getMsg(record, wstring);
	void clearBoard();
	wstring numIntToStr(int);
	wstring bigNum(int);
	wstring twoWords(vector<vector<int>>, int, record);
	int whichCase(record, vector<vector<int>>);
	void printMsg();
	int recordIndex;			//指向目前的recordBoard索引值
};

struct record
{
	int hunter;			// 移動者
	int Xpos;			// X起始點
	int Ypos;			// Y起始點
	int whosTurn;		// 黑方or紅方 黑:0 紅:1			// = (hunter < 8 && hunter > 0? 0 : 1)
	int deltaX;			// 移動X
	int deltaY;			// 移動Y
	int prey = 0;		// 被吃的人 nullable
};