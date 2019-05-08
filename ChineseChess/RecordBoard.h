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
	const int startX;
	const int startY;
	const int width;
	const int height;

	// member function
	void printBoard();
	void regret(vector<vector<int>>& chessBoard);
	void reduction(vector<vector<int>>& chessBoard);
	void setRecord(int x, int y, const vector<vector<int>>& chessBoard, const vector<vector<int>>& colorBoard);		//�qchinessChess�I�s�Ǹ�Ƶ�recordBoard
private:
	static map<int, wstring> nameMap;
	wstring RedNum(int Xpos);
	wstring BlkNum(int Xpos);
	void writeDetail(record);
	void writeMsg(record);
	void clearBoard();
	void printMsg();
	int recordIndex;			//���V�ثe��recordBoard���ޭ�
};

struct record
{
	int hunter;			// ���ʪ�
	int Xpos;			// X�_�l�I
	int Ypos;			// Y�_�l�I
	int whosTurn;		// �¤�or���� ��:0 ��:1			// = (hunter < 8 && hunter > 0? 0 : 1)
	int deltaX;			// ����X
	int deltaY;			// ����Y
	int prey = 0;		// �Q�Y���H nullable
};