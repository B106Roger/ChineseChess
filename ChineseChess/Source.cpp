#include <iostream>
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


	wcout << L"ùà ùù ùá ùù ùâ" << endl;
	wcout << L"ùà ùù ùá ùù ùâ" << endl;
	wcout << L"ùã ùù ùä ùù ùå" << endl;


	//wcout << L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø" << endl;
	wstring a(L"¢°¡@¢±¡@¢²¡@¢³¡@¢´¡@¢µ¡@¢¶¡@¢·");
	wstring b(L"¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®");
	wstring c(L"ùø   ¢x   ¢x   ¢x ¢@¢x ¡þ¢x   ¢x   ¢x   ùø");
	wstring d(L"ùø ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡Xùø");
	wstring e(L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø");
	wstring f(L"ùø ¡X¢q ¡X¬¶¡X¢q ¡X¢q ¡X¢q ¡X¬¶¡X¢q ¡Xùø");
	wstring g(L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø");
	wstring h(L"¬¶¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡Xùø");
	wstring i(L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø");
	wstring j(L"ùø ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡Xùø");
	wstring k(L"ùø     ·¡ ªe            º~ ¬É    ùø ");
	wstring l(L"ùø ¡X¢s ¡X¢s ¡X¢s ¡X¢s ¡X¢s ¡X¢s ¡X¢s ¡Xùø");
	wstring m(L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø");
	wstring n(L"ùø ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡X¢q ¡Xùø");
	wstring o(L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø");
	wstring p(L"ùø ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡X¢r ¡Xùø");
	wstring q(L"ùø   ¢x   ¢x   ¢x¡@ ¢x   ¢x   ¢x   ¢x   ùø");
	wstring r(L"¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®ùù ¨®");
	wstring s(L"¤@¡@¤G¡@¤T¡@¥|¡@¤­¡@¤»¡@¤C¡@¤K");
	wcout << a << endl;
	wcout << b << endl;
	wcout << c << endl;
	wcout << d << endl;
	wcout << e << endl;
	wcout << f << endl;
	wcout << g << endl;
	wcout << h << endl;
	wcout << i << endl;
	wcout << j << endl;
	wcout << k << endl;
	wcout << l << endl;
	wcout << m << endl;
	wcout << n << endl;
	wcout << o << endl;
	wcout << p << endl;
	wcout << q << endl;
	wcout << r << endl;
	wcout << s << endl;
	
	//system("CLS");
	ChineseChess newGame;
	newGame.gameStart();
	
		

	

	return 0;
}