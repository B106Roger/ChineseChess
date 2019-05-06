#include "ChineseChess.h"
#include"RecordBoard.h"

using namespace std;

ChineseChess::ChineseChess()
	:gameOver(false),frameWidth(65),frameHeight(35), order(0)
{
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

	hintBoard.printBoard();
	hintBoard.printHint1(order);
	ChineseChess::setCursor(gameBoard.startX, gameBoard.startY);
	// printStartWindow()

	while (!gameOver)
	{
		if (_kbhit())
		{
			int ch = _getch();
			// 按下Enter鍵後
			if (ch == '\r') 
			{
				/* start 取出目前游標在棋盤的位置 */
				int x, y;
				getCursor(x, y);
				x = (x - gameBoard.startX) / 4;
				y = (y - gameBoard.startY) / 2;
				ChineseChess::setCursor(40, 25);
				cout << "X: ";
				cout.width(3);
				cout << x;
				cout << "  Y: ";
				cout.width(3);
				cout << y << endl;
				/* end 取出目前游標在棋盤的位置 */

				if (gameBoard.colorBoard[y][x] == 1 || (gameBoard.colorBoard[y][x] == 0 && gameBoard.chessBoard[y][x] == 0))
				{
					// 如果選到自己 或是 選到不能移動的空白格子，就取消選取
					gameBoard.resetColorBoard();
					gameBoard.printBoard();
				}
				else if (gameBoard.colorBoard[y][x] == -1)
				{
					// 移動棋子 ，輪下一回合
					gameBoard.movingChess(x, y);
					order = !order;
					hintBoard.printHint1(order);
				}
				else if (gameBoard.colorBoard[y][x] == -2)
				{
					// 座標上的旗子被吃 ，輪下一回合
					gameBoard.movingChess(x, y);
					order = !order;
					hintBoard.printHint1(order);
				}
				else if (gameBoard.colorBoard[y][x] == 0 && gameBoard.chessBoard[y][x] != 0)
				{
					// 判斷棋子可移動的範圍並替colorBoard著色
					// order = 0 黑色移動    order = 1 紅色移動
					if ((order == 0 && gameBoard.chessBoard[y][x] <= 7) || (order == 1 && gameBoard.chessBoard[y][x] >= 8))
					{
						hintBoard.printHint2(order, gameBoard.chessBoard[y][x]);
						gameBoard.moveChess(x, y);
					}
				}
				// 設定成原本的cursor 位置
				ChineseChess::setCursor(4 * x + gameBoard.startX, 2 * y + gameBoard.startY);
			}
			// 按下方向鍵後
			else if (ch == 224)
			{
				ch = _getch();
				// 取得目前位置
				CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleinfo);
				// 移動到20,20印座標
				COORD point;
				ChineseChess::setCursor(40, 30);
				
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
				/* start 印出棋子在window的座標 */
				cout << "X: ";
				cout.width(3);
				cout << point.X << "    Y: ";
				cout.width(3);
				cout << point.Y;
				// 回到原本的座標
				/* end 印出棋子在window的座標 */
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
			}
			// 按下Esc鍵後
			//else if (ch == 27)
			//{

			//}
			//// 悔棋
			//else if (ch == '<')
			//{
			//	// 印悔棋小視窗(member function)  default 否
			//	while (true)
			//	{
			//		// 切換是否
			//		if (_kbhit())
			//		{
			//			int ch = _getch();
			//			if (ch == 224)
			//			{
			//				ch = _getch();
			//				switch (ch)
			//				{
			//				case 75: // 左
			//				case 77: // 右
			//				default:
			//				}
			//			}
			//			else if (ch == '\r')
			//			{
			//				// 悔棋
			//				// gameboard.printBoard()
			//				// hintBoard.printHint1()
			//				// hintBoard.printHint2()
			//				// break;
			//			}
			//		}
			//	}
			//}
			//// 還原
			//else if (ch == '>')
			//{
			//}
		}
	}
	/*while (true)
	{
		if (mode == GameMode)
		{
			detectKB();
		}
		else if (mode == MainMenuMode)
		{
			//  1. 雙人遊戲  2. 繼續遊戲(讀取棋盤) 3. 退出遊戲 	
		}
		else if (mode == EscMode)
		{
			//  1. 繼續遊戲  2. 重新開始(捨棄當前所有資料)   3. 投降(儲存record 輸了也要儲存record) 4. 儲存遊戲  5. 主選單
		}
		else if (mode = ExitMode)
		{
			break;
		}
	}*/

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
