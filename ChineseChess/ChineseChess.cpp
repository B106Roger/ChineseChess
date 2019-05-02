#include "ChineseChess.h"
#include"RecordBoard.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include<Windows.h>
using namespace std;

ChineseChess::ChineseChess()
	:gameOver(false),frameWidth(45),frameHeight(40)
{
	// 初始化棋盤為9*9陣列
	for (int i = 0; i < 9; i++)
	{
		gameBoard.chessBoard.push_back(vector<int>(0, 9));
		gameBoard.colorBoard.push_back(vector<int>(0, 9));
	}
}
ChineseChess::~ChineseChess()
{
}

void ChineseChess::gameStart(void)
{
	printFrame();
	while (!gameOver)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				// 取得目前位置
				CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
				// 移動到20,20印座標
				COORD point;
				point.X = 20;
				point.Y = 20;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
				
				switch(ch)
				{
				case 72: 
					point.Y = (consoleinfo.dwCursorPosition.Y <= 0 ? frameHeight : consoleinfo.dwCursorPosition.Y - 1);
					point.X = consoleinfo.dwCursorPosition.X;
					break;  // 上
				case 80: 
					point.Y = (consoleinfo.dwCursorPosition.Y <= frameHeight ? 0 : consoleinfo.dwCursorPosition.Y + 1);
					point.X = consoleinfo.dwCursorPosition.X;
					break; // 下
				case 75:
					point.X = (consoleinfo.dwCursorPosition.X <= 0 ? frameWidth*3 : consoleinfo.dwCursorPosition.X - 1);
					point.Y = consoleinfo.dwCursorPosition.Y;
					break; // 左
				case 77: 
					point.X = (consoleinfo.dwCursorPosition.X >= frameWidth*3 ? 0 : consoleinfo.dwCursorPosition.X + 1);
					point.Y = consoleinfo.dwCursorPosition.Y;
					break; // 右
				};
				cout << "X: ";
				cout.width(3);
				cout << point.X << "    Y: ";
				cout.width(3);
				cout << point.Y;
				// 回到原本的座標
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			}
		}
	}
}

void ChineseChess::printFrame()
{
	for (int i = 0; i < frameHeight; i++)
	{
		for (int j = 0; j < frameWidth; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					wcout << L"╔ ";
				}
				else if (j == frameWidth - 1)
				{
					wcout << L"╗";
				}
				else
				{
					wcout << L" ═ ";
				}
			}
			else if (i == frameHeight - 1)
			{
				if (j == 0)
				{
					wcout << L"╚ ";
				}
				else if (j == frameWidth - 1)
				{
					wcout << L"╝ ";
				}
				else
				{
					wcout << L" ═ ";
				}
			}
			else
			{
				if (j == 0 || j == frameWidth - 1)
				{
					wcout << L"║ ";
				}
				else
				{
					wcout << "   ";
				}
			}
		}
		cout << endl;
	}
}

void ChineseChess::readAndSetBoard()
{
	ifstream in;
	string fileName;
	cin >> fileName;
	in.open(fileName);
	if (in.is_open())
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				in >> gameBoard.chessBoard[i][j];
				gameBoard.colorBoard[i][j] = 0;
			}
		}
		in >> order;
	}
	else
	{
		cout << "fail!!\n";
	}
}

void ChineseChess::setCursor(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

