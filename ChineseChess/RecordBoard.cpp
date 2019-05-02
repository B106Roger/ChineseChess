#include "RecordBoard.h"
#include<Windows.h>
#include<iostream>


RecordBoard::RecordBoard()
	:startX(3),startY(3),width(20),height(20)
{
}


RecordBoard::~RecordBoard()
{
}

void RecordBoard::printBoard()
{
	COORD point;
	for (int i = 0; i < 34; i++)
	{
		point.X = startX;
		point.Y = startY +    i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
		/*for (int j = 0; j < 40; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					wcout << L"ùÝ ";
				}
			}
		}*/
		if (i == 0)
		{
			wcout << L"ùÝ ùù ";
			wcout.width(30);
			wcout << L"   ¾Ô   ªp   Åã   ¥Ü ";
			wcout << L" ùù ùß";
		}
		else if (i == 35)
		{

		}
	}
}
