#pragma once
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
	const int startX = 4;
	const int startY = 2;
	const int width = 29;
	const int height = 32;

	// member function
	void printBoard();
	bool regret(vector<vector<int>>& chessBoard);
	bool regretSingle(vector<vector<int>>& chessBoard);
	bool reduction(vector<vector<int>>& chessBoard);
	bool reductionSingle(vector<vector<int>>& chessBoard);
	void resetRecordBoard();
	void setRecord(int x, int y, const vector<vector<int>>& chessBoard, const vector<vector<int>>& colorBoard);		// // 遊戲模式: 產生record結構，record結構+棋盤可以推出中式記譜法
	void saveRecord(string fileName, int finished);  // 遊戲模式: 儲存遊戲紀錄程式
	void rebaseRecord();                             // 重播模式: 重新產生中世記譜法

	void clearBoard();
	void printMsg();
private:
	static map<int, wstring> nameMap;
	wstring RedNum(int Xpos);
	wstring BlkNum(int Xpos);
	void writeDetail(record);
	wstring getMsg(record, wstring);                 // 產生中式記譜法
	wstring numIntToStr(int);
	wstring bigNum(int);
	wstring twoWords(vector<vector<int>>, int, record);
	int whichCase(record, vector<vector<int>>);
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