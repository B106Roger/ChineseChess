#include "RecordBoard.h"
#include<Windows.h>
#include<iostream>


RecordBoard::RecordBoard()
	:startX(4), startY(1), width(27), height(31)
{
}


RecordBoard::~RecordBoard()
{
}

void RecordBoard::printBoard()
{
	COORD point;

	for (int i = 0; i < height; i++)
	{
		point.Y = startY + i;
		for (int j = 0; j < width; j += 2)
		{
			point.X = startX + j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			if (j == 0 || j == width - 1) {
				if (i == 0 || i == height - 1)		//�|�Ө���
					wcout << L"��";
				else
					wcout << L"��";					//���k�ⰼ
			}
			else if (i == 0 || i == height - 1) {	//�W�U�ⰼ
				wcout << L"��";
			}

		}
	}
}

void RecordBoard::writeMsg(record tmp)
{	//�P�_�Ѻ�
	wstring tmpString;
	tmpString.insert(0, nameMap[tmp.hunter]);
	//�P�_���©M�_�l��m
	if (tmp.whosTurn == 0)
		tmpString.insert(1, BlkNum(tmp.Xpos));
	else
		tmpString.insert(1, RedNum(tmp.Xpos));
	//�P�_�e�i��h�ξ�V����
	if (tmp.deltaY > 0)
		tmpString.insert(2, L"�i");
	else if (tmp.deltaY == 0)
		tmpString.insert(2, L"��");
	else if (tmp.deltaY < 0)
		tmpString.insert(2, L"�h");
	//�P�_�ت���m
	if (tmp.whosTurn == 0)
		tmpString.insert(3, BlkNum(tmp.Xpos + tmp.deltaX));
	else
		tmpString.insert(3, RedNum(tmp.Xpos + tmp.deltaX));
	msgBoard.push_back(tmpString);
}

wstring RecordBoard::RedNum(int Xpos)
{
	if (Xpos == 1)
		return L"�E";
	else if (Xpos == 2)
		return L"�K";
	else if (Xpos == 3)
		return L"�C";
	else if (Xpos == 4)
		return L"��";
	else if (Xpos == 5)
		return L"��";
	else if (Xpos == 6)
		return L"�|";
	else if (Xpos == 7)
		return L"�T";
	else if (Xpos == 8)
		return L"�G";
	else if (Xpos == 9)
		return L"�@";
	else
		return L"";
}

wstring RecordBoard::BlkNum(int Xpos)
{
	if (Xpos == 1)
		return L"��";
	else if (Xpos == 2)
		return L"��";
	else if (Xpos == 3)
		return L"��";
	else if (Xpos == 4)
		return L"��";
	else if (Xpos == 5)
		return L"��";
	else if (Xpos == 6)
		return L"��";
	else if (Xpos == 7)
		return L"��";
	else if (Xpos == 8)
		return L"��";
	else if (Xpos == 9)
		return L"��";
	else
		return L"";
}
map<int, wstring>RecordBoard::nameMap = {
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
