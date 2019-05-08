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
// �Lrecord�خ�
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
}

// �g�r���ƶivector<wstring>
void RecordBoard::writeMsg(record tmp)
{	
	wstring tmpString;
	//�P�_�ĴX�B
	tmpString.insert(0, BlkNum(recordIndex));		//BlkNum�|�Nn�নn+1������Ʀr��X
	tmpString.insert(1, L" �@");
	//�P�_���¤�
	tmp.whosTurn = (tmp.hunter < 8 && tmp.hunter > 0 ? 0 : 1);
	tmpString.insert(2, tmp.whosTurn == 0 ? L"��" : L"��");
	tmpString.insert(3, L"�G");
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

// regret �����L���F��M��
void RecordBoard::clearBoard()
{
	COORD point;
	
	point.Y = startY + 1;
	for (int i = 0; i < 10; i++) {
		point.X = startX + 3;
		point.Y++;
		for (int j = 0; j < 20; j++) {
			point.X ++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			cout << "�@";
		}
	}
}

// �L�Xrecord index �e10��
void RecordBoard::printMsg()
{
	COORD point;
	point.X = startX + 4;
	// �q1
	if (recordIndex <= 10) {
		for (int i = 0; i < recordIndex; i++) {
			point.Y = startY + i + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			wcout << msgBoard[i] << endl;
		}
	}
	else{
		int j = 0;
		for (int i = recordIndex - 10; i < recordIndex; i++) {
			point.Y = startY + j + 2;
			j++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			wcout << msgBoard[i] << endl;
		}
	}
}

void RecordBoard::regret(vector<vector<int>>& chessBoard)
{
	COORD endPoint, startPoint;
	int detailIndex = recordIndex - 1;
	endPoint.X = detailBoard[detailIndex].deltaX + detailBoard[detailIndex].Xpos;
	endPoint.Y = detailBoard[detailIndex].deltaY + detailBoard[detailIndex].Ypos;
	startPoint.X = detailBoard[detailIndex].Xpos;
	startPoint.Y = detailBoard[detailIndex].Ypos;
	chessBoard[endPoint.Y][endPoint.X] = detailBoard[detailIndex].prey;
	chessBoard[startPoint.Y][startPoint.X] = detailBoard[detailIndex].hunter;
	recordIndex--;
	detailIndex = recordIndex - 1;
	endPoint.X = detailBoard[detailIndex].deltaX + detailBoard[detailIndex].Xpos;
	endPoint.Y = detailBoard[detailIndex].deltaY + detailBoard[detailIndex].Ypos;
	startPoint.X = detailBoard[detailIndex].Xpos;
	startPoint.Y = detailBoard[detailIndex].Ypos;
	chessBoard[endPoint.Y][endPoint.X] = detailBoard[detailIndex].prey;
	chessBoard[startPoint.Y][startPoint.X] = detailBoard[detailIndex].hunter;
	recordIndex--;
	clearBoard();
	printMsg();
}

void RecordBoard::reduction(vector<vector<int>>& chessBoard)
{
}

// ��O���s�i�}�Cvector<record>
void RecordBoard::writeDetail(record tmpRecord) {
	detailBoard.push_back(tmpRecord);
}

void RecordBoard::setRecord(int x, int y, const vector<vector<int>>& chessBoard, const vector<vector<int>>& colorBoard)
{	//endPoint�q0�}�l
	COORD startPoint, enemyPoint;
	record newRecord;
	for (int i = 0; i < colorBoard.size(); i++) {
		for (int j = 0; j < colorBoard[i].size(); j++) {
			if (colorBoard[i][j] == 1) {	//��첾�ʫe����m
				startPoint.X = j;
				startPoint.Y = i;
			}
			if (colorBoard[i][j] == -2 && x == j && y == i) {	//���Y���ĤH
				enemyPoint.X = x;
				enemyPoint.Y = y;
				newRecord.prey = chessBoard[enemyPoint.Y][enemyPoint.X];
			}
		}
	}
	newRecord.Xpos = startPoint.X;
	newRecord.Ypos = startPoint.Y;
	newRecord.deltaX = x - startPoint.X;
	newRecord.deltaY = y - startPoint.Y;
	newRecord.hunter = chessBoard[startPoint.Y][startPoint.X];
	newRecord.whosTurn = (newRecord.hunter <= 7 && newRecord.hunter >= 0) ? 0 : 1;
	writeDetail(newRecord);
	writeMsg(newRecord);		//recordIndex�|+1
	printMsg();

}



wstring RecordBoard::RedNum(int Xpos)
{
	if (Xpos == 0)
		return L"�E";
	else if (Xpos == 1)
		return L"�K";
	else if (Xpos == 2)
		return L"�C";
	else if (Xpos == 3)
		return L"��";
	else if (Xpos == 4)
		return L"��";
	else if (Xpos == 5)
		return L"�|";
	else if (Xpos == 6)
		return L"�T";
	else if (Xpos == 7)
		return L"�G";
	else if (Xpos == 8)
		return L"�@";
	else
		return L"";
}

wstring RecordBoard::BlkNum(int Xpos)
{
	if (Xpos == 0)
		return L"��";
	else if (Xpos == 1)
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