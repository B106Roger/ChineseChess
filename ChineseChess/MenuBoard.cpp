#include "MenuBoard.h"
#include"ChineseChess.h"


MenuBoard::MenuBoard(int cursorX, int cursorY, int arg_width, int arg_height, int iniMode)
{
	cursor.push_back(cursorX);
	cursor.push_back(cursorY);
	size.push_back(arg_width);
	size.push_back(arg_height);
}


MenuBoard::~MenuBoard()
{
}
// 主選單模式
int MenuBoard::mainMenu()
{
	breakOut = false; // 迴圈開始
	printBoard(); // 印出選單
	while (!breakOut) {
		if (_kbhit())
		{
			int ch = _getch();
			// 按下Enter鍵後
			if (ch == '\r')
			{
				int returnValue;
				switch (mode) {
				case 1:        // 雙人遊戲
					returnValue =  1;             // ChineseChess.mode 的GameMode
					break;
				case 2:        // 繼續遊戲(讀取棋盤)
					returnValue = 1;              // ChineseChess.mode 的GameMode
					break;
				case 3:        // 重播賽局
					returnValue = 1;
					break;
				case 4:        // 離開遊戲
					ChineseChess::setCursorSize(true, 0); // 歸還游標
					returnValue = 3; 
				}
				ChineseChess::setCursorSize(true, 0);
				return returnValue;
			}
			// 按下方向鍵後
			else if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: // 上
					if (mode == 1) mode = 4;
					else --mode;
					break;
				case 80: // 下
					if (mode == 4) mode = 1;
					else ++mode;
					break;
				};
				printSelect(); // 更新已選取選項位置
			}
		}
	}
}

// 印出主選單外框
void MenuBoard::printBoard()
{
	// 隱藏游標
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
	printSelect();
}

// 印出主選單選項
void MenuBoard::printSelect() {

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 1);
	if (mode == 1) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"雙人遊戲";

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 3);
	if (mode == 2) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"繼續遊戲";

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 5);
	if (mode == 3) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"重播棋局";

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 7);
	if (mode == 4) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"離開遊戲";
}