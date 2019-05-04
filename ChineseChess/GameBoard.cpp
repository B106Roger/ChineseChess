#include "GameBoard.h"
#include"ChineseChess.h"
#include<Windows.h>
#include"Chess.h"

GameBoard::GameBoard()
{
	for (int i = 0; i < 10; i++)
	{
		chessBoard.push_back(vector<int>(9, 0));
		colorBoard.push_back(vector<int>(9, 0));
	}
}


GameBoard::~GameBoard()
{
}

// 印出整個棋盤
void GameBoard::printBoard()
{
	for (int i = 0; i < height; i++)
	{
		printRow(i);
	}
}

// 印出棋盤的每一行 + 顏色  
void GameBoard::printRow(int rowIndex)
{
	// 楚河漢界
	ChineseChess::setCursor(startX, startY + rowIndex);
	if (rowIndex == 9)
	{
		ChineseChess::SetColor(0, 15);
		wcout << L"∥　　　楚河　　　　　漢界　　　∥";
		return;
	}
	// 其他row
	for (int j = 0; j < width; j++)
	{
		// 不可能有棋子的狀況
		if (rowIndex % 2 == 1 || j % 2 == 1)
		{
			ChineseChess::SetColor(0, 15);
		}
		// 有可能有棋子的狀況
		else
		{
			int x = j / 2, y = rowIndex / 2;
			int fontColor, backgroundColor;
			// 如果上面有旗子
			if (chessBoard[y][x] != 0)
			{
				// 而且是可以被吃掉的旗子
				if (colorBoard[y][x] != 0)
				{
					//                         灰底紅字:灰底黑字
					backgroundColor = 9;
					fontColor = (chessBoard[y][x] > 7 ? 12 : 0);
				}
				// 如果是不能被吃掉的旗子
				else
				{
					// 正常的棋子              灰底紅字:灰底黑色
					backgroundColor = 7;
					fontColor = (chessBoard[y][x] > 7 ? 12 : 0);
				}
			}
			// 如果上面沒棋子
			else if (colorBoard[y][x] == 0)
			{
				// 空白部分 白底黑字
				fontColor = 0;
				backgroundColor = 15;
			}
			ChineseChess::SetColor(fontColor, backgroundColor);
		}
		wcout << getPrintedChar(rowIndex, j);
	}
}

// 取得棋盤上應該要印的字
wstring GameBoard::getPrintedChar(int i, int j)
{
	if (i % 2 == 0)
	{
		if (j % 2 == 0)
		{
			if (chessBoard[i / 2][j / 2] != 0)
			{
				return Chess::chessName[chessBoard[i / 2][j / 2]];
			}
			// 角落
			if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
			{
				return L"●";
			}
			// 第一列，最後一列
			if (j == 0 || j == width - 1)
			{
				return L"∥";
			}
			// 第一行，最後一行
			if (i == 0 || i == height - 1)
			{
				return L"＝";
			}
			// 楚河漢界
			if (i == 8 || i == 10)
			{
				return L"—";
			}
			// 交叉點
			if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
			{
				return L"＋";
			}

		}
		else
		{
			if (i == 0 || i == height - 1)
			{
				return L"＝";
			}
			else if (j % 2 == 1)
			{
				return L"—";
			}
		}
	}
	else
	{
		if (j % 2 == 0)
		{
			if (j == 0 || j == width - 1)
			{
				return L"∥";
			}
			else
			{
				return L"｜";
			}
		}
		else
		{
			if (j == 7 && (i == 1 || i == 15))
			{
				return L"＼";
			}
			else if (j == 9 && (i == 3 || i == 17))
			{
				return L"＼";
			}
			else if (j == 7 && (i == 3 || i == 17))
			{
				return L"／";
			}
			else if (j == 9 && (i == 1 || i == 15))
			{
				return L"／";
			}
			
		}
		
	}
	return  L"　";
}

