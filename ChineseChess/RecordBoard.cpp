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
// 印recordBoard框框
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

//棋子移動後寫入record
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
	if (recordIndex != msgBoard.size()) {
		msgBoard.erase(msgBoard.begin() + recordIndex, msgBoard.end());
		detailBoard.erase(detailBoard.begin() + recordIndex, detailBoard.end());
	}

	writeDetail(newRecord);
	wstring firstTwo = twoWords(chessBoard, whichCase(newRecord, chessBoard), newRecord);
	//recordIndex + 1
	recordIndex++;
	msgBoard.push_back(getMsg(newRecord, firstTwo));	//recordIndex會+1
	printMsg();

}
//寫進vector<record> detailBoard
void RecordBoard::writeDetail(record tmpRecord) {
	detailBoard.push_back(tmpRecord);
}
//依據case組成msg前兩個字
wstring RecordBoard::twoWords(vector<vector<int>> chessBoard, int caseNum, record tmpRecord)
{
	wstring firstTwo;
	//case1: 棋種 + 起始直排
	if (caseNum == 1) {
		//判斷棋種
		firstTwo += nameMap[tmpRecord.hunter];
		firstTwo += L" ";
		//判斷紅黑和起始位置
		if (tmpRecord.whosTurn == 0)
			firstTwo += BlkNum(tmpRecord.Xpos);
		else
			firstTwo += RedNum(tmpRecord.Xpos);
		firstTwo += L" ";
	}
	//case2: 前/後(排序) + 棋種
	else if (caseNum == 2) {
		//判斷前後
		int anotherPos;
		for (int i = 0; i < chessBoard.size(); i++) {
			if (i != tmpRecord.Ypos && chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter)
				anotherPos = i;
		}
		if (tmpRecord.whosTurn == 0) {
			if (anotherPos > tmpRecord.Ypos)
				firstTwo += L"後 ";
			else
				firstTwo += L"前 ";
		}
		else if (tmpRecord.whosTurn == 1) {
			if (anotherPos < tmpRecord.Ypos)
				firstTwo += L"後 ";
			else
				firstTwo += L"前 ";
		}

		//判斷棋種
		firstTwo += nameMap[tmpRecord.hunter];
		firstTwo += L" ";
	}
	//case3: 排序 + 棋種
	else if (caseNum == 3) {
		//判斷前中後(3個) or 前二三四五(4 or 5個)
		int count = 0;
		for (int i = 0; i < chessBoard.size(); i++) {
			if (chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter)
				count++;
		}
		//判斷是前中後哪個
		if (count == 3) {
			int sortPos = 0;
			bool found = false;
			for (int i = 0; i < chessBoard.size() && !found; i++) {
				if (chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter) {
					sortPos++;
					if (i == tmpRecord.Ypos)
						found = true;
				}
			}
			//判斷是紅方還是黑方
			if (tmpRecord.whosTurn == 0) {		//黑方最下面是前，最上面是後
				if (sortPos == 3)
					firstTwo += L"前 ";
				else if (sortPos == 2)
					firstTwo += L"中 ";
				else if (sortPos == 1)
					firstTwo += L"後 ";
			}
			else if (tmpRecord.whosTurn == 1) {	//紅方最下面是後，最上面是前
				if (sortPos == 1)
					firstTwo += L"前 ";
				else if (sortPos == 2)
					firstTwo += L"中 ";
				else if (sortPos == 3)
					firstTwo += L"後 ";
			}
		}
		//同一直排有4或5個，判斷是前二三四五哪一個
		else if(count == 4 || count == 5){
			int sortPos = 0;
			//如果是紅方，往上到下分別是前二三四五
			if (tmpRecord.whosTurn == 1) {
				int sortPos = 0;
				bool found = false;
				for (int i = 0; i < chessBoard.size() && !found; i++) {
					if (chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter) {
						sortPos++;
						if (i == tmpRecord.Ypos)
							found = true;
					}
				}
				if (sortPos == 1)
					firstTwo += L"前 ";
				else if (sortPos == 2)
					firstTwo += L"二 ";
				else if (sortPos == 3)
					firstTwo += L"三 ";
				else if (sortPos == 4)
					firstTwo += L"四 ";
				else if (sortPos == 5)
					firstTwo += L"五 ";
			}
			//如果是黑方，從下往上算分別是前二三四五
			else if (tmpRecord.whosTurn == 0) {
				bool found = false;
				for (int i = int(chessBoard.size()) - 1; i >= 0 && !found; i--) {
					if (chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter) {
						sortPos++;
						if (i == tmpRecord.Ypos)
							found = true;
					}
				}
				if (sortPos == 1)
					firstTwo += L"前 ";
				else if (sortPos == 2)
					firstTwo += L"二 ";
				else if (sortPos == 3)
					firstTwo += L"三 ";
				else if (sortPos == 4)
					firstTwo += L"四 ";
				else if (sortPos == 5)
					firstTwo += L"五 ";
			}
		}
		//判斷棋種
		firstTwo += nameMap[tmpRecord.hunter];
		firstTwo += L" ";
	}
	//case4: 前/後 + 起始直排
	else if (caseNum == 4) {
		//判斷該排有2還是3個
		int count = 0;
		for (int i = 0; i < chessBoard.size(); i++) {
			if (chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter)
				count++;
		}
		if (count == 2) {
			//判斷前後
			int anotherPos;
			for (int i = 0; i < chessBoard.size(); i++) {
				if (i != tmpRecord.Ypos && chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter)
					anotherPos = i;
			}
			if (tmpRecord.whosTurn == 0) {
				if (anotherPos > tmpRecord.Ypos)
					firstTwo += L"後 ";
				else
					firstTwo += L"前 ";
			}
			else if (tmpRecord.whosTurn == 1) {
				if (anotherPos < tmpRecord.Ypos)
					firstTwo += L"後 ";
				else
					firstTwo += L"前 ";
			}
		}
		else if (count == 3) {
			//找在第幾個位置
			int sortPos = 0;
			bool found = false;
			for (int i = 0; i < chessBoard.size() && !found; i++) {
				if (chessBoard[i][tmpRecord.Xpos] == tmpRecord.hunter) {
					sortPos++;
					if (i == tmpRecord.Ypos)
						found = true;
				}
			}
			//判斷是紅方還是黑方
			if (tmpRecord.whosTurn == 0) {		//黑方最下面是前，最上面是後
				if (sortPos == 3)
					firstTwo += L"前 ";
				else if (sortPos == 2)
					firstTwo += L"中 ";
				else if (sortPos == 1)
					firstTwo += L"後 ";
			}
			else if (tmpRecord.whosTurn == 1) {	//紅方最下面是後，最上面是前
				if (sortPos == 1)
					firstTwo += L"前 ";
				else if (sortPos == 2)
					firstTwo += L"中 ";
				else if (sortPos == 3)
					firstTwo += L"後 ";
			}
		}
		//判斷紅黑和起始位置
		if (tmpRecord.whosTurn == 0)
			firstTwo += BlkNum(tmpRecord.Xpos);
		else
			firstTwo += RedNum(tmpRecord.Xpos);
		firstTwo += L" ";
	}
	return firstTwo;
}
//判斷是中式記譜法哪一種case
int RecordBoard::whichCase(record tmpRecord, vector<vector<int>> chessBoard)
{	//case1: 該行只有一個該棋種  case2: 該行有兩個同樣的該棋種  case3: 該行有兩個以上該棋種，且其他相同棋種分別在不同行  case4: 在兩行有兩個以上該棋種
	//如果是兵或卒，有可能是case1、3、4
	if (tmpRecord.hunter == 7 || tmpRecord.hunter == 14) {
		int count = 0;
		for (int i = 0; i < chessBoard.size(); i++) {
			for (int j = 0; j < chessBoard[i].size(); j++) {
				if (chessBoard[i][j] == tmpRecord.hunter && j == tmpRecord.Xpos)
					count++;
			}
		}
		//該行只有一個兵或卒--> case1
		if (count == 1)
			return 1;
		//該行有兩或三個兵或卒 --> case2或3或4 (檢查其他排有沒有也是兩個一樣的棋種在同一排)
		else if (count == 2 || count == 3) {
			//找該棋種分別在棋盤上的哪幾行
			vector<int> countOther(9, 0);
			for (int i = 0; i < chessBoard.size(); i++) {
				for (int j = 0; j < chessBoard[i].size(); j++) {
					if (chessBoard[i][j] == tmpRecord.hunter && j != tmpRecord.Xpos)
						countOther[j]++;
				}
			}
			int caseNum = count;
			//如果其他行有兩個以上同行 --> case4  (不論count = 2 or 3)
			for (int i = 0; i < countOther.size(); i++) {
				if (countOther[i] >= 2)
					caseNum = 4;
			}
			//如果其他兵卒都不同行 --> case2 or 3 (count == caseNum)
			return caseNum;
		}
		//該行有4或5個兵卒 --> case3
		else
			return 3;
	}
	//否則判斷是case1或2
	else {
		int count = 0;
		for (int i = 0; i < chessBoard.size(); i++) {
			for (int j = 0; j < chessBoard[i].size(); j++) {
				if (chessBoard[i][j] == tmpRecord.hunter && j == tmpRecord.Xpos)
					count++;
			}
		}
		if (count == 1)
			return 1;
		else
			return 2;
	}
	return 0;
}
//寫中式記譜法進vector<wstring> msgBoard
wstring RecordBoard::getMsg(record tmp, wstring firstTwo)
{	
	wstring tmpString;
	//判斷第幾步
	tmpString = numIntToStr(recordIndex);
	tmpString += L" ";
	//判斷紅黑方
	tmp.whosTurn = (tmp.hunter < 8 && tmp.hunter > 0 ? 0 : 1);
	tmpString += tmp.whosTurn == 0 ? L"黑" : L"紅";
	tmpString += L"：";
	//套上前兩個字
	tmpString += firstTwo;
	if (tmp.whosTurn == 0) {				//�¤詹�U���O�i�A���W���O�h�A�G���M������}�P�_
		if (tmp.deltaY > 0)
			tmpString += L"進";
		else if (tmp.deltaY == 0)
			tmpString += L"平";
		else if (tmp.deltaY < 0)
			tmpString += L"退";
		tmpString += L" ";
	}
	else {
		if (tmp.deltaY < 0)
			tmpString += L"進";
		else if (tmp.deltaY == 0)
			tmpString += L"平";
		else if (tmp.deltaY > 0)
			tmpString += L"退";
		tmpString += L" ";
	}

	//判斷目的位置
	if (tmp.whosTurn == 0)
		tmpString += BlkNum(tmp.Xpos + tmp.deltaX);
	else
		tmpString += RedNum(tmp.Xpos + tmp.deltaX);
	//將組合完成的紀錄存入msgBoard
	return tmpString;
}
//將數字轉成全形字串
wstring RecordBoard::numIntToStr(int num)
{
	vector<int> digits;
	wstring String;
	while (num / 10 != 0) {
		digits.push_back(num % 10);
		num /= 10;
	}
	digits.push_back(num);
	for (int i = int(digits.size()) - 1; i >= 0; i--) {
		String += bigNum(digits[i]);
	}
	return String;
}
//印出中式記譜法
void RecordBoard::printMsg()
{
	COORD point;
	point.X = startX + 4;
	//小於10筆資料
	if (recordIndex <= 10) {
		for (int i = 0; i < recordIndex; i++) {
			point.Y = startY + i + 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			for (int j = 0; j < msgBoard[i].size(); j++) {
				//如果是'紅'字就印成紅色
				if (msgBoard[i][j] == L'紅') {
					ChineseChess::SetColor(4, 0);
					wcout << msgBoard[i][j];
				}
				else {
					ChineseChess::SetColor();
					wcout << msgBoard[i][j];
				}
			}

		}
	}
	//大於10筆資料就印最新10筆
	else{
		int j = 0;
		for (int i = recordIndex - 10; i < recordIndex; i++) {
			point.Y = startY + j + 2;
			j++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			for (int j = 0; j < msgBoard[i].size(); j++) {
				//如果是'紅'字就印成紅色
				if (msgBoard[i][j] == L'紅') {
					ChineseChess::SetColor(4, 0);
					wcout << msgBoard[i][j];
				}
				else {
					ChineseChess::SetColor();
					wcout << msgBoard[i][j];
				}
			}
		}
	}
}
//重頭產生中世記譜法
void RecordBoard::rebaseRecord()
{
	vector<vector<int>> chessBoard = ChineseChess::gameBoard.chessBoard;
	recordIndex = int(detailBoard.size()) - 1;
	for (; recordIndex >= 0; recordIndex--)
	{
		record & tmpRec = detailBoard[recordIndex];
		chessBoard[tmpRec.Ypos][tmpRec.Xpos] = chessBoard[tmpRec.Ypos + tmpRec.deltaY][tmpRec.Xpos + tmpRec.deltaX];
		chessBoard[tmpRec.Ypos + tmpRec.deltaY][tmpRec.Xpos + tmpRec.deltaX] = tmpRec.prey;
		wstring firstTwo = twoWords(chessBoard, whichCase(tmpRec, chessBoard), tmpRec);
		++recordIndex;
		msgBoard.insert(msgBoard.begin(), getMsg(tmpRec, firstTwo));
		--recordIndex;
	}
	recordIndex = int(detailBoard.size());
	return;
}


//悔棋(2步)
bool RecordBoard::regret(vector<vector<int>>& chessBoard)
{	
	if (recordIndex < 2)
		return false;
	else {
		regretSingle(chessBoard);
		regretSingle(chessBoard);
		clearBoard();
		printMsg();
		return true;
	}
}
//悔棋(1步)
bool RecordBoard::regretSingle(vector<vector<int>>& chessBoard)
{
	if (recordIndex == 0)
		return false;
	else {
		COORD endPoint, startPoint;
		int detailIndex = recordIndex - 1;
		endPoint.X = detailBoard[detailIndex].deltaX + detailBoard[detailIndex].Xpos;
		endPoint.Y = detailBoard[detailIndex].deltaY + detailBoard[detailIndex].Ypos;
		startPoint.X = detailBoard[detailIndex].Xpos;
		startPoint.Y = detailBoard[detailIndex].Ypos;
		chessBoard[endPoint.Y][endPoint.X] = detailBoard[detailIndex].prey;
		chessBoard[startPoint.Y][startPoint.X] = detailBoard[detailIndex].hunter;
		recordIndex--;
		return true;
	}
}

// regret 後清除recordBoard
void RecordBoard::clearBoard()
{
	COORD point;
	ChineseChess::SetColor();
	point.Y = startY + 1;
	for (int i = 0; i < 10; i++) {
		point.X = startX + 3;
		point.Y++;
		for (int j = 0; j < 20; j++) {
			point.X++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			cout << "　";
		}
	}
}


//還原(2步)
bool RecordBoard::reduction(vector<vector<int>>& chessBoard)
{	
	if (recordIndex == detailBoard.size())
		return false;
	else {
		reductionSingle(chessBoard);
		reductionSingle(chessBoard);
		printMsg();
		return true;
	}
}
//還原(1步)
bool RecordBoard::reductionSingle(vector<vector<int>>& chessBoard)
{
	if (recordIndex == detailBoard.size())
		return false;
	else {
		COORD endPoint, startPoint;
		recordIndex++;
		int detailIndex = recordIndex - 1;
		endPoint.X = detailBoard[detailIndex].deltaX + detailBoard[detailIndex].Xpos;
		endPoint.Y = detailBoard[detailIndex].deltaY + detailBoard[detailIndex].Ypos;
		startPoint.X = detailBoard[detailIndex].Xpos;
		startPoint.Y = detailBoard[detailIndex].Ypos;
		chessBoard[endPoint.Y][endPoint.X] = detailBoard[detailIndex].hunter;
		chessBoard[startPoint.Y][startPoint.X] = 0;
		return true;
	}
}
//清空detailBoard, msgBoard, recordIndex歸零
void RecordBoard::resetRecordBoard()
{
	detailBoard.clear();
	msgBoard.clear();
	recordIndex = 0;
}

void RecordBoard::saveRecord(string fileName, int finished) {
	size_t index = fileName.find(".txt");
	if (index != string::npos) fileName.insert(index, "Rec");

	fstream outputFile(fileName, ios::out);
	outputFile << finished << " " << endl;
	for (int i = 0; i < recordIndex; i++) {
		outputFile << detailBoard[i].hunter << " "
			<< detailBoard[i].Xpos << " "
			<< detailBoard[i].Ypos << " "
			<< detailBoard[i].whosTurn << " "
			<< detailBoard[i].deltaX << " "
			<< detailBoard[i].deltaY << " "
			<< detailBoard[i].prey << " " << endl;
	}

	outputFile.close();

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

wstring RecordBoard::bigNum(int num)
{
	if (num == 1)
		return L"１";
	else if (num == 2)
		return L"２";
	else if (num == 3)
		return L"３";
	else if (num == 4)
		return L"４";
	else if (num == 5)
		return L"５";
	else if (num == 6)
		return L"６";
	else if (num == 7)
		return L"７";
	else if (num == 8)
		return L"８";
	else if (num == 9)
		return L"９";
	else if (num == 0)
		return L"０";
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

