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
				if (i == 0 || i == height - 1)		//四個角落
					wcout << L"●";
				else
					wcout << L"∥";					//左右兩側
			}
			else if (i == 0 || i == height - 1) {	//上下兩側
				wcout << L"＝";
			}

		}
	}
}

void RecordBoard::writeMsg(record tmp)
{
	msgBoard.push_back(chessName[tmp.hunter]);
	//msgBoard.push_back(tmp.)
	if (tmp.deltaY > 0)
		msgBoard.push_back(L"進");
	else if (tmp.deltaY == 0)
		msgBoard.push_back(L"平");
	else if (tmp.deltaY < 0)
		msgBoard.push_back(L"退");


}

wstring RecordBoard::RedNum(int Xpos)
{
	if (Xpos == 1)
		return L"九";
	else if (Xpos == 2)
		return L"八";
	else if (Xpos == 3)
		return L"七";
	else if (Xpos == 4)
		return L"六";
	else if (Xpos == 5)
		return L"五";
	else if (Xpos == 6)
		return L"四";
	else if (Xpos == 7)
		return L"三";
	else if (Xpos == 8)
		return L"二";
	else if (Xpos == 9)
		return L"一";
}

wstring RecordBoard::BlkNum(int Xpos)
{
	if (Xpos == 1)
		return L"１";
	else if (Xpos == 2)
		return L"２";
	else if (Xpos == 3)
		return L"３";
	else if (Xpos == 4)
		return L"４";
	else if (Xpos == 5)
		return L"５";
	else if (Xpos == 6)
		return L"四";
	else if (Xpos == 7)
		return L"三";
	else if (Xpos == 8)
		return L"二";
	else if (Xpos == 9)
		return L"一";
}
