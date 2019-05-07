#include "ChineseChess.h"
#include"RecordBoard.h"

using namespace std;

GameBoard ChineseChess::gameBoard = GameBoard();
RecordBoard ChineseChess::recordBoard = RecordBoard();
HintBoard ChineseChess::hintBoard = HintBoard();
EscBoard ChineseChess::escBoard = EscBoard();
MenuBoard ChineseChess::maenuBoard = MenuBoard();
string ChineseChess::fileName;
ChineseChess::ChineseChess()
	:gameOver(false), order(0)
{
	mode = 0;  // 一開始設為主選單模式
}
ChineseChess::~ChineseChess()
{

}
void ChineseChess::gameLoop(void)
{
	
	while (mode != 3)    //  ExitMode
	{
		if (mode == 0)   // MenuMode
		{
			printFrame();
			int menuValue = maenuBoard.mainMenu();
			//  1. 雙人遊戲  2. 繼續遊戲(讀取棋盤)  3. 重播棋局  4. 離開遊戲
			if (menuValue == 1)       
			{
				newGame();
				mode = 1;
			}
			else if (menuValue == 2)
			{
				readAndSetBoard();
				mode = 1;
			}
			else if (menuValue == 3)
			{
				mode = 0;
			}
			else if (menuValue == 4)
			{
				mode = 3;
			}
		}
		else if (mode == 1)   // GameMode
		{
			
			gameStart();
		}
		else if (mode == 3)    // ReplayMode
		{
			//  replayBoard.replay()
		}
	}
}
void ChineseChess::gameStart(void)
{
	printFrame(); // 要將其他不需要的東西刷掉
	recordBoard.printBoard();
	gameBoard.printBoard();
	hintBoard.printBoard(); // hintBoard基本框
	hintBoard.printHint1(order); // 輪到誰
	if (gameBoard.isGeneral(order)) { // 有被將軍嗎？
		hintBoard.printHint3(order);
	}
	// testing
	// escBoard.escMenu();
	// maenuBoard.mainMenu();
	ChineseChess::setCursor(gameBoard.startX, gameBoard.startY);
	while (mode == 1) // 1 是ChineseChess的GameMode
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
					hintBoard.hideHint2();
				}
				else if (gameBoard.colorBoard[y][x] == -1)
				{
					// 移動棋子 ，輪下一回合
					gameBoard.movingChess(x, y);
					order = !order;
					hintBoard.printHint1(order); // 輪轉時，hint1換方，hint2隱藏，hint3判斷
					hintBoard.hideHint2();
					if(gameBoard.isGeneral(order)) hintBoard.printHint3(order);
					else hintBoard.hideHint3();
				}
				else if (gameBoard.colorBoard[y][x] == -2)
				{
					// 座標上的旗子被吃 ，輪下一回合
					gameBoard.movingChess(x, y);
					order = !order;
					hintBoard.printHint1(order);
					hintBoard.hideHint2();
					if (gameBoard.isGeneral(order)) hintBoard.printHint3(order);
					else hintBoard.hideHint3();
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
			else if (ch == 27)
			{
				int escModeValue = escBoard.escMenu();
				if (escModeValue == 0)      // 1繼續遊戲
				{
					gameBoard.printBoard();
				}
				else if (escModeValue == 1) // 2重新開始
				{
					newGame();
					break;
				}
				else if (escModeValue == 2) // 3投降
				{
					// 印出投降提示
					// 決定儲存遊戲 或 回主選單
				}
				else if (escModeValue == 3) // 4儲存遊戲
				{
					// 儲存遊戲
					gameBoard.printBoard();
				}
				else if (escModeValue == 4) // 5回主選單
				{
					mode = 0;
				}
			}
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
	
}


// 印出邊框
void ChineseChess::printFrame()
{
	wstring edge(width - 2, L'＝'),side(width - 2, L'　');
	edge = L"●" + edge;
	edge.push_back(L'●');
	side = L"∥" + side;
	side.push_back(L'∥');
	for (int i = 0; i < height; i++)
	{
		ChineseChess::setCursor(startX, startY + i);
		if (i == 0 || i == height - 1)
		{
			wcout << edge;
		}
		else
		{
			wcout << side;
		}
	}

}

// 新遊戲
void ChineseChess::newGame()
{
	order = 0;
	gameBoard.resetColorBoard();
	gameBoard.resetChessBoard();
	recordBoard.msgBoard.clear();
	recordBoard.detailBoard.clear();
}

// 讀取檔案
void ChineseChess::readAndSetBoard()
{
	ifstream in;
	fileName = "Test.txt";
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
		in.clear();
		in.close();
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

void ChineseChess::setCursorSize(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
