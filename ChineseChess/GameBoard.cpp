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

// �L�X��ӴѽL
void GameBoard::printBoard()
{
	for (int i = 0; i < height; i++)
	{
		printRow(i);
	}
}

// �L�X�ѽL���C�@�� + �C��  
void GameBoard::printRow(int rowIndex)
{
	// ���e�~��
	ChineseChess::setCursor(startX, startY + rowIndex);
	if (rowIndex == 9)
	{
		ChineseChess::SetColor(0, 15);
		wcout << L"���@�@�@���e�@�@�@�@�@�~�ɡ@�@�@��";
		return;
	}
	// ��Lrow
	for (int j = 0; j < width; j++)
	{
		// ���i�঳�Ѥl�����p
		if (rowIndex % 2 == 1 || j % 2 == 1)
		{
			ChineseChess::SetColor(0, 15);
		}
		// ���i�঳�Ѥl�����p
		else
		{
			int x = j / 2, y = rowIndex / 2;
			int fontColor, backgroundColor;
			// �p�G�W�����X�l
			if (chessBoard[y][x] != 0)
			{
				// �ӥB�O�i�H�Q�Y�����X�l
				if (colorBoard[y][x] != 0)
				{
					//                         �ǩ����r:�ǩ��¦r
					backgroundColor = 9;
					fontColor = (chessBoard[y][x] > 7 ? 12 : 0);
				}
				// �p�G�O����Q�Y�����X�l
				else
				{
					// ���`���Ѥl              �ǩ����r:�ǩ��¦�
					backgroundColor = 7;
					fontColor = (chessBoard[y][x] > 7 ? 12 : 0);
				}
			}
			// �p�G�W���S�Ѥl
			else if (colorBoard[y][x] == 0)
			{
				// �ťճ��� �թ��¦r
				fontColor = 0;
				backgroundColor = 15;
			}
			ChineseChess::SetColor(fontColor, backgroundColor);
		}
		wcout << getPrintedChar(rowIndex, j);
	}
}

// ���o�ѽL�W���ӭn�L���r
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
			// ����
			if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
			{
				return L"��";
			}
			// �Ĥ@�C�A�̫�@�C
			if (j == 0 || j == width - 1)
			{
				return L"��";
			}
			// �Ĥ@��A�̫�@��
			if (i == 0 || i == height - 1)
			{
				return L"��";
			}
			// ���e�~��
			if (i == 8 || i == 10)
			{
				return L"�X";
			}
			// ��e�I
			if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
			{
				return L"��";
			}

		}
		else
		{
			if (i == 0 || i == height - 1)
			{
				return L"��";
			}
			else if (j % 2 == 1)
			{
				return L"�X";
			}
		}
	}
	else
	{
		if (j % 2 == 0)
		{
			if (j == 0 || j == width - 1)
			{
				return L"��";
			}
			else
			{
				return L"�U";
			}
		}
		else
		{
			if (j == 7 && (i == 1 || i == 15))
			{
				return L"�@";
			}
			else if (j == 9 && (i == 3 || i == 17))
			{
				return L"�@";
			}
			else if (j == 7 && (i == 3 || i == 17))
			{
				return L"��";
			}
			else if (j == 9 && (i == 1 || i == 15))
			{
				return L"��";
			}
			
		}
		
	}
	return  L"�@";
}

