#include "RecordBoard.h"
#include<Windows.h>
#include<iostream>


RecordBoard::RecordBoard()
	:startX(4),startY(1),width(27),height(31)
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
		for (int j = 0; j < width; j+=2)
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
{
	msgBoard.push_back(chessName[tmp.hunter]);
	//msgBoard.push_back(tmp.)
	if (tmp.deltaY > 0)
		msgBoard.push_back(L"�i");
	else if (tmp.deltaY == 0)
		msgBoard.push_back(L"��");
	else if (tmp.deltaY < 0)
		msgBoard.push_back(L"�h");


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
		return L"�|";
	else if (Xpos == 7)
		return L"�T";
	else if (Xpos == 8)
		return L"�G";
	else if (Xpos == 9)
		return L"�@";
}
