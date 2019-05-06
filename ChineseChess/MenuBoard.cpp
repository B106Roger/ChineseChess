#include "MenuBoard.h"
#include"ChineseChess.h"


MenuBoard::MenuBoard(int cursorX, int cursorY, int arg_width, int arg_height, int iniMode)
{
	cursor.push_back(cursorX);
	cursor.push_back(cursorY);
	size.push_back(arg_width);
	size.push_back(arg_height);
}


MenuBoard::~MenuBoard()
{
}
// �D���Ҧ�
int MenuBoard::mainMenu()
{
	breakOut = false; // �j��}�l
	printBoard(); // �L�X���
	while (!breakOut) {
		if (_kbhit())
		{
			int ch = _getch();
			// ���UEnter���
			if (ch == '\r')
			{
				int returnValue;
				switch (mode) {
				case 1:        // ���H�C��
					returnValue =  1;             // ChineseChess.mode ��GameMode
					break;
				case 2:        // �~��C��(Ū���ѽL)
					returnValue = 1;              // ChineseChess.mode ��GameMode
					break;
				case 3:        // �����ɧ�
					returnValue = 1;
					break;
				case 4:        // ���}�C��
					ChineseChess::setCursorSize(true, 0); // �k�ٴ��
					returnValue = 3; 
				}
				ChineseChess::setCursorSize(true, 0);
				return returnValue;
			}
			// ���U��V���
			else if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72: // �W
					if (mode == 1) mode = 4;
					else --mode;
					break;
				case 80: // �U
					if (mode == 4) mode = 1;
					else ++mode;
					break;
				};
				printSelect(); // ��s�w����ﶵ��m
			}
		}
	}
}

// �L�X�D���~��
void MenuBoard::printBoard()
{
	// ���ô��
	ChineseChess::setCursorSize(false, 0);
	int frameWidth = size[0];
	int frameHeight = size[1];
	ChineseChess::SetColor(9, 0);
	for (int i = 0; i < frameHeight; i++) {
		ChineseChess::setCursor(cursor[0], cursor[1] + i);
		for (int j = 0; j < frameWidth; j++) {
			if (i == 0 || i == frameHeight - 1 || i % 2 == 0) // �W
			{
				if (j == 0) wcout << L"��";// ���W��
				else if (j == frameWidth - 1) wcout << L"��";// �k�W��
				else wcout << L"��";// �W��
			}
			else// ��
			{
				if (j == 0 || j == frameWidth - 1) wcout << L"��";// ����
				else wcout << L"�@"; // 
			}
		}
	}
	ChineseChess::SetColor();
	printSelect();
}

// �L�X�D���ﶵ
void MenuBoard::printSelect() {

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 1);
	if (mode == 1) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"���H�C��";

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 3);
	if (mode == 2) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"�~��C��";

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 5);
	if (mode == 3) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"�����ѧ�";

	ChineseChess::setCursor(cursor[0] + 8, cursor[1] + 7);
	if (mode == 4) ChineseChess::SetColor(0, 15);
	else ChineseChess::SetColor();
	wcout << L"���}�C��";
}