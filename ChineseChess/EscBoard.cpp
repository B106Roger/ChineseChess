#include "EscBoard.h"
#include "ChineseChess.h"

EscBoard::EscBoard(int cursorX, int cursorY, int sizeX, int sizeY, int iniMode)
	:mode(iniMode)
{
	cursor.push_back(cursorX);
	cursor.push_back(cursorY);
	size.push_back(sizeX);
	size.push_back(sizeY);
}


EscBoard::~EscBoard()
{
}

int EscBoard::escMenu() {
	mode = 0;
	printBoard(); // 印出選單
	while (true) {
		if (_kbhit())
		{
			int ch = _getch();
			// 按下Enter鍵後
			if (ch == '\r')
			{
				int returnValue = mode;
				ChineseChess::setCursorSize(true, 0); // 歸還游標
				ChineseChess::gameBoard.printBoard();
				return returnValue;
			}
			// 按下方向鍵後
			else if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: // 上
					if (mode == 0) mode = 4;
					else mode--;
					break;
				case 80: // 下
					if (mode == 4) mode = 0;
					else mode++;
					break;
				};
				printWord(); // 更新已選取選項位置
			}
		}
	}
}

int EscBoard::escMenuReplay() {
	mode = 0;
	printBoardReplay(); // 印出選單
	while (true) {
		if (_kbhit())
		{
			int ch = _getch();
			// 按下Enter鍵後
			if (ch == '\r')
			{
				int returnValue = mode;
				ChineseChess::setCursorSize(true, 0); // 歸還游標
				ChineseChess::gameBoard.printBoard();
				return returnValue;
			}
			// 按下方向鍵後
			else if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: // 上
					if (mode == 0) mode = 2;
					else mode--;
					break;
				case 80: // 下
					if (mode == 2) mode = 0;
					else mode++;
					break;
				};
				printWordReplay(); // 更新已選取選項位置
			}
		}
	}
}

void EscBoard::printBoard() {
	ChineseChess::setCursorSize(false, 0);
	int frameWidth = size[0];
	int frameHeight = size[1];
	ChineseChess::SetColor(9, 0);
	for (int i = 0; i < frameHeight; i++) {
		ChineseChess::setCursor(cursor[0], cursor[1] + i);
		for (int j = 0; j < frameWidth; j++) {
			if (i == 0 || i == frameHeight - 1 || i % 2 == 0) // 上
			{
				if (j == 0) wcout << L"●";// 左上角
				else if (j == frameWidth - 1) wcout << L"●";// 右上角
				else wcout << L"＝";// 上方
			}
			else// 中
			{
				if (j == 0 || j == frameWidth - 1) wcout << L"∥";// 中間
				else wcout << L"　"; // 
			}
		}
	}
	ChineseChess::SetColor();
	printWord();
	// cout << ChineseChess::gameBoard.chessBoard[0][0];
}

void EscBoard::printBoardReplay() {
	ChineseChess::setCursorSize(false, 0);
	int frameWidth = size[0];
	int frameHeight = size[1] - 4;
	ChineseChess::SetColor(9, 0);
	for (int i = 0; i < frameHeight; i++) {
		ChineseChess::setCursor(cursor[0], cursor[1] + i);
		for (int j = 0; j < frameWidth; j++) {
			if (i == 0 || i == frameHeight - 1 || i % 2 == 0) // 上
			{
				if (j == 0) wcout << L"●";// 左上角
				else if (j == frameWidth - 1) wcout << L"●";// 右上角
				else wcout << L"＝";// 上方
			}
			else// 中
			{
				if (j == 0 || j == frameWidth - 1) wcout << L"∥";// 中間
				else wcout << L"　"; // 
			}
		}
	}
	ChineseChess::SetColor();
	printWordReplay();
}

void EscBoard::printWord() {
	ChineseChess::SetColor();
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 1);
	if(mode == 0) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"繼續遊戲";
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 3);
	if (mode == 1) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"重新開始";
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 5);
	if (mode == 2) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"我方投降";
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 7);
	if (mode == 3) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"儲存遊戲";
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 9);
	if (mode == 4) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"回主選單";
}

void EscBoard::printWordReplay() {
	ChineseChess::SetColor();
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 1);
	if (mode == 0) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"繼續重播";
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 3);
	if (mode == 1) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"儲存遊戲";
	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 5);
	if (mode == 2) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"回主選單";
}