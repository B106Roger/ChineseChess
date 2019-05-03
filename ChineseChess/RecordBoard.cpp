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
{	//判斷棋種
	wstring tmpString;
	tmpString.insert(0, nameMap[tmp.hunter]);
	//判斷紅黑和起始位置
	if (tmp.whosTurn == 0)
		tmpString.insert(1, BlkNum(tmp.Xpos));
	else
		tmpString.insert(1, RedNum(tmp.Xpos));
	//判斷前進後退或橫向移動
	if (tmp.deltaY > 0)
		tmpString.insert(2, L"進");
	else if (tmp.deltaY == 0)
		tmpString.insert(2, L"平");
	else if (tmp.deltaY < 0)
		tmpString.insert(2, L"退");
	//判斷目的位置
	if (tmp.whosTurn == 0)
		tmpString.insert(3, BlkNum(tmp.Xpos + tmp.deltaX));
	else
		tmpString.insert(3, RedNum(tmp.Xpos + tmp.deltaX));
	msgBoard.push_back(tmpString);
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
	else
		return L"";
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
		return L"６";
	else if (Xpos == 7)
		return L"７";
	else if (Xpos == 8)
		return L"８";
	else if (Xpos == 9)
		return L"９";
	else
		return L"";
}
map<int, wstring>RecordBoard::nameMap = {
	pair<int,wstring>(1,L"將"),
	pair<int,wstring>(2,L"士"),
	pair<int,wstring>(3,L"象"),
	pair<int,wstring>(4,L"車"),
	pair<int,wstring>(5,L"馬"),
	pair<int,wstring>(6,L"包"),
	pair<int,wstring>(7,L"卒"),
	pair<int,wstring>(8,L"帥"),
	pair<int,wstring>(9,L"仕"),
	pair<int,wstring>(10,L"相"),
	pair<int,wstring>(11,L"車"),
	pair<int,wstring>(12,L"傌"),
	pair<int,wstring>(13,L"炮"),
	pair<int,wstring>(14,L"兵"),
};
