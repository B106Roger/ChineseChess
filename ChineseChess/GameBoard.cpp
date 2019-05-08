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
	ChineseChess::setCursor(startX, startY);
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
int GameBoard::movingChess(int x, int y)
{
	// 1 => 帥被吃  2 => 將被吃  0 => 遊戲還沒結束
	for (int i = 0; i < colorBoard.size(); i++)
	{
		for (int j = 0; j < colorBoard[0].size(); j++)
		{
			if (colorBoard[i][j] == 1)
			{
				int returnValue = 0;
				if (chessBoard[y][x] == 1 || chessBoard[y][x] == 8)
				{
					returnValue = 1;
				}
				chessBoard[y][x] = chessBoard[i][j];
				chessBoard[i][j] = 0;
				resetColorBoard();
				printBoard();
				return returnValue;
			}
		}
	}
}

// 移動(顯示可走位置)士
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

// 移動(顯示可走位置)馬
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

// 移動(顯示可走位置)象
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

// 移動(顯示可走位置)將軍
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

// 移動(顯示可走位置)車
void GameBoard::moveTank(int x, int  y) {
	int targetChess = chessBoard[y][x];
	colorBoard[y][x] = 1;

	if (targetChess == 4) { // 黑方(1-7上方)
		// 上下左右
		for (int boardY = y; boardY >= 0; boardY--) { // 上
			if (chessBoard[boardY][x] == targetChess) {
				if(colorBoard[boardY][x] == 1) continue; //自己
				else if (colorBoard[boardY][x] == 0) break; // 同樣是車
			}
			else if (chessBoard[boardY][x] == 0) { // 無人
				colorBoard[boardY][x] = -1;
			}
			else if (chessBoard[boardY][x] <= 7) { //我方擋
				break;
			}
			else if (chessBoard[boardY][x] <= 14) {// 敵方擋
				colorBoard[boardY][x] = -2;
				break;
			}
			
		}
		for (int boardY = y; boardY <= 9; boardY++) { // 下
			if (chessBoard[boardY][x] == targetChess) {
				if (colorBoard[boardY][x] == 1) continue; //自己
				else if (colorBoard[boardY][x] == 0) break; // 同樣是車
			}
			else if (chessBoard[boardY][x] == 0) { // 無人(0)
				colorBoard[boardY][x] = -1;
			}
			else if (chessBoard[boardY][x] <= 7) { //我方擋(1-7)
				break;
			}
			else if (chessBoard[boardY][x] <= 14) {// 敵方擋(8-14)
				colorBoard[boardY][x] = -2;
				break;
			}
		}
		for (int boardX = x; boardX >= 0; boardX--) { // 左
			if (chessBoard[y][boardX] == targetChess) {
				if (colorBoard[y][boardX] == 1) continue; //自己
				else if (colorBoard[y][boardX] == 0) break; // 同樣是車
			}
			else if (chessBoard[y][boardX] == 0) { // 無人
				colorBoard[y][boardX] = -1;
			}
			else if (chessBoard[y][boardX] <= 7) { //我方擋
				break;
			}
			else if (chessBoard[y][boardX] <= 14) {// 敵方擋
				colorBoard[y][boardX] = -2;
				break;
			}

		}
		for (int boardX = x; boardX <= 8; boardX++) { // 右
			if (chessBoard[y][boardX] == targetChess) {
				if (colorBoard[y][boardX] == 1) continue; //自己
				else if (colorBoard[y][boardX] == 0) break; // 同樣是車
			}
			else if (chessBoard[y][boardX] == 0) { // 無人(0)
				colorBoard[y][boardX] = -1;
			}
			else if (chessBoard[y][boardX] <= 7) { //我方擋(1-7)
				break;
			}
			else if (chessBoard[y][boardX] <= 14) {// 敵方擋(8-14)
				colorBoard[y][boardX] = -2;
				break;
			}

		}
	}
	else if (targetChess == 11) { // 紅方(8-14下方)
		for (int boardY = y; boardY >= 0; boardY--) { // 上
			if (chessBoard[boardY][x] == targetChess) {
				if (colorBoard[boardY][x] == 1) continue; //自己
				else if (colorBoard[boardY][x] == 0) break; // 同樣是車
			}
			else if (chessBoard[boardY][x] == 0) { // 無人
				colorBoard[boardY][x] = -1;
			}
			else if (chessBoard[boardY][x] <= 7) { // 敵方擋
				colorBoard[boardY][x] = -2;
				break;
			}
			else if (chessBoard[boardY][x] <= 14) {// 我方擋
				
				break;
			}

		}
		for (int boardY = y; boardY <= 9; boardY++) { // 下
			if (chessBoard[boardY][x] == targetChess) {
				if (colorBoard[boardY][x] == 1) continue; //自己
				else if (colorBoard[boardY][x] == 0) break; // 同樣是車
			}
			else if (chessBoard[boardY][x] == 0) { // 無人(0)
				colorBoard[boardY][x] = -1;
			}
			else if (chessBoard[boardY][x] <= 7) { // 敵方擋(1-7)
				colorBoard[boardY][x] = -2;
				break;
			}
			else if (chessBoard[boardY][x] <= 14) {//我方擋(8-14)
				break;
			}
		}
		for (int boardX = x; boardX >= 0; boardX--) { // 左
			if (chessBoard[y][boardX] == targetChess) {
				if (colorBoard[y][boardX] == 1) continue; //自己
				else if (colorBoard[y][boardX] == 0) break; // 同樣是車
			}
			else if (chessBoard[y][boardX] == 0) { // 無人
				colorBoard[y][boardX] = -1;
			}
			else if (chessBoard[y][boardX] <= 7) { // 敵方擋
				colorBoard[y][boardX] = -2;
				break;
			}
			else if (chessBoard[y][boardX] <= 14) { //我方擋
				break;
			}

		}
		for (int boardX = x; boardX <= 8; boardX++) { // 右
			if (chessBoard[y][boardX] == targetChess) {
				if (colorBoard[y][boardX] == 1) continue; //自己
				else if (colorBoard[y][boardX] == 0) break; // 同樣是車
			}
			else if (chessBoard[y][boardX] == 0) { // 無人(0)
				colorBoard[y][boardX] = -1;
			}
			else if (chessBoard[y][boardX] <= 7) { // 敵方擋(1-7)
				colorBoard[y][boardX] = -2;
				break;
			}
			else if (chessBoard[y][boardX] <= 14) {// 我方擋(8-14)
				
				break;
			}

		}
	}
}

// 移動(顯示可走位置)炮
void GameBoard::moveCannon(int x, int y) {
	int targetChess = chessBoard[y][x];
	colorBoard[y][x] = 1;

	if (targetChess == 6) { // 黑方(1-7上方)
		// 上下左右
		int turret = 0; // 炮架
		for (int boardY = y; boardY >= 0; boardY--) { // 上
			if (turret == 0) { // 無炮架
				if(chessBoard[boardY][x] == 0) colorBoard[boardY][x] = -1; // 無人
				else if (chessBoard[boardY][x] != 0 && colorBoard[boardY][x] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[boardY][x] == 0) continue; // 無人
				else if (chessBoard[boardY][x] <= 7) break; // 我方
				else if (chessBoard[boardY][x] <= 14) { // 敵方
					colorBoard[boardY][x] = -2;
					break;
				}
			}
		}
		turret = 0; // 炮架
		for (int boardY = y; boardY <= 9; boardY++) { // 下
			if (turret == 0) { // 無炮架
				if (chessBoard[boardY][x] == 0) colorBoard[boardY][x] = -1; // 無人
				else if (chessBoard[boardY][x] != 0 && colorBoard[boardY][x] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[boardY][x] == 0) continue; // 無人
				else if (chessBoard[boardY][x] <= 7) break; // 我方
				else if (chessBoard[boardY][x] <= 14) { // 敵方
					colorBoard[boardY][x] = -2;
					break;
				}
			}
		}
		turret = 0; // 炮架
		for (int boardX = x; boardX >= 0; boardX--) { // 左
			if (turret == 0) { // 無炮架
				if (chessBoard[y][boardX] == 0) colorBoard[y][boardX] = -1; // 無人
				else if (chessBoard[y][boardX] != 0 && colorBoard[y][boardX] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[y][boardX] == 0) continue; // 無人
				else if (chessBoard[y][boardX] <= 7) break; // 我方
				else if (chessBoard[y][boardX] <= 14) { // 敵方
					colorBoard[y][boardX] = -2;
					break;
				}
			}
		}
		turret = 0; // 炮架
		for (int boardX = x; boardX <= 8; boardX++) { // 右
			if (turret == 0) { // 無炮架
				if (chessBoard[y][boardX] == 0) colorBoard[y][boardX] = -1; // 無人
				else if (chessBoard[y][boardX] != 0 && colorBoard[y][boardX] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[y][boardX] == 0) continue; // 無人
				else if (chessBoard[y][boardX] <= 7) break; // 我方
				else if (chessBoard[y][boardX] <= 14) { // 敵方
					colorBoard[y][boardX] = -2;
					break;
				}
			}
		}
	}
	else if (targetChess == 13) { // 紅方(8-14下方)
		int turret = 0; // 炮架
		for (int boardY = y; boardY >= 0; boardY--) { // 上
			if (turret == 0) { // 無炮架
				if (chessBoard[boardY][x] == 0) colorBoard[boardY][x] = -1; // 無人
				else if (chessBoard[boardY][x] != 0 && colorBoard[boardY][x] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[boardY][x] == 0) continue; // 無人
				else if (chessBoard[boardY][x] <= 7) { // 敵方
					colorBoard[boardY][x] = -2;
					break;
				}
				else if (chessBoard[boardY][x] <= 14) { // 我方
					break;
				}
			}

		}
		turret = 0; // 炮架
		for (int boardY = y; boardY <= 9; boardY++) { // 下
			if (turret == 0) { // 無炮架
				if (chessBoard[boardY][x] == 0) colorBoard[boardY][x] = -1; // 無人
				else if (chessBoard[boardY][x] != 0 && colorBoard[boardY][x] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[boardY][x] == 0) continue; // 無人
				else if (chessBoard[boardY][x] <= 7) { // 敵方
					colorBoard[boardY][x] = -2;
					break;
				}
				else if (chessBoard[boardY][x] <= 14) { // 我方
					break;
				}
			}
		}
		turret = 0; // 炮架
		for (int boardX = x; boardX >= 0; boardX--) { // 左
			if (turret == 0) { // 無炮架
				if (chessBoard[y][boardX] == 0) colorBoard[y][boardX] = -1; // 無人
				else if (chessBoard[y][boardX] != 0 && colorBoard[y][boardX] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[y][boardX] == 0) continue; // 無人
				else if (chessBoard[y][boardX] <= 7) {// 敵方
					colorBoard[y][boardX] = -2;
					break; 
				}
				else if (chessBoard[y][boardX] <= 14) { // 我方
					
					break;
				}
			}

		}
		turret = 0; // 炮架
		for (int boardX = x; boardX <= 8; boardX++) { // 右
			if (turret == 0) { // 無炮架
				if (chessBoard[y][boardX] == 0) colorBoard[y][boardX] = -1; // 無人
				else if (chessBoard[y][boardX] != 0 && colorBoard[y][boardX] != 1) turret = 1; // 有任何不是自己的人
			}
			else if (turret == 1) { // 有炮架
				if (chessBoard[y][boardX] == 0) continue; // 無人
				else if (chessBoard[y][boardX] <= 7) {// 敵方
					colorBoard[y][boardX] = -2;
					break;
				}
				else if (chessBoard[y][boardX] <= 14) { // 我方

					break;
				}
			}
		}
	}
}

// 移動(顯示可走位置)卒
void GameBoard::moveSolider(int x, int y) {
	int targetChess = chessBoard[y][x];
	colorBoard[y][x] = 1;

	if (targetChess == 7) {
		if (y < 5) { // 河內
			if (chessBoard[y + 1][x] > 7) { // 8-14敵方
				colorBoard[y + 1][x] = -2;
			}
			else if (chessBoard[y + 1][x] == 0) { // 無人
				colorBoard[y + 1][x] = -1;
			}
		}
		else if (y >= 5) { //過河
			for (int boardY = y; boardY <= y + 1; boardY++) { // 向前
				for (int boardX = x - 1; boardX <= x + 1; boardX++) { // 左1右1
					if ((boardY == y && boardX == x) || (boardY < 0) || (boardX < 0) || (boardY > 9) || (boardX > 8) || (boardY == y+1 && (boardX == x-1||boardX == x+1))) continue; // 自己或是在棋盤外或是斜行
					else if(chessBoard[boardY][boardX] == 0) colorBoard[boardY][boardX] = -1;
					else if (chessBoard[boardY][boardX] <= 7) continue;
					else if(chessBoard[boardY][boardX] <= 14) colorBoard[boardY][boardX] = -2;
				}
			}
		}
	}
	else if (targetChess == 14) {
		if (y >= 5) { // 河內
			if (chessBoard[y - 1][x] == 0) { // 無人
				colorBoard[y - 1][x] = -1;
			}
			else if (chessBoard[y - 1][x] <= 7) { // 1-7敵方
				colorBoard[y - 1][x] = -2;
			}
			
		}
		else if (y < 5) { //過河
			for (int boardY = y; boardY >= y - 1; boardY--) { // 向前↑(負)
				for (int boardX = x - 1; boardX <= x + 1; boardX++) { // 左1右1
					if ((boardY == y && boardX == x) || (boardY < 0) || (boardX < 0) || (boardY > 9) || (boardX > 8) || (boardY == y - 1 && (boardX == x - 1 || boardX == x + 1))) continue; // 自己或是在棋盤外或是斜行
					else if (chessBoard[boardY][boardX] == 0) colorBoard[boardY][boardX] = -1;
					else if (chessBoard[boardY][boardX] <= 7) colorBoard[boardY][boardX] = -2;
					else if (chessBoard[boardY][boardX] <= 14) continue;
				}
			}
		}
	}
}

// 是否將軍，若將軍已經被吃，仍然回傳false
bool GameBoard::isGeneral(int order) {

	if (order == 0) { // 黑方被將軍了嗎？
		int generalY = -1, generalX = -1;
		for (int boardY = 0; boardY <= 2 && generalY == -1; boardY++){ // 步驟一：找到將
			for (int boardX = 3; boardX <= 5 && generalX == -1; boardX++){
				if (chessBoard[boardY][boardX] == 1) {
					generalY = boardY;
					generalX = boardX;
					break;
				}
			}
		}
		if (generalY == -1 && generalX == -1) return false;
		for (int boardY = 0; boardY <= 9; boardY++) { // 步驟二：將敵方掃過一輪
			for (int boardX = 0; boardX <= 8; boardX++) {
				if (chessBoard[boardY][boardX] > 7) {
					moveChessWithoutPrintBoard(boardX, boardY);
					if (colorBoard[generalY][generalX] == -2) {
						resetColorBoard();
						return true;
					}
					resetColorBoard();
				}
			}
		}
		return false;
	}
	
	else if (order == 1) { // 紅方被將軍了嗎？
		int generalY = -1, generalX = -1;
		for (int boardY = 7; boardY <= 9 && generalY == -1; boardY++) { // 步驟一：找到將
			for (int boardX = 3; boardX <= 5 && generalX == -1; boardX++) {
				if (chessBoard[boardY][boardX] == 8) {
					generalY = boardY;
					generalX = boardX;
					break;
				}
			}
		}
		if (generalY == -1 && generalX == -1) return false;
		for (int boardY = 0; boardY <= 9; boardY++) { // 步驟二：將敵方掃過一輪
			for (int boardX = 0; boardX <= 8; boardX++) {
				if (0 < chessBoard[boardY][boardX] && chessBoard[boardY][boardX] <= 7) {
					moveChessWithoutPrintBoard(boardX, boardY);
					if (colorBoard[generalY][generalX] == -2) {
						resetColorBoard();
						return true;
					}
					resetColorBoard();
				}
			}
		}
		return false;
	}
}
void GameBoard::moveChessWithoutPrintBoard(int x, int y) {
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
}

// 新遊戲
void GameBoard::resetChessBoard()
{
	chessBoard[0] = { 4,5,3,2,1,2,3,5,4 };
	chessBoard[1] = { 0,0,0,0,0,0,0,0,0 };;
	chessBoard[2] = { 0,6,0,0,0,0,0,6,0 };
	chessBoard[3] = { 7,0,7,0,7,0,7,0,7 };
	chessBoard[4] = { 0,0,0,0,0,0,0,0,0 };
	chessBoard[5] = { 0,0,0,0,0,0,0,0,0 };
	chessBoard[6] = { 14,0,14,0,14,0,14,0,14 };
	chessBoard[7] = { 0,13,0,0,0,0,0,13,0 };
	chessBoard[8] = { 0,0,0,0,0,0,0,0,0 };
	chessBoard[9] = { 11,12,10,9,8,9,10,12,11 };

}

// 讓chineseChess的saveGame()呼叫
void GameBoard::saveChessBoard(string fileName, int order) {
	fstream outputFile(fileName, ios::out);
	if (!outputFile.is_open()) cout << "fail open" << endl;
	for (int i = 0; i < chessBoard.size(); i++) {
		for (int j = 0; j < chessBoard[i].size(); j++) {
			outputFile << chessBoard[i][j] << " ";
		}
	}
	outputFile << order;
	outputFile.close();
}