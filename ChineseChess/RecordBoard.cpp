#include "RecordBoard.h"
#include<Windows.h>
#include<iostream>


RecordBoard::RecordBoard()
	:startX(4), startY(1), width(29), height(31), recordIndex(0)		//�q(4,1)�}�l�e��(30, 32)
{
}


RecordBoard::~RecordBoard()
{
}

void RecordBoard::printBoard()
{
	COORD point;
	//�L�Ĥ@�C
	point.Y = startY;
	point.X = startX;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	wcout << L"���ССоԡ@�p�@��@�ܡССС�";
	//�L�ĤG�C��̫�@�C
	for (int i = 1; i < height; i++)
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
			else if(i == height - 1)				//�U��
				wcout << L"��";
		}
	}
	record test1, test2;
	test1.hunter = 2;
	test1.deltaX = 1;
	test1.deltaY = 1;
	test1.Xpos = 5;
	test1.Ypos = 2;
	writeMsg(test1);
	test2.hunter = 12;
	test2.deltaX = 1;
	test2.deltaY = -2;
	test2.Xpos = 2;
	test2.Ypos = 10;
	writeMsg(test2);
	printMsg();
}

void RecordBoard::writeMsg(record tmp)
{	
	wstring tmpString;
	//�P�_�ĴX�B
	tmpString.insert(0, BlkNum(recordIndex + 1));
	tmpString.insert(1, L" �@");
	//�P�_���¤�
	tmp.whosTurn = (tmp.hunter < 8 && tmp.hunter > 0 ? 0 : 1);
	tmpString.insert(2, tmp.whosTurn == 0 ? L"��" : L"��");
	tmpString.insert(3, L" ");
	//�P�_�Ѻ�
	tmpString.insert(4, nameMap[tmp.hunter]);
	tmpString.insert(5, L" ");
	//�P�_���©M�_�l��m
	if (tmp.whosTurn == 0)
		tmpString.insert(6, BlkNum(tmp.Xpos));
	else
		tmpString.insert(6, RedNum(tmp.Xpos));
	tmpString.insert(7, L" ");
	//�P�_�e�i��h�ξ�V����
	if (tmp.whosTurn == 0) {				//�¤詹�U���O�i�A���W���O�h�A�G���M������}�P�_
		if (tmp.deltaY > 0)
			tmpString.insert(8, L"�i");
		else if (tmp.deltaY == 0)
			tmpString.insert(8, L"��");
		else if (tmp.deltaY < 0)
			tmpString.insert(8, L"�h");
		tmpString.insert(9, L" ");
	}
	else {
		if (tmp.deltaY < 0)
			tmpString.insert(8, L"�i");
		else if (tmp.deltaY == 0)
			tmpString.insert(8, L"��");
		else if (tmp.deltaY > 0)
			tmpString.insert(8, L"�h");
		tmpString.insert(9, L" ");
	}

	//�P�_�ت���m
	if (tmp.whosTurn == 0)
		tmpString.insert(10, BlkNum(tmp.Xpos + tmp.deltaX));
	else
		tmpString.insert(10, RedNum(tmp.Xpos + tmp.deltaX));
	//�N�զX�����������s�JmsgBoard
	msgBoard.push_back(tmpString);
	//record�����ޭȦb�s�J��+1
	recordIndex++;
}

void RecordBoard::printMsg()
{
	COORD point;
	point.X = startX + 4;
	for (int i = 0; i < recordIndex; i++) {
		point.Y = startY + i + 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
		wcout << msgBoard[i] << endl;
	}
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