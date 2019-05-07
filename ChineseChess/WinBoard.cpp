#include "WinBoard.h"
#include "ChineseChess.h"


WinBoard::WinBoard(int cursorX, int cursorY, int sizeX, int sizeY, int iniMode)
	:mode(iniMode)
{
	cursor.push_back(cursorX);
	cursor.push_back(cursorY);
	size.push_back(sizeX);
	size.push_back(sizeY);
}

WinBoard::~WinBoard()
{
}

int WinBoard::winMenu(int order) {
	winner = order;
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
				return returnValue;
			}
			// 按下方向鍵後
			else if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 75: // 左
					if (mode == 0) mode = 1;
					else mode--;
					break;
				case 77: // 右
					if (mode == 1) mode = 0;
					else mode++;
					break;
				};
				printWord(); // 更新已選取選項位置
			}
		}
	}
}

void WinBoard::printBoard(){
	ChineseChess::setCursorSize(false, 0);
	int frameWidth = size[0];
	int frameHeight = size[1];
	ChineseChess::SetColor(6, 0); //土黃色框
	for (int i = 0; i < frameHeight; i++) {
		ChineseChess::setCursor(cursor[0], cursor[1] + i);
		for (int j = 0; j < frameWidth; j++) {
			
			if (i == 0 || i == frameHeight - 1) // 上
			{
				if (j == 0) wcout << L"●";// 左上角
				else if (j == frameWidth - 1) wcout << L"●";// 右上角
				else wcout << L"＝";// 上方
			}
			else// 中
			{
				if (j == 0 || j == frameWidth - 1) wcout << L"∥";// 中間
				else {
					// ChineseChess::SetColor(0, 6);
					wcout << L"　";
				}
			}
		}
	}
	ChineseChess::SetColor();
	printWord();
}

void WinBoard::printWord() {
	ChineseChess::SetColor();

	ChineseChess::setCursor(cursor[0] + (size[0]-4), cursor[1]);
	if (winner == 0) {
		ChineseChess::SetColor(8, 0); // 灰字黑底
		wcout << L"黑方勝利";
	}
	else if (winner == 1) {
		ChineseChess::SetColor(12, 0); // 淺紅字黑底
		wcout << L"紅方勝利";
	}

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 3);
	if (mode == 0) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"回主選單";
	ChineseChess::setCursor(cursor[0] + 32, cursor[1] + 3);
	if (mode == 1) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"儲存遊戲";

	ChineseChess::SetColor();
}