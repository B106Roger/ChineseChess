#include "HintBoard.h"
#include "ChineseChess.h" // 必須在.cpp檔include
#include "Chess.h"
/*HintBoard::HintBoard()
{
	//cursor.push_back(cursorX); cursor.push_back(cursorY);
	//size.push_back(sizeX); size.push_back(sizeY);
	//lowerBoardCursor.push_back(cursorX); lowerBoardCursor.push_back((cursorY + sizeY * 2 / 3));
	//lowerBoardSize.push_back(sizeX); lowerBoardSize.push_back(sizeY / 3);
}*/

HintBoard::HintBoard(int cursorX, int cursorY, int sizeX, int sizeY)
{
	cursor.push_back(cursorX); cursor.push_back(cursorY);
	size.push_back(sizeX); size.push_back(sizeY);
	lowerBoardCursor.push_back(cursorX); lowerBoardCursor.push_back((cursorY + sizeY * 3 / 5));
	lowerBoardSize.push_back(sizeX); lowerBoardSize.push_back(sizeY * 2 / 5);
}


HintBoard::~HintBoard()
{
}


void HintBoard::printHint1(int order) {
	if (order == 0) {
		ChineseChess::setCursor(cursor[0] + 4, cursor[1] + 4); // 左跳兩格，下跳兩格
		ChineseChess::SetColor(9, 0);
		wcout << L"現在輪到　";
		ChineseChess::SetColor(8, 0);
		wcout << L"黑色方　";
		ChineseChess::SetColor(9, 0);
		wcout << L"下棋";
	}
	else if(order == 1){
		ChineseChess::setCursor(cursor[0] + 4, cursor[1] + 4);// 左跳兩格，下跳兩格
		ChineseChess::SetColor(9, 0);
		wcout << L"現在輪到　";
		ChineseChess::SetColor(4, 0);
		wcout << L"紅色方　";
		ChineseChess::SetColor(9, 0);
		wcout << L"下棋";
	}
	ChineseChess::SetColor();
}


void HintBoard::printHint2(int order, int chessIndex) {
	if (order == 0) {
		ChineseChess::setCursor(cursor[0] + 8, cursor[1]+8);
		ChineseChess::SetColor(9, 0);
		wcout << L"您選擇了　　";
		ChineseChess::SetColor(8, 0);
		wcout << Chess::chessName[chessIndex];

	}
	else if (order == 1) {
		ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 8);
		ChineseChess::SetColor(9, 0);
		wcout << L"您選擇了　　";
		ChineseChess::SetColor(4, 0);
		wcout << Chess::chessName[chessIndex];
		
	}
	ChineseChess::SetColor();
}

void HintBoard::hideHint2() {
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 8);
	ChineseChess::SetColor(9, 0);
	wcout << L"　　　　　　　";
}

void HintBoard::printHint3(int order) {
	if (order == 0) {
		ChineseChess::SetColor(0, 8); // 黑字灰底
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 12);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 13);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 14);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 15);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 16);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";

		ChineseChess::SetColor(7, 0); // 白字黑底
		ChineseChess::setCursor(cursor[0] + 10, cursor[1] + 14);
		wcout << L"　　　　　被將軍　！";

		ChineseChess::SetColor(8, 0); // 灰字黑底
		ChineseChess::setCursor(cursor[0] + 10, cursor[1] + 14);
		wcout << L"　　黑方";
		
		ChineseChess::SetColor(7, 0); // 白字黑底
		ChineseChess::setCursor(cursor[0] + 10, cursor[1] + 14);
		wcout << L"！";


	}
	else if (order == 1) {
		
		ChineseChess::SetColor(0, 4); // 黑字紅底
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 12);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 13);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 14);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 15);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + 16);
		for (int i = 0; i < size[0] - 2; i++) wcout << L"　";

		ChineseChess::SetColor(7, 0); // 白字黑底
		ChineseChess::setCursor(cursor[0] + 10, cursor[1] + 14);
		wcout << L"　　　　　被將軍　！";

		ChineseChess::SetColor(4, 0); // 紅字黑底
		ChineseChess::setCursor(cursor[0] + 10, cursor[1] + 14);
		wcout << L"　　紅方";

		ChineseChess::SetColor(7, 0); // 白字黑底
		ChineseChess::setCursor(cursor[0] + 10, cursor[1] + 14);
		wcout << L"！";
	}
	ChineseChess::SetColor();
}

void HintBoard::hideHint3() {
	for (int i = 12; i <= 16; i++) {
		ChineseChess::setCursor(cursor[0] + 2, cursor[1] + i);
		for (int j = 0; j < size[0] - 2; j++) wcout << L"　";
	}
}

void HintBoard::printLowerBoard() {
	int frameWidth = lowerBoardSize[0];
	int frameHeight = lowerBoardSize[1];
	// cout << lowerBoardCursor[1] << endl;
	ChineseChess::SetColor();
	for (int i = 0; i < frameHeight; i++) {
		ChineseChess::setCursor(lowerBoardCursor[0], lowerBoardCursor[1] + i);
		for (int j = 0; j < frameWidth; j++) {
			if (i == 0) // 上
			{
				if (j == 0 || j == frameWidth - 1) // 左上角
					wcout << L"●";
				else // 上方
					wcout << L"＝";
			}
			else if (i == frameHeight - 1) // 下
			{
				//if (j == 0 || j == frameWidth - 1) // 左下角
				//	wcout << L"●";
				//else // 下方
				//	wcout << L"＝";
			}
			else // 中
			{
				ChineseChess::setCursor(lowerBoardCursor[0] + 4, lowerBoardCursor[1] + i);
				if (i == 2)      wcout << L"ＥＳＣ選單　　＜悔棋　　＞還原";
				else if (i == 4)  wcout << L"　　　ＥＮＴＥＲ　　選取棋子";
				else if (i == 6)  wcout << L"　　　　　↑　　　　　　　　　";
				else if (i == 8)  wcout << L"　　　　←　→　　方向鍵控制游標";
				else if (i == 10)  wcout << L"　　　　　↓　　　　　　　　　";
				break;
			}
		}
	}
}

void HintBoard::printBoard() {

	int frameWidth = size[0];
	int frameHeight = size[1];
	ChineseChess::SetColor();
	for (int i = 0; i < frameHeight; i++) {
		ChineseChess::setCursor(cursor[0], cursor[1] + i);
		for (int j = 0; j < frameWidth; j++) {
			if (i == 0) // 上
			{
				if (j == 0) // 左上角
				{
					wcout << L"●";
				}
				else if (j == frameWidth - 1) // 右上角
				{
					wcout << L"●";
				}
				else // 上方
				{
					wcout << L"＝";
				}
			}
			else if (i == frameHeight - 1) // 下
			{
				if (j == 0) // 左下角
				{
					wcout << L"●";
				}
				else if (j == frameWidth - 1) // 右下角
				{
					wcout << L"●";
				}
				else // 下方
				{
					wcout << L"＝";
				}
			}
			else // 中
			{
				if (j == 0 || j == frameWidth - 1) // 中間
				{
					wcout << L"∥";
				}
				else // 
				{
					wcout << L"　";
				}
			}
		}
	}
	printLowerBoard();
	// printHint1(0);
	// printHint2(0, 5);
	// hideHint2();
	// printHint3(0);
	// hideHint3();
}

int HintBoard::winMenu(int order) {
	return winBoard.winMenu(order);
};