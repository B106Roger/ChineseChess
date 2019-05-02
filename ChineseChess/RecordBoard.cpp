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
