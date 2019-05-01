#include "ChineseChess.h"
#include"RecordBoard.h"
#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

ChineseChess::ChineseChess()
	:gameOver(false)
{
}


ChineseChess::~ChineseChess()
{
}

void ChineseChess::gameStart(void)
{
	while (!gameOver)
	{
		if (_kbhit())
		{
			char ch = _getch();
			cout << ch << endl;
		}
	}
}
