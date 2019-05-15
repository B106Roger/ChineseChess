#include "ChineseChess.h"
#include"RecordBoard.h"

using namespace std;
// static data member
GameBoard ChineseChess::gameBoard = GameBoard();
RecordBoard ChineseChess::recordBoard = RecordBoard();
HintBoard ChineseChess::hintBoard = HintBoard();
EscBoard ChineseChess::escBoard = EscBoard();
MenuBoard ChineseChess::maenuBoard = MenuBoard();
string ChineseChess::fileName;

ChineseChess::ChineseChess()
	: order(0)
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
	//wcout << L"　　　　　中　　　　　　　";
	//wcout << L"　中中中中中中中中中　　　　　　　";
	//wcout << L"　中　　　中　　　中　　　　";
	//wcout << L"　　　　　中　　　　　　　";
	//wcout << L"　　　　　中　　　　　　　";
	//wcout << L"　　　　　中　　　　　　　";
	//wcout << L"　　　　　中　　　　　　　";
	// wcout << L"　　　　　中　　　　　　　";
}
// 流程迴圈
void ChineseChess::gameLoop(void)
{
	bool firstIn =true;
	while (mode != 4)    //  ExitMode
	{

		if (mode == 0)   // MenuMode
		{
			
			printFrame(startX, startY, width, height);
			if(firstIn) printArtSleep();
			else printArt();
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
			if (replayWindow() == 1)
			{
				replayMode();
			}
			else
			{
				mode = 0;
			}
			
		}
		firstIn = false;
	}
}

// 遊戲迴圈
void ChineseChess::gameStart(void)
{
	printFrame(startX, startY, width, height); // 要將其他不需要的東西刷掉
	recordBoard.printBoard();
	recordBoard.printMsg();
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
					if (gameBoard.movingChess(x, y) == 1) // 敵對王被吃了
					{
						if (hintBoard.winMenu(order) == 1) // 印出本方勝利，如果儲存
						{
							order = !order;               // 確定是哪一方勝利時，儲存其盤仍要換另外一方下
							saveGame(1);
						}
						mode = 0; // 儲存或回主選單都要mode = 0(跳回主選單)
					}
					
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
				int x, y;
				getCursor(x, y);
				
				switch(ch)
				{
				case 72: // 上
					y = (y <= gameBoard.startY ? gameBoard.startY + gameBoard.height - 1 : y - 2);
					x = x;
					break;  
				case 80: // 下
					y = (y >= gameBoard.startY + gameBoard.height - 1 ? gameBoard.startY : y + 2);
					x = x;
					break; 
				case 75: // 左
					x = (x <= gameBoard.startX ? (gameBoard.startX + (gameBoard.width- 1)*2 ) : x - 4);
					y = y;
					break; 
				case 77: // 右
					x = (x >= (gameBoard.startX + (gameBoard.width - 1)*2)? gameBoard.startX : x + 4);
					y = y;
					break;
				};
				// 回到原本的座標
				setCursor(x, y);
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
					if (hintBoard.winMenu(!order) == 1) { //儲存遊戲
						saveGame(0);
					}
					mode = 0; // +回主選單
					// 印出投降提示
					// 決定儲存遊戲 或 回主選單
					gameBoard.printBoard();
				}
				else if (escModeValue == 3) // 3.儲存遊戲
				{
					// 儲存遊戲
					saveGame(0);
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
				if (returnValue == 1)
				{
					if (recordBoard.regret(gameBoard.chessBoard) == 1)
					{
						printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], L"悔　棋　成　功");
					} 
					else
					{
						printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], L"悔　棋　失　敗");
					}
					
				}
				else
				{
					printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], L"悔　棋　失　敗");
				}
				setCursor(subWindow[0] + subWindow[2] - 10, subWindow[1] + 3);
				wcout << L"按任意鍵以繼續操作";
				while (true)
				{
					if (_kbhit())
					{
						_getch();
						break;
					}
				}
				gameBoard.printBoard();
			}
			// 按下 > 鍵後
			else if (ch == '.')
			{
				// 還原
				int returnValue = smallWindow(L"確　認　還　原");
				if (returnValue == 1)
				{
					if (recordBoard.reduction(gameBoard.chessBoard) == 1)
					{
						printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], L"還　原　成　功");
					}
					else
					{
						printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], L"還　原　失　敗");
					}
				}
				else
				{
					printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], L"還　原　失　敗");
				}
				setCursor(subWindow[0] + subWindow[2] - 10, subWindow[1] + 3);
				wcout << L"按任意鍵以繼續操作";
				while (true)
				{
					if (_kbhit())
					{
						_getch();
						break;
					}
				}
				gameBoard.printBoard();
			}
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
		int leftspace = (xsize - int(title.size()) - 2) / 2;
		int rightspace = xsize - int(title.size()) - 2 - leftspace;
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
		if (i == 0)
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

void ChineseChess::printArt() {
	fstream inputChina("chung.txt", ios::in);
	fstream inputChess("guo.txt", ios::in);
	setCursorSize(false, 0);

	string line;
	int yPos = 3;

	SetColor(6, 0);
	while (getline(inputChina, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
	}


	yPos = 3;
	SetColor(6, 0);
	while (getline(inputChess, line)) {
		setCursor(70, yPos);
		cout << line << endl;
		yPos++;
	}

	inputChina.close();
	inputChess.close();
	SetColor();
}

void ChineseChess::printArtSleep() {
	fstream inputChina("chung.txt", ios::in);
	fstream inputChess("guo.txt", ios::in);
	setCursorSize(false, 0);

	string line;
	int yPos = 3;

	SetColor(6, 0);
	while (getline(inputChina, line)) {
		setCursor(3, yPos);
		cout << line << endl;
		yPos++;
		Sleep(100);
	}


	yPos = 3;
	SetColor(6, 0);
	while (getline(inputChess, line)) {
		setCursor(70, yPos);
		cout << line << endl;
		yPos++;
		Sleep(100);
	}
	
	inputChina.close();
	inputChess.close();
	SetColor();
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
	int xPos = gameBoard.startX + 12, yPos = gameBoard.startY;
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
				if (fileName.size() > 0)
				{
					fileName.pop_back();
					cout << "\b \b";
				}
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
	setCursorSize(false, 0);
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
			setCursorSize(true, 0);
			return returnValue;
		}
	}

}

// 讀取檔案for繼續遊戲
// 0 讀檔失敗、 1 讀檔成功、 2 賽局已結束
int ChineseChess::readAndSetBoard(string name)
{
	ifstream inBoard, inRecord;
	string boardName = name, recordName = name;

	inBoard.open(boardName);
	if (inBoard.is_open())
	{
		int offset = (int)boardName.find(".txt");
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
		if (inRecord.is_open())
		{
			recordBoard.rebaseRecord();
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

// 印出 是否 的字
int ChineseChess::smallWindow(wstring title)
{
	// 1是  0否
	int returnValue = 1;
	int asideFromBoard = 6; // for 全形字
	setCursorSize(false, 0);
	printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3], title);
	// 印是否
	SetColor();
	if (returnValue == 0) SetColor(0,15);
	setCursor(subWindow[0] + asideFromBoard, subWindow[1] + 2);
	wcout << L"否";
	SetColor();
	if (returnValue == 1) SetColor(0, 15);
	setCursor(subWindow[0] + subWindow[2] * 2 - asideFromBoard - 2, subWindow[1] + 2);
	wcout << L"是";

	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == '\r')
			{
				setCursorSize(true, 0);
				SetColor();
				return returnValue;
			}
			else if (ch == 224)
			{
				ch = _getch();
				if (ch == 77 || ch == 75)
				{
					returnValue = !returnValue;
				}
			}

			SetColor();
			if (returnValue == 0) SetColor(0, 15);
			setCursor(subWindow[0] + asideFromBoard, subWindow[1] + 2);
			wcout << L"否";
			SetColor();
			if (returnValue == 1) SetColor(0, 15);
			setCursor(subWindow[0] + subWindow[2] * 2 - asideFromBoard - 2, subWindow[1] + 2);
			wcout << L"是";
		}
	}
}

// 儲存遊戲
void ChineseChess::saveGame(int finished) {
	if (fileName == "") { // 
		char tmp[20];
		time_t time_seconds = time(0);
		tm now_time;
		localtime_s(&now_time, &time_seconds);
		strftime(tmp, sizeof(tmp), "%Y_%m_%d_%H_%M_%S", &now_time);
		fileName = tmp + static_cast<string>(".txt");
		gameBoard.saveChessBoard(fileName, order);
		recordBoard.saveRecord(fileName, finished);
		saveGameSuccess();
	}
	else {
		gameBoard.saveChessBoard(fileName, order);
		recordBoard.saveRecord(fileName, finished);
		saveGameSuccess();
	}
}

// 重播遊戲讀檔視窗
int ChineseChess::replayWindow()
{
	// 設定視窗大小
	int xPos = gameBoard.startX + 12, yPos = gameBoard.startY;
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
				if (fileName.size() > 0)
				{
					fileName.pop_back();
					cout << "\b \b";
				}
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
	setCursorSize(false, 0);
	int resultBit, readFileResult = readAndSetBoard2(fileName);
	if (readFileResult == 1)
	{
		printFrame(xPos, yPos, windowWidth, 4, L"讀　取　檔　案　成　功");
		resultBit = 1;
	}
	else if (readFileResult == 0)
	{
		printFrame(xPos, yPos, windowWidth, 4, L"讀　取　檔　案　失　敗");
		fileName = "";
		resultBit = 0;
	}
	ChineseChess::setCursor(xPos + windowWidth / 2 - 4, yPos + 2);
	wcout << L"按任意鍵以繼續操作";
	while (true)
	{
		if (_kbhit())
		{
			_getch();
			setCursorSize(true, 0);
			break;
		}
	}
	return resultBit;
}

// 讀取檔案for重播模式。       0 讀檔其中一個失敗、 1 讀檔成功
int ChineseChess::readAndSetBoard2(string name)
{
	ifstream inBoard, inRecord;
	string boardName = name, recordName = name;

	inBoard.open(boardName);
	if (inBoard.is_open())
	{
		int offset = (int)boardName.find(".txt");
		recordName.insert(offset, "Rec");
		inRecord.open(recordName);
		if (inRecord.is_open())
		{
			int gameOverBit;
			inRecord >> gameOverBit;
			recordBoard.detailBoard.clear();
			// 讀取下棋記錄
			record tmpRec;
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
			
			// 讀取棋盤資料的
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					inBoard >> gameBoard.chessBoard[i][j];
				}
			}
			inBoard >> order;
			fileName = "";
			inRecord.close();
			inBoard.close();
			return 1;
		}
	}
	inBoard.close();
	fileName = "";
	return 0;
}

// 重播遊戲loop
void ChineseChess::replayMode()
{
	setCursorSize(false, 0);
	printFrame(startX, startY, width, height);
	
	recordBoard.rebaseRecord(true);
	recordBoard.printBoard();
	recordBoard.printMsg();
	gameBoard.printBoard();
	hintBoard.printBoard(mode);
	hintBoard.printHint1(order); // 輪轉時，hint1換方，hint2隱藏，hint3判斷
	while (true)
	{
		if (_kbhit())
		{
			int ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				if (ch == 75) //左
				{
					if (recordBoard.regretSingle(gameBoard.chessBoard) == true)
					{
						gameBoard.printBoard();
						order = !order;
						hintBoard.printHint1(order); // 輪轉時，hint1換方，hint2隱藏，hint3判斷
						recordBoard.clearBoard();
						recordBoard.printMsg();
						if (gameBoard.isGeneral(order)) hintBoard.printHint3(order);
						else hintBoard.hideHint3();
						
					}
				}
				else if (ch == 77)
				{
					if (recordBoard.reductionSingle(gameBoard.chessBoard) == true)
					{
						gameBoard.printBoard();
						order = !order;
						hintBoard.printHint1(order); // 輪轉時，hint1換方，hint2隱藏，hint3判斷
						recordBoard.clearBoard();
						recordBoard.printMsg();
						if (gameBoard.isGeneral(order)) hintBoard.printHint3(order);
						else hintBoard.hideHint3();
					}
				}
			}
			else if (ch == 27) // Esc
			{
				int escModeValue = escBoard.escMenuReplay();
				if (escModeValue == 0)      // 0.繼續遊戲
				{
					gameBoard.printBoard();
				}
				else if (escModeValue == 1) // 1.儲存遊戲
				{
					// 儲存遊戲
					fileName = "";
					saveGame(0);
					gameBoard.printBoard();
				}
				else if (escModeValue == 2) // 2.回主選單
				{
					mode = 0;
					return;
				}
			}
		}
	}
	setCursorSize(true, 0);

}

// 提示檔名視窗
void ChineseChess::saveGameSuccess(void)
{
	printFrame(subWindow[0], subWindow[1], subWindow[2], subWindow[3] + 2, L"檔　案　儲　存　成　功");
	setCursor(subWindow[0] + 2, subWindow[1] + 2);
	wcout << L"檔名: ";
	cout << fileName;
	setCursor(subWindow[0] + subWindow[2] - 10, subWindow[1] + 5);
	wcout << L"按任意鍵以繼續操作";
	while (true)
	{
		if (_kbhit())
		{
			_getch();
			break;
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

