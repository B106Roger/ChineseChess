﻿#include <iostream>
#include <locale>
#include<conio.h>
#include<Windows.h>
#include"ChineseChess.h"
#include"RecordBoard.h"
using namespace std;

int main(void)
{
	locale loc("chs");
	setlocale(LC_ALL, "chs");
	wcout.imbue(loc);

	
	//wcout << L"╠ ═ ╬ ═ ╣╠ ═ ╬ ═ ╣╠ ═ ╬ ═ ╣╠ ═ ╬ ═ ╣╠ ═ ╬ ═ ╣" << endl;
	//wcout << L"╠ ═ ╬ ═ ╣" << endl;
	//wcout << L"╚ ═ ╩ ═ ╝" << endl;


	//wcout << L"║   │   │   │　 │   │   │   │   ║" << endl;
	//wstring a(L"１　２　３　４　５　６　７　８");
	//wstring b(L"車═ 車═ 車═ 車═ 車═ 車═ 車═ 車═ 車");
	//wstring c(L"║   │   │   │ ＼│ ／│   │   │   ║");
	//wstring d(L"║ —┼ —┼ —┼ —┼ —┼ —┼ —┼ —║");
	//wstring e(L"║   │   │   │　 │   │   │   │   ║");
	//wstring f(L"║ —┼ —炮—┼ —┼ —┼ —炮—┼ —║");
	//wstring g(L"║   │   │   │　 │   │   │   │   ║");
	//wstring h(L"炮—┼ —┼ —┼ —┼ —┼ —┼ —┼ —║");
	//wstring i(L"║   │   │   │　 │   │   │   │   ║");
	//wstring j(L"║ —┴ —┴ —┴ —┴ —┴ —┴ —┴ —║");
	//wstring k(L"║     楚 河            漢 界    ║ ");
	//wstring l(L"║ —┬ —┬ —┬ —┬ —┬ —┬ —┬ —║");
	//wstring m(L"║   │   │   │　 │   │   │   │   ║");
	//wstring n(L"║ —┼ —┼ —┼ —┼ —┼ —┼ —┼ —║");
	//wstring o(L"║   │   │   │　 │   │   │   │   ║");
	//wstring p(L"║ —┴ —┴ —┴ —┴ —┴ —┴ —┴ —║");
	//wstring q(L"║   │   │   │　 │   │   │   │   ║");
	//wstring r(L"車═ 車═ 車═ 車═ 車═ 車═ 車═ 車═ 車");
	//wstring s(L"一　二　三　四　五　六　七　八");
	//wcout << a << endl;
	//wcout << b << endl;
	//wcout << c << endl;
	//wcout << d << endl;
	//wcout << e << endl;
	//wcout << f << endl;
	//wcout << g << endl;
	//wcout << h << endl;
	//wcout << i << endl;
	//wcout << j << endl;
	//wcout << k << endl;
	//wcout << l << endl;
	//wcout << m << endl;
	//wcout << n << endl;
	//wcout << o << endl;
	//wcout << p << endl;
	//wcout << q << endl;
	//wcout << r << endl;
	//wcout << s << endl;
	//

	ChineseChess newGame;
	newGame.gameStart();

	return 0;
}