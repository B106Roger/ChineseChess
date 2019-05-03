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
	int hunter;			// ���ʪ�
	int Xpos;			// X�_�l�I
	int Ypos;			// Y�_�l�I
	int whosTurn;		// �¤�or���� ��:0 ��:1
	int deltaX;			// ����X
	int deltaY;			// ����Y
	int prey;			// �Q�Y���H nullable
};