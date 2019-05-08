#include "RecordBoard.h"
#include "ChineseChess.h"
#include<Windows.h>
#include<iostream>


RecordBoard::RecordBoard()
	:startX(4), startY(1), width(29), height(31), recordIndex(0)		//從(4,1)開始畫到(30, 32)
{
}

RecordBoard::~RecordBoard()
{
}
// �Lrecord�خ�
void RecordBoard::printBoard()
{
	COORD point;
	//印第一列
	point.Y = startY;
	point.X = startX;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	wcout << L"●－－－戰　況　顯　示－－－●";
	//印第二列到最後一列
	for (int i = 1; i < height; i++)
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
			else if(i == height - 1)				//下側
				wcout << L"＝";
		}
	}
}

// �g�r���ƶivector<wstring>
void RecordBoard::writeMsg(record tmp)
{	
	wstring tmpString;
	//判斷第幾步
	tmpString.insert(0, BlkNum(recordIndex));		//BlkNum會將n轉成n+1的中文數字輸出
	tmpString.insert(1, L" 　");
	//判斷紅黑方
	tmp.whosTurn = (tmp.hunter < 8 && tmp.hunter > 0 ? 0 : 1);
	tmpString.insert(2, tmp.whosTurn == 0 ? L"黑" : L"紅");
	tmpString.insert(3, L"：");
	//判斷棋種
	tmpString.insert(4, nameMap[tmp.hunter]);
	tmpString.insert(5, L" ");
	//判斷紅黑和起始位置
	if (tmp.whosTurn == 0)
		tmpString.insert(6, BlkNum(tmp.Xpos));
	else
		tmpString.insert(6, RedNum(tmp.Xpos));
	tmpString.insert(7, L" ");
	//判斷前進後退或橫向移動
	if (tmp.whosTurn == 0) {				//黑方往下走是進，往上走是退，故須和紅方分開判斷
		if (tmp.deltaY > 0)
			tmpString.insert(8, L"進");
		else if (tmp.deltaY == 0)
			tmpString.insert(8, L"平");
		else if (tmp.deltaY < 0)
			tmpString.insert(8, L"退");
		tmpString.insert(9, L" ");
	}
	else {
		if (tmp.deltaY < 0)
			tmpString.insert(8, L"進");
		else if (tmp.deltaY == 0)
			tmpString.insert(8, L"平");
		else if (tmp.deltaY > 0)
			tmpString.insert(8, L"退");
		tmpString.insert(9, L" ");
	}

	//判斷目的位置
	if (tmp.whosTurn == 0)
		tmpString.insert(10, BlkNum(tmp.Xpos + tmp.deltaX));
	else
		tmpString.insert(10, RedNum(tmp.Xpos + tmp.deltaX));
	//將組合完成的紀錄存入msgBoard
	msgBoard.push_back(tmpString);
	//record的索引值在存入後+1
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
			cout << "　";
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
{	//endPoint從0開始
	COORD startPoint, enemyPoint;
	record newRecord;
	for (int i = 0; i < colorBoard.size(); i++) {
		for (int j = 0; j < colorBoard[i].size(); j++) {
			if (colorBoard[i][j] == 1) {	//找到移動前的位置
				startPoint.X = j;
				startPoint.Y = i;
			}
			if (colorBoard[i][j] == -2 && x == j && y == i) {	//有吃掉敵人
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
	writeMsg(newRecord);		//recordIndex會+1
	printMsg();

}



wstring RecordBoard::RedNum(int Xpos)
{
	if (Xpos == 0)
		return L"九";
	else if (Xpos == 1)
		return L"八";
	else if (Xpos == 2)
		return L"七";
	else if (Xpos == 3)
		return L"六";
	else if (Xpos == 4)
		return L"五";
	else if (Xpos == 5)
		return L"四";
	else if (Xpos == 6)
		return L"三";
	else if (Xpos == 7)
		return L"二";
	else if (Xpos == 8)
		return L"一";
	else
		return L"";
}

wstring RecordBoard::BlkNum(int Xpos)
{
	if (Xpos == 0)
		return L"１";
	else if (Xpos == 1)
		return L"２";
	else if (Xpos == 2)
		return L"３";
	else if (Xpos == 3)
		return L"４";
	else if (Xpos == 4)
		return L"５";
	else if (Xpos == 5)
		return L"６";
	else if (Xpos == 6)
		return L"７";
	else if (Xpos == 7)
		return L"８";
	else if (Xpos == 8)
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

void RecordBoard::saveRecord(string fileName, int finished) {
	size_t index = fileName.find(".txt");
	if (index != string::npos) fileName.insert(index, "Rec");
	
	fstream outputFile(fileName, ios::out);
	outputFile << finished << " ";
	for (int i = 0; i < detailBoard.size(); i++) {
		outputFile << detailBoard[i].hunter << " " 
			<< detailBoard[i].Xpos << " " 
			<< detailBoard[i].Ypos << " " 
			<< detailBoard[i].whosTurn << " " 
			<< detailBoard[i].deltaX << " " 
			<< detailBoard[i].deltaY << " " 
			<< detailBoard[i].prey << " ";
	}

	outputFile.close();
}