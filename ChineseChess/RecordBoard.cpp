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
}

void RecordBoard::writeMsg(record tmp)
{	
	//record�����ޭ�+1
	recordIndex++;

	wstring tmpString;
	//�P�_�ĴX�B
	tmpString = numIntToStr(recordIndex);
	tmpString += L" ";
	//�P�_���¤�
	tmp.whosTurn = (tmp.hunter < 8 && tmp.hunter > 0 ? 0 : 1);
	tmpString += tmp.whosTurn == 0 ? L"��" : L"��";
	tmpString += L"�G";
	//�P�_�Ѻ�
	tmpString += nameMap[tmp.hunter];
	tmpString += L" ";
	//�P�_���©M�_�l��m
	if (tmp.whosTurn == 0)
		tmpString += BlkNum(tmp.Xpos);
	else
		tmpString += RedNum(tmp.Xpos);
	tmpString += L" ";
	//�P�_�e�i��h�ξ�V����
	if (tmp.whosTurn == 0) {				//�¤詹�U���O�i�A���W���O�h�A�G���M������}�P�_
		if (tmp.deltaY > 0)
			tmpString += L"�i";
		else if (tmp.deltaY == 0)
			tmpString += L"��";
		else if (tmp.deltaY < 0)
			tmpString += L"�h";
		tmpString += L" ";
	}
	else {
		if (tmp.deltaY < 0)
			tmpString += L"�i";
		else if (tmp.deltaY == 0)
			tmpString += L"��";
		else if (tmp.deltaY > 0)
			tmpString += L"�h";
		tmpString += L" ";
	}

	//�P�_�ت���m
	if (tmp.whosTurn == 0)
		tmpString += BlkNum(tmp.Xpos + tmp.deltaX);
	else
		tmpString += RedNum(tmp.Xpos + tmp.deltaX);
	//�N�զX�����������s�JmsgBoard
	msgBoard.push_back(tmpString);

}

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

wstring RecordBoard::numIntToStr(int num)
{
	vector<int> digits;
	wstring String;
	while (num / 10 != 0) {
		digits.push_back(num % 10);
		num /= 10;
	}
	digits.push_back(num);
	for (int i = digits.size() - 1; i >= 0; i--) {
		String += bigNum(digits[i]);
	}
	return String;
}

void RecordBoard::printMsg()
{
	COORD point;
	point.X = startX + 4;
	if (recordIndex <= 10) {
		for (int i = 0; i < recordIndex; i++) {
			point.Y = startY + i + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			for (int j = 0; j < msgBoard[i].size(); j++) {
				//�p�G�O����U�ѴN�N"��"�r��������
				if (msgBoard[i][j] == L'��') {
					SetColor(12);
					wcout << msgBoard[i][j];
				}
				else {
					SetColor(7);
					wcout << msgBoard[i][j];
				}
			}

		}
	}
	else{
		int j = 0;
		for (int i = recordIndex - 10; i < recordIndex; i++) {
			point.Y = startY + j + 2;
			j++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			for (int j = 0; j < msgBoard[i].size(); j++) {
				//�p�G�O����U�ѴN�N"��"�r��������
				if (msgBoard[i][j] == L'��') {
					SetColor(12);
					wcout << msgBoard[i][j];
				}
				else {
					SetColor(7);
					wcout << msgBoard[i][j];
				}
			}
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
	COORD endPoint, startPoint;
	recordIndex++;
	int detailIndex = recordIndex - 1;
	endPoint.X = detailBoard[detailIndex].deltaX + detailBoard[detailIndex].Xpos;
	endPoint.Y = detailBoard[detailIndex].deltaY + detailBoard[detailIndex].Ypos;
	startPoint.X = detailBoard[detailIndex].Xpos;
	startPoint.Y = detailBoard[detailIndex].Ypos;
	chessBoard[endPoint.Y][endPoint.X] = detailBoard[detailIndex].hunter;
	chessBoard[startPoint.Y][startPoint.X] = 0;
	recordIndex++;
	detailIndex = recordIndex - 1;
	endPoint.X = detailBoard[detailIndex].deltaX + detailBoard[detailIndex].Xpos;
	endPoint.Y = detailBoard[detailIndex].deltaY + detailBoard[detailIndex].Ypos;
	startPoint.X = detailBoard[detailIndex].Xpos;
	startPoint.Y = detailBoard[detailIndex].Ypos;
	chessBoard[endPoint.Y][endPoint.X] = detailBoard[detailIndex].hunter;
	chessBoard[startPoint.Y][startPoint.X] = 0;
	printMsg();
}

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
	if (recordIndex != msgBoard.size()) {
		msgBoard.erase(msgBoard.begin() + recordIndex, msgBoard.end());
		detailBoard.erase(detailBoard.begin() + recordIndex, detailBoard.end());
	}

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

wstring RecordBoard::bigNum(int num)
{
	if (num == 1)
		return L"��";
	else if (num == 2)
		return L"��";
	else if (num == 3)
		return L"��";
	else if (num == 4)
		return L"��";
	else if (num == 5)
		return L"��";
	else if (num == 6)
		return L"��";
	else if (num == 7)
		return L"��";
	else if (num == 8)
		return L"��";
	else if (num == 9)
		return L"��";
	else if (num == 0)
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
void RecordBoard::SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}