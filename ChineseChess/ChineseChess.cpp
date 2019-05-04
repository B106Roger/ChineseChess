#include "ChineseChess.h"
#include"RecordBoard.h"

using namespace std;

ChineseChess::ChineseChess()
	:gameOver(false),frameWidth(65),frameHeight(35)
{
	// 初始化棋盤為9*10陣列
	for (int i = 0; i < 10; i++)
	{
		gameBoard.chessBoard.push_back(vector<int>(0, 9));
		gameBoard.colorBoard.push_back(vector<int>(0, 9));
	}
	// hintBoard = new HintBoard();
}
ChineseChess::~ChineseChess()
{

}

void ChineseChess::gameStart(void)
{
	system("PAUSE");
	system("CLS");
	readAndSetBoard();
	printFrame();
	recordBoard.printBoard();
	gameBoard.printBoard();
	ChineseChess::setCursor(gameBoard.startX, gameBoard.startY);
	while (!gameOver)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == '\r') // Enter press
			{
				// 取出目前游標位置
				int x, y;
				getCursor(x, y);
				x = (x - gameBoard.startX) / 4;
				y = (y - gameBoard.startY) / 2;
				ChineseChess::setCursor(40, 30);
				cout << "X: ";
				cout.width(3);
				cout << x;
				cout << "  Y: ";
				cout.width(3);
				cout << y << endl;
				ChineseChess::setCursor(4 * x + gameBoard.startX, 2 * y + gameBoard.startY);

				if (gameBoard.colorBoard[y][x] == 1)
				{
					// 不做事
				}
				else if (gameBoard.colorBoard[y][x] == -1)
				{
					// 移動棋子
				}
				else if (gameBoard.colorBoard[y][x] == -2)
				{
					// 座標上的旗子被吃
				}
				// 去chessBoard判斷有沒有旗子 continue
				// colorBorad 幫移動位置塗灰
				//if(ch = _getch();)
				// colorBoard 0:colorBoard => 0 // -1: colorBoard => 
			} 
			else if (ch == 224)
			{
				ch = _getch();
				// 取得目前位置
				CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
				// 移動到20,20印座標
				COORD point;
				point.X = 70;
				point.Y = 20;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
				
				switch(ch)
				{
				case 72: // 上
					point.Y = (consoleinfo.dwCursorPosition.Y <= gameBoard.startY ? gameBoard.startY + gameBoard.height - 1 : consoleinfo.dwCursorPosition.Y - 2);
					point.X = consoleinfo.dwCursorPosition.X;
					break;  
				case 80: // 下
					point.Y = (consoleinfo.dwCursorPosition.Y >= gameBoard.startY + gameBoard.height - 1 ? gameBoard.startY : consoleinfo.dwCursorPosition.Y + 2);
					point.X = consoleinfo.dwCursorPosition.X;
					break; 
				case 75: // 左
					point.X = (consoleinfo.dwCursorPosition.X <= gameBoard.startX ? (gameBoard.startX + (gameBoard.width- 1)*2 ) : consoleinfo.dwCursorPosition.X - 4);
					point.Y = consoleinfo.dwCursorPosition.Y;
					break; 
				case 77: // 右
					point.X = (consoleinfo.dwCursorPosition.X >= (gameBoard.startX + (gameBoard.width - 1)*2)? gameBoard.startX : consoleinfo.dwCursorPosition.X + 4);
					point.Y = consoleinfo.dwCursorPosition.Y;
					break;
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

// 印出邊框
void ChineseChess::printFrame()
{
	for (int i = 0; i < height; i++)
	{
		ChineseChess::setCursor(startX, startY + i);
		for (int j = 0; j < width; j++)
		{
			if (i == 0) 
			{
				if (j == 0) // 左上角
				{
					wcout << L"●";
				}
				else if (j == width - 1) // 右上角
				{
					wcout << L"●";
				}
				else // 上方
				{
					wcout << L"＝";
				}
			}
			else if (i == height - 1)
			{
				if (j == 0) // 左下角
				{
					wcout << L"●";
				}
				else if (j == width - 1) // 右下角
				{
					wcout << L"●";
				}
				else // 下方
				{
					wcout << L"＝";
				}
			}
			else
			{
				if (j == 0 || j == width - 1) // 中間
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
	hintBoard.printBoard();
}

// 讀取檔案
void ChineseChess::readAndSetBoard()
{
	ifstream in;
	string fileName = "Test.txt";
	in.open(fileName);
	if (in.is_open())
	{
		for (int i = 0; i < 10; i++)
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

// 設定座標
void ChineseChess::setCursor(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// 設定顏色
void ChineseChess::SetColor(int f, int b)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}

// 取得目前游標位置
void ChineseChess::getCursor(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}
