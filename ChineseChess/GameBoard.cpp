#include "GameBoard.h"
#include"ChineseChess.h"
#include<Windows.h>
#include"Chess.h"
#include<algorithm>
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
				if (colorBoard[y][x] == -2)
				{
					//                         灰底紅字:灰底黑字
					backgroundColor = 9;
					fontColor = (chessBoard[y][x] > 7 ? 12 : 0);
				}
				// 如果是不能被吃掉的旗子
				else// if (colorBoard[y][x] == 0)
				{
					// 正常的棋子              灰底紅字:灰底黑色
					backgroundColor = 7;
					fontColor = (chessBoard[y][x] > 7 ? 12 : 0);
				}
			}
			// 如果上面沒棋子
			else
			{
				// 可移動的格子
				if (colorBoard[y][x] == -1)
				{
					// 空白部分 白底灰字
					fontColor = 0;
					backgroundColor = 7;
				}
				// 不可移動的格子
				else
				{
					// 空白部分 白底黑字
					fontColor = 0;
					backgroundColor = 15;
				}
			}
			ChineseChess::SetColor(fontColor, backgroundColor);
		}
		wcout << getPrintedChar(rowIndex, j);
	}
	ChineseChess::SetColor();
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

// 提示旗子可移動位置 + 重印GameBoard
void GameBoard::moveChess(int x, int y)
{
	int targetChess = chessBoard[y][x];
	resetColorBoard();
	int deltaChess = 7;
	// 黑士  紅士
	if (targetChess == 2 || targetChess == 9)
	{
		moveKnight(x, y);
	}
	// 黑象  紅象
	else if (targetChess == 3 || targetChess == 10)
	{
		moveElephant(x, y);
	}
	// 黑馬  紅馬
	else if (targetChess == 5 || targetChess == 12)
	{
		moveHorse(x, y);
	}
	// 將
	else if (targetChess == 1 || targetChess == 1 + deltaChess)
	{
		moveGeneral(x, y);
	}
	// 車
	else if (targetChess == 4 || targetChess == 4 + deltaChess)
	{
		moveTank(x, y);
	}
	// 炮
	else if (targetChess == 6 || targetChess == 6 + deltaChess)
	{
		moveCannon(x, y);
	}
	// 卒
	else if (targetChess == 7 || targetChess == 7 + deltaChess)
	{
		moveSolider(x, y);
	}
	printBoard();

}

// 重設colorBoard顏色
void GameBoard::resetColorBoard(void)
{
	for (int i = 0; i < colorBoard.size(); i++)
	{
		for (int j = 0; j < colorBoard[0].size(); j++)
		{
			colorBoard[i][j] = 0;
		}
	}
}

// 移動棋子 + 重印GameBoard
void GameBoard::movingChess(int x, int y)
{
	for (int i = 0; i < colorBoard.size(); i++)
	{
		for (int j = 0; j < colorBoard[0].size(); j++)
		{
			if (colorBoard[i][j] == 1)
			{
				chessBoard[y][x] = chessBoard[i][j];
				chessBoard[i][j] = 0;
				resetColorBoard();
				printBoard();
				return;
			}
		}
	}
}

// 移動士
void GameBoard::moveKnight(int x, int y)
{
	int targetChess = chessBoard[y][x];
	colorBoard[y][x] = 1;
	// 黑士
	if (targetChess == 2)
	{
		for (int boardY = 0; boardY <= 2; boardY++)
		{
			for (int boardX = 3; boardX <= 5; boardX++)
			{
				if (abs(boardX - x) == 1 && abs(boardY - y) == 1)
				{
					if (chessBoard[boardY][boardX] == 0)
					{
						colorBoard[boardY][boardX] = -1;
					}
					else if (chessBoard[boardY][boardX] > 7)
					{
						colorBoard[boardY][boardX] = -2;
					}
				}
			}
		}
	}
	// 紅士
	else if (targetChess == 9)
	{
		for (int boardY = 7; boardY <= 9; boardY++)
		{
			for (int boardX = 3; boardX <= 5; boardX++)
			{
				if (abs(boardX - x) == 1 && abs(boardY - y) == 1)
				{
					if (chessBoard[boardY][boardX] == 0)
					{
						colorBoard[boardY][boardX] = -1;
					}
					else if (chessBoard[boardY][boardX] <= 7)
					{
						colorBoard[boardY][boardX] = -2;
					}
				}
			}
		}
	}
}

// 移動馬
void GameBoard::moveHorse(int x, int y)
{
	// 呼叫此function 前必須確認棋子馬
	// 大於7表示紅色，否則為黑色
	int targetChessColor = chessBoard[y][x] > 7;
	colorBoard[y][x] = 1;
	// 決定for loop 範圍
	const int positionStartX = max(0, x - 2), positionStartY = max(0, y - 2);
	const int positionEndX = min(8, x + 2), positionEndY = min(9, y + 2);

	for (int positionY = positionStartY; positionY <= positionEndY; positionY++)
	{
		for (int positionX = positionStartX; positionX <= positionEndX; positionX++)
		{
			if (chessBoard[positionY][positionX] != 0 && ((chessBoard[positionY][positionX] > 7) == targetChessColor))
			{
				// 如果跟自己同色的棋字就跳過此次判斷
				continue;
			}
			// 可移動的位置
			if (abs(positionX - x) == 1 && abs(positionY - y) == 2)
			{
				// 檢查拐馬腳
				if ((positionY > y && chessBoard[positionY - 1][x] == 0) 
					|| (positionY < y && chessBoard[positionY + 1][x] == 0))
				{
					colorBoard[positionY][positionX] = (chessBoard[positionY][positionX] == 0 ? -1 : -2);
				}
			}
			else if (abs(positionX - x) == 2 && abs(positionY - y) == 1)
			{
				// 檢查拐馬腳
				if ((positionX > x && chessBoard[y][positionX - 1] == 0)
					|| (positionX < x && chessBoard[y][positionX + 1] == 0))
				{
					colorBoard[positionY][positionX] = (chessBoard[positionY][positionX] == 0 ? -1 : -2);
				}
			}
		}
	}
}

// 移動象
void GameBoard::moveElephant(int x, int y)
{
	int targetChessColor = chessBoard[y][x] > 7;
	int region = targetChessColor == 1 ? 5 : 0;
	colorBoard[y][x] = 1;
	// 決定for loop 範圍
	const int positionStartX =0, positionStartY =0 + region;
	const int positionEndX = 8, positionEndY = 4 + region;

	for (int positionY = positionStartY; positionY <= positionEndY; positionY++)
	{
		for (int positionX = positionStartX; positionX <= positionEndX; positionX++)
		{
			if (chessBoard[positionY][positionX] != 0 && ((chessBoard[positionY][positionX] > 7) == targetChessColor))
			{
				// 如果跟自己同色的棋字就跳過此次判斷
				continue;
			}
			if (abs(positionX - x) == 2 && abs(positionY - y) == 2)
			{
				// 檢查拐象眼
				int middleX = (x + positionX) / 2;
				int middleY = (y + positionY) / 2;
				if (chessBoard[middleY][middleX] == 0)
				{
					colorBoard[positionY][positionX] = (chessBoard[positionY][positionX] == 0 ? -1 : -2);
				}
			}
		}
	}
}

void GameBoard::moveGeneral(int x, int y) {
	int targetChess = chessBoard[y][x];
	colorBoard[y][x] = 1;

	// 只能在九宮內行走(直行或橫行)
	// 王見王

	if (targetChess == 1) { // 黑方(上方)
		for (int boardY = 0; boardY <= 2; boardY++) // 由下到上
		{
			for (int boardX = 3; boardX <= 5; boardX++) // 由左到右
			{
				// 若該格子在將的上/下
				if (abs(boardX - x) == 1 && abs(boardY - y) == 0) {
					// 沒人(0)，灰色
					if (chessBoard[boardY][boardX] == 0)
					{
						colorBoard[boardY][boardX] = -1;
					}
					// 敵人(8-14)，藍色
					else if (chessBoard[boardY][boardX] > 7) // 0被排除了
					{
						colorBoard[boardY][boardX] = -2;
					}
					// 其他：我方(1-7)
				}
				// 格子在將的左/右
				else if (abs(boardX - x) == 0 && abs(boardY - y) == 1) {
					// 沒人(0)，灰色
					if (chessBoard[boardY][boardX] == 0)
					{
						colorBoard[boardY][boardX] = -1;
					}
					// 敵人(8-14)，就為藍色
					else if (chessBoard[boardY][boardX] > 7)
					{
						colorBoard[boardY][boardX] = -2;
					}
					// 其他：我方(1-7)
				}
			}// inner-for
		}// outer-for

		//若可以直視紅帥(從黑將到紅帥上整條路上沒棋子)，則紅帥格子為藍色
		for (int boardY = y; boardY <= 9; boardY++) {
			if (chessBoard[boardY][x] == 1) continue; // 黑將，繼續
			else if (chessBoard[boardY][x] == 8) { // 找到紅帥了，塗色，結束
				colorBoard[boardY][x] = -2;
				break;
			}
			else if(chessBoard[boardY][x] != 0) break; // 有棋子，結束判斷
			// 其他，沒任何棋子
		}
	}//黑方
	else if(targetChess == 8){ // 紅方(下方)
		for (int boardY = 7; boardY <= 9; boardY++)
		{
			for (int boardX = 3; boardX <= 5; boardX++)
			{
				// 格子在將的上/下
				if (abs(boardX - x) == 1 && abs(boardY - y) == 0) {
					// 沒人(0)，灰色
					if (chessBoard[boardY][boardX] == 0)
					{
						colorBoard[boardY][boardX] = -1;
					}
					// 敵人(1-7)，藍色
					else if (chessBoard[boardY][boardX] <= 7)
					{
						colorBoard[boardY][boardX] = -2;
					}
					// 其他：我方(8-14)
				}
				// 格子在將的左/右
				else if (abs(boardX - x) == 0 && abs(boardY - y) == 1) {
					// 沒人(0)，灰色
					if (chessBoard[boardY][boardX] == 0)
					{
						colorBoard[boardY][boardX] = -1;
					}
					// 敵人(1-7)，藍色
					else if (chessBoard[boardY][boardX] <= 7)
					{
						colorBoard[boardY][boardX] = -2;
					}
					// 其他：我方(8-14)
				}
			}// inner-for
		}//outer-for

		//若可以直視黑將(從紅帥到黑將上整條路上沒棋子)，則黑將格子為藍色
		for (int boardY = y; boardY >= 0; boardY--) {
			if (chessBoard[boardY][x] == 8) continue; // 紅帥，繼續
			else if (chessBoard[boardY][x] == 1) { // 找到黑將了，塗色，結束
				colorBoard[boardY][x] = -2;
				break;
			}
			else if (chessBoard[boardY][x] != 0) break; // 有棋子，結束判斷
			// 其他，沒任何棋子
		}
	}//紅方
}
void GameBoard::moveTank(int x, int  y) {

}
void GameBoard::moveCannon(int x, int y) {

}
void GameBoard::moveSolider(int x, int y) {

}