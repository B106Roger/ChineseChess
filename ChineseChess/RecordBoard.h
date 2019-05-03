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
	int hunter;			// ���ʪ�
	int startX;			// X�_�l�I
	int startY;			// Y�_�l�I
	int deltaX;			// ����X
	int deltaY;			// ����Y
	int prey;			// �Q�Y���H nullable
};

map<int, wstring>RecordBoard::chessName = {
	pair<int,wstring>(1,L"�N"),
	pair<int,wstring>(2,L"�h"),
	pair<int,wstring>(3,L"�H"),
	pair<int,wstring>(4,L"��"),
	pair<int,wstring>(5,L"��"),
	pair<int,wstring>(6,L"�]"),
	pair<int,wstring>(7,L"��"),
	pair<int,wstring>(8,L"��"),
	pair<int,wstring>(9,L"�K"),
	pair<int,wstring>(10,L"��"),
	pair<int,wstring>(11,L"��"),
	pair<int,wstring>(12,L"�X"),
	pair<int,wstring>(13,L"��"),
	pair<int,wstring>(14,L"�L"),
};