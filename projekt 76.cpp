// projekt 76.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void HideCursor();
void size(int&, char&);
void gotoxy(int, int);
void draw(int, int, int, char);
void move(int&, int&, int&, char, unsigned char);



int main()
{
	char znak;
	int rozm = 0;
	int x = 0;
	int y = 0;
	unsigned char strzalka;
//------------------------------------------------------------------------------------------
	size(rozm, znak);
	HideCursor();
	draw(x, y, rozm, znak);
	do 
	{
		strzalka = _getch();
		move(x, y, rozm, znak, strzalka);
	} while (strzalka != 27);


	_getch();
}
void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void size(int& rozm, char& znak) // poczatkowa wielkosc figury i znak jakim chcesz rysowac
{

	do
	{
		cout << "Podaj poczatkowy rozmiar figury od 5 do 10: ";
		cin >> rozm;

	} while (rozm <= 4 || rozm > 11 );
	cout << "Podaj znak ASCII, ktorym chcesz rysowac figure: "; 
	cin >> znak;
	system("cls");

}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void draw(int x, int y, int rozm, char znak) // rysowanie figury 
{
	int szerfig = rozm*2;
	int wysfig = rozm;
	gotoxy(x,y);
	for (int i = 0; i < szerfig; i++)
	{
		cout << znak;
	}
	gotoxy(x, y);
	for (int i = 1; i < wysfig; i++)
	{
		if (i < wysfig/2)
		{
			gotoxy(x+i,y+i);
			cout << znak;
		}
		else
		{
			gotoxy(x+(((wysfig/2)-i)*2+i), y+i);
			cout << znak;
		}
	}
	gotoxy(x,  y+wysfig-1);
	for (int i = 0; i < szerfig; i++)
	{
		cout << znak;
	}
}

void move(int &x, int &y, int &rozm, char znak, unsigned char strzalka) // przesuwanie 
{
	_CONSOLE_SCREEN_BUFFER_INFO m;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &m);
	if (strzalka == 224)
		strzalka = _getch();

	if (strzalka == 72) //gora
	{
		y -= 1;
		if (y <= -1) { y = 0; } 
	}
	if (strzalka == 80) //dol
	{
		y += 1;
		if (y < m.dwCursorPosition.Y - rozm) { y = m.dwCursorPosition.Y - rozm; } 
	} 
		
	if (strzalka == 77) //prawo
	{ 
		x += 1;
		if (x >= m.dwMaximumWindowSize.X - (rozm * 2)) { x = m.dwMaximumWindowSize.X - (rozm * 2); } 
	}
		
	if (strzalka == 75) //lewo
	{
		x -= 1;
		if (x <= -1) { x = 0; } 
	} 
		
	if (strzalka == 45) //mniejsze
	{ 
		rozm -= 1; 
		if (x <= -1) { x = 0; }
		if (y <= -1) { y = 0; }
	} 
	if (strzalka == 43) //wieksze
	{
		if (rozm <= (m.dwMaximumWindowSize.X/2)) { rozm += 1; }
		if (x >= m.dwMaximumWindowSize.X - (rozm * 2)) { rozm -= 1; } // do prawej sciany i koniec powiekszania
		if (y < m.dwCursorPosition.Y - rozm) { rozm -= 1; } // do dolnej sciany i koniec
	
	} 

	system("cls");
	gotoxy(0, 0);
	draw(x, y, rozm, znak);
}
