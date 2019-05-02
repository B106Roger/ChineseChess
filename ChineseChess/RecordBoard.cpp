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
	for (int i = 0; i < height; i++)
	{
		point.X = startX;
		point.Y = startY +    i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
		for (int j = 0; j < width; j++)
		{

		}
	}
}
