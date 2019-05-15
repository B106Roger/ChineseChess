#pragma once
#include "GameBoard.h"
#include "RecordBoard.h"
#include "HintBoard.h"
#include "EscBoard.h"
#include "MenuBoard.h"
#include "WinBoard.h"
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include <time.h>
using namespace std;

class ChineseChess
{
public:
	// constructor
	ChineseChess();
	~ChineseChess();

	// data member
	                          // [ 主選單模式  遊戲模式   Esc模式   重播模式     離開     ]
	int mode;                 // [  MenuMode , GameMode , EscMode , ReplayMode , ExitMode ]
	int order = 0;            // 0 黑方先  1 紅方先

	const int startX = 0;     // 視窗左上角x,y視窗
	const int startY = 0;     
	const int width = 64;     // 視窗長寬
	const int height = 36;
	static GameBoard gameBoard;
	static RecordBoard recordBoard;
	static HintBoard hintBoard;
	static EscBoard escBoard;
	static MenuBoard maenuBoard;
	vector<int> subWindow;   // X,Y,width,height
	
	static string fileName;  // 所讀取的檔案名稱
	// member function
	void gameLoop(void);     // 遊戲流程迴圈
	void gameStart(void);    // 遊戲模式: 遊戲開始迴圈
	void printFrame(int xpos, int ypos, int xsize, int ysize, wstring title = L""); // 印出框框
	void printArtSleep();
	void printArt();

	int smallWindow(wstring title);    // 印出悔棋還原的確認視窗
	int fileWindow();                  // 主選單模式-繼續遊戲: 輸入檔名視窗
	int readAndSetBoard(string name);  // 主選單模式-繼續遊戲: 讀檔程式
	int replayWindow();                // 重播模式: 輸入檔名視窗
	int readAndSetBoard2(string name); // 重播模式: 讀檔程式
	void replayMode();                 // 重播模式: 顯示棋盤、提示版、紀錄板
	void newGame();                    // 主選單模式-雙人遊戲: reset 棋盤、提示版、紀錄板
	void saveGame(int finished);       // Esc模式-儲存遊戲: 儲存遊戲程式
	void saveGameSuccess(void);        // Esc模式-儲存遊戲: 提示儲存檔案的名稱



	// 以下皆為console視窗設定函數
	// 0 黑, 1 藍, 2 綠, 3淺藍, 4 紅, 5 紫, 6土黃, 7 白灰, 8 灰, 9 亮藍,10亮綠, 11亮淺藍, 12淺紅, 13淺粉, 14淺黃 15 白
	static void SetColor(int fontColor = 7, int backgroundColor = 0);
	static void setCursor(int x, int y);
	void getCursor(int &x, int &y);
	static void setCursorSize(bool visible, DWORD size); // visible = 0/1
};