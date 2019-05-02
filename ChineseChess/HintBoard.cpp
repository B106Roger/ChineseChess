#include "HintBoard.h"
#include "ChineseChess.h" // 必須在.cpp檔include
/*HintBoard::HintBoard()
{
}*/

HintBoard::HintBoard(int cursorX, int cursorY, int sizeX, int sizeY)
{
	cursor.push_back(cursorX); cursor.push_back(cursorY);
	size.push_back(sizeX); size.push_back(sizeY);
}


HintBoard::~HintBoard()
{
}

void HintBoard::printBoard() {

	/*int frameWidth = cursor[1] + size[1];
	int frameHeight = cursor[0] + size[0];
	ChineseChess::setCursor(cursor[0], cursor[1]);

	for (int i = cursor[0]; i < cursor[0] + size[0]; i++) {
		for (int j = cursor[1]; j < cursor[1] + size[1]; j++) {
			if (i == 0)
			{
				if (j == 0) // 左上角
				{
					wcout << L"╔ ";
				}
				else if (j == frameWidth - 1) // 右上角
				{
					wcout << L"╗";
				}
				else // 上方
				{
					wcout << L" ═ ";
				}
			}
			else if (i == frameHeight - 1)
			{
				if (j == 0) // 左下角
				{
					wcout << L"╚ ";
				}
				else if (j == frameWidth - 1) // 右下角
				{
					wcout << L"╝ ";
				}
				else // 下方
				{
					wcout << L" ═ ";
				}
			}
			else
			{
				if (j == 0 || j == frameWidth - 1) // 中間
				{
					wcout << L"║ ";
				}
				else // 
				{
					wcout << "   ";
				}
			}
		}
	}*/

}