#include "ChineseChess.h"
#include"RecordBoard.h"

using namespace std;
// static data member
GameBoard ChineseChess::gameBoard = GameBoard();
RecordBoard ChineseChess::recordBoard = RecordBoard();
HintBoard ChineseChess::hintBoard = HintBoard();
EscBoard ChineseChess::escBoard = EscBoard();
MenuBoard ChineseChess::maenuBoard = MenuBoard();
WinBoard ChineseChess::winBoard = WinBoard();
//ReadFileBoard ChineseChess::fileBoard = ReadFileBoard();
string ChineseChess::fileName;

ChineseChess::ChineseChess()
	:gameOver(false), order(0)
{
	mode = 0;  // 一開始設為主選單模式
	subWindow = vector<int>(4, 0);
	subWindow[0] = gameBoard.startX;
	subWindow[1] = gameBoard.startY + 8;
	subWindow[2] = gameBoard.width;
	subWindow[3] = 5;
}
ChineseChess::~ChineseChess()
{

}
// 流程迴圈
void ChineseChess::gameLoop(void)
{
	while (mode != 4)    //  ExitMode
	{
		if (mode == 0)   // MenuMode
		{
			printFrame();
			int menuValue = maenuBoard.mainMenu();
			//  0. 雙人遊戲  1. 繼續遊戲(讀取棋盤)  2. 重播棋局  3. 離開遊戲
			newGame();
			if (menuValue == 0)       
			{
				newGame();
				mode = 1; // GameMode
			}
			else if (menuValue == 1)
			{
				// 依據檔按讀取成功與失敗決定GameMode或MenuMode
				mode = fileWindow();
			}
			else if (menuValue == 2)
			{
				// 未完成
				mode = 3;  // ReplayMode
			}
			else if (menuValue == 3)
			{
				mode = 4;  // ExitMode 
			}
		}
		else if (mode == 1)   // GameMode
		{
			gameStart();
		}
		else if (mode == 3)    // ReplayMode
		{
			// 未完成
			// 先換成menuMode，因為還沒做完
			mode = 0;
		}
	}
}

// 遊戲迴圈
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
					recordBoard.setRecord(x, y, gameBoard.chessBoard, gameBoard.colorBoard);
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
					recordBoard.setRecord(x, y, gameBoard.chessBoard, gameBoard.colorBoard);
					gameBoard.movingChess(x, y);
					//
					//if (gameBoard.movingChess(x, y) == true)
					//{
					//	if (hintBoard.winMenu(order) == 1)
					//	{
					//		saveGame();
					//	}
					//	mode = 0;
					//}
					//
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
				if (escModeValue == 0)      // 0.繼續遊戲
				{
					gameBoard.printBoard();
				}
				else if (escModeValue == 1) // 1.重新開始
				{
					newGame();
					break;
				}
				else if (escModeValue == 2) // 2.投降
				{
					if (hintBoard.winMenu(!order) == 0) { // 回主選單
						mode = 0;
					}
					else { // 儲存遊戲，然後在回主選單
						saveGame();
						mode = 0;
					}
					// 印出投降提示
					// 決定儲存遊戲 或 回主選單
					// 未完成
					gameBoard.printBoard();
				}
				else if (escModeValue == 3) // 3.儲存遊戲
				{
					// 儲存遊戲
					// 未完成
					gameBoard.printBoard();
				}
				else if (escModeValue == 4) // 4.回主選單
				{
					mode = 0;
				}
			}
			// 按下 < 鍵後
			else if (ch == ',')
			{
				// 悔棋 
				int returnValue = smallWindow(L"確　認　悔　棋");
				//recordBoard.regret(gameBoard.chessBoard);			//還在debug
			}
			// 按下 > 鍵後
			else if (ch == '.')
			{
				// 還原
				int returnValue = smallWindow(L"確　認　還　原");
				//recordBoard.reduction(gameBoard.chessBoard);
			}

			
			//{
			//	印悔棋小視窗(member function)  default 否
			//	while (true)
			//	{
			//		 切換是否
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
			//				 悔棋
			//				 gameboard.printBoard()
			//				 hintBoard.printHint1()
			//				 hintBoard.printHint2()
			//				 break;
			//			}
			//		}
			//	}
			//}
			// 還原
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

// 印出邊框(可調參數)
void ChineseChess::printFrame(int xpos, int ypos, int xsize, int ysize, wstring title)
{
	SetColor();
	wstring upper;
	wstring lower(xsize - 2, L'＝');
	wstring side(xsize - 2, L'　');
	lower = L"●" + lower;
	lower.push_back(L'●');
	side = L"∥" + side;
	side.push_back(L'∥');
	if (int(title.size()) != 0)
	{
		int leftspace = (xsize - title.size() - 2) / 2;
		int rightspace = xsize - title.size() - 2 - leftspace;
		upper = title;
		upper = wstring(leftspace, L'＝') + upper + wstring(rightspace, L'＝');
		upper.insert(0, 1, L'●');
		upper.push_back(L'●');
	}
	else
	{
		upper = lower;
	}
	
	for (int i = 0; i < ysize; i++)
	{
		ChineseChess::setCursor(xpos, ypos + i);
		if (i == 0 )
		{
			wcout << upper;
		}
		else if (i == ysize - 1)
		{
			wcout << lower;
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
	recordBoard.resetRecordBoard();
	fileName = "";
}

// 讀取視窗
int ChineseChess::fileWindow()
{
	// 設定視窗大小
	int xPos = gameBoard.startX, yPos = gameBoard.startY;
	int windowWidth = gameBoard.width;
	int windowHeight = 15;
	// 印出視窗
	wstring title = L"請　輸　入　檔　名";
	printFrame(xPos, yPos, windowWidth, 4, title);
	ChineseChess::setCursor(xPos + 2, yPos + 2);
	fileName = "";
	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == '\r')
			{
				break;
			}
			else if (ch == '\b')
			{
				fileName.pop_back();
				cout << "\b \b";
			}
			else if (fileName.length() > (windowWidth - 4) * 2)
			{
				continue;
			}
			else
			{
				fileName.push_back(ch);
				cout << ch;
			}
		}
	}
	int returnValue, readFileResult = readAndSetBoard(fileName);
	if (readFileResult == 1)
	{
		printFrame(xPos, yPos, windowWidth, 4, L"讀　取　檔　案　成　功");
		returnValue = 1; // GameMode
	}
	else if (readFileResult == 0)
	{
		printFrame(xPos, yPos, windowWidth, 4, L"讀　取　檔　案　失　敗");
		fileName = "";
		returnValue = 0; // MenuMode
	}
	else if (readFileResult == 2)
	{
		printFrame(xPos, yPos, windowWidth, 4, L"此　賽　局　已　結　束");
		fileName = "";
		returnValue = 0; // MenuMode
	}
	ChineseChess::setCursor(xPos + windowWidth / 2 - 4, yPos + 2);
	wcout << L"按任意鍵以繼續操作";
	while (true)
	{
		if (_kbhit())
		{
			_getch();
			return returnValue;
		}
	}

}

// 讀取檔案
// 0 讀檔失敗 1 讀檔成功 2 賽局已結束
int ChineseChess::readAndSetBoard(string name)
{
	ifstream inBoard, inRecord;
	string boardName = name, recordName = name;

	inBoard.open(boardName);
	if (inBoard.is_open())
	{
		int offset = boardName.find(".txt");
		recordName.insert(offset, "Rec");
		inRecord.open(recordName);
		if (inRecord.is_open())
		{
			int gameOverBit;
			inRecord >> gameOverBit;
			if (gameOverBit == 1)
			{
				inRecord.close();
				inBoard.close();
				fileName = "";
				return 2;
			}
			else
			{
				// 讀取下棋記錄
				record tmpRec;
				recordBoard.detailBoard.clear();
				while (inRecord >> tmpRec.hunter)
				{
					inRecord >> tmpRec.Xpos
						>> tmpRec.Ypos
						>> tmpRec.whosTurn
						>> tmpRec.deltaX
						>> tmpRec.deltaY
						>> tmpRec.prey;
					recordBoard.detailBoard.push_back(tmpRec);
				}
			}
		}
		// 讀取棋盤資料的
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				inBoard >> gameBoard.chessBoard[i][j];
			}
		}
		inBoard >> order;
		fileName = boardName;

		inRecord.close();
		inBoard.close();
		return 1;
	}
	else
	{
		fileName = "";
		return 0;
	}
}

// 悔棋
int ChineseChess::smallWindow(wstring title)
{
	// 1是  0否
	int returnValue = 1;
	setCursorSize(false, 0);
	printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], title);
	// 印是否
	SetColor();
	if (returnValue == 0) SetColor(0,15);
	setCursor(subWindow[0] + 2, subWindow[1] + 2);
	wcout << L"否";
	SetColor();
	if (returnValue == 1) SetColor(0, 15);
	setCursor(subWindow[0] + subWindow[2], subWindow[1] + 2);
	wcout << L"是";

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == '\r')
			{
				setCursorSize(true, 0);
				return returnValue;
			}
			else if (ch == 224)
			{
				ch = _getch();
				if (ch == 77 || ch == 75)
				{
					returnValue != returnValue;
				}
			}

			SetColor();
			if (returnValue == 0) SetColor(0, 15);
			setCursor(subWindow[0] + 2, subWindow[1] + 2);
			wcout << L"否";
			SetColor();
			if (returnValue == 1) SetColor(0, 15);
			setCursor(subWindow[0] + subWindow[2], subWindow[1] + 2);
			wcout << L"是";
		}
	}
}

// static function
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

// 設定座標visible
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

void ChineseChess::saveGame() {
	if (fileName == "") { // 
		//time_t t = time(0);
		//char tmp[64];
		//strftime_s(tmp, sizeof(tmp), "%Y_%m_%d_%X", localtime(&t));
		//fileName = tmp;
	}
	else {

	}
}