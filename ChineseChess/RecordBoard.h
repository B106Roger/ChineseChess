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
	int hunter;        // ���ʪ�
	int deltaX;        // ����X
	int deltaY;        // ����Y
	int prey;          // �Q�Y���H nullable
};