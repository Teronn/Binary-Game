#include <stdio.h>
#include "conio2.h"
#include <iostream>
#include "Plansza.h"
#include "Pole.h"
#include <stdio.h>
#include "conio2.h"
#include <math.h>  
#include <cstdlib>
#include <ctime>

#define LEGENDAX 2  // Pozycja X legendy
#define LEGENDAY 2 // Pozycja Y legendy

#define XGAME 48 // Lewy górny róg planszy (x)
#define YGAME 7 // Lewy górny róg planszy (y)

using namespace std;

Plansza::Plansza(int size)
	:size(size)
{
}

void Plansza::gamble()
{
	char text1[30];
	int zn = 0, k = this->gambling;
	clrscr();
	this->gambling = 0;
	gotoxy(10, 12);
	cputs("Wpisz rozmiar planszy (wielokrotnosc 2)");
	gotoxy(10, 14);
	cputs("Wcisnij r - aby zresetowac");
	gotoxy(10, 16);
	cputs("Wartosc to :");
	
	while (zn != 13)
	{
		zn = getch();
		if (zn >= '0' && zn <= '9')
		{
			this->gambling = this->gambling * 10 + zn - 48;
			putch(zn);
		}
		if (zn == 'r')
		{
			this->gamble();
			break;
		}
	}
	if (this->gambling % 2 == 1 || this->gambling == 0)
		this->gamble();


}

void Plansza::setSize(int newsize) {
	size = newsize;
}

void Plansza::setShowNeighbours(bool newbool)
{
	showNeighbours = newbool;
}

void Plansza::setCountNumbers(bool newbool)
{
	countNumbers = newbool;
}

void Plansza::setMsgInfo(int newcom) {
	msgInfo = newcom;
}

void Plansza::setMsgInfo1X(int newcom) {
	msgInfo1X = newcom;
}

void Plansza::setMsgInfo1Y(int newcom) {
	msgInfo1Y = newcom;
}

void Plansza::setMsgInfo2X(int newcom) {
	msgInfo2X = newcom;
}

void Plansza::setMsgInfo2Y(int newcom) {
	msgInfo2Y = newcom;
}

void Plansza::setMsgInfo3X(int newcom) {
	msgInfo3X = newcom;
}

void Plansza::setMsgInfo3Y(int newcom) {
	msgInfo3Y = newcom;
}

void Plansza::setTipEnd(int newtip) {
	tipEnd = newtip;
}

void Plansza::setsubTipEnd(int newtip) {
	subtipEnd = newtip;
}

Pole** Plansza::setTable(int desiredSize)
{
	Pole ** tablica = new Pole *[desiredSize];
	for (int i = 0; i < desiredSize;i++)
			tablica[i] = new Pole[desiredSize];
	return tablica;
}

void Plansza::clearTable(int desiredSize,Pole ** tablica)
{
	for (int i = 0; i<desiredSize; i++)
		delete[] tablica[i];

	delete[] tablica;
}

bool Plansza::gotXNeighbour(Pole ** tablica, int xc, int yc, int val)
{
	if (xc > 0 && xc < size - 1)
	{
		int x1 = tablica[xc - 1][yc].getValue();
		int x2 = tablica[xc + 1][yc].getValue();
			if (x1 == val && x2 == val)
				return true;

	}
	if (xc > 1)
	{
		int x1 = tablica[xc - 1][yc].getValue();
		int x2 = tablica[xc - 2][yc].getValue();
			if (x1 == val && x2 == val)
				return true;
	}
	if (xc < size -2)
	{
		int x1 = tablica[xc + 1][yc].getValue();
		int x2 = tablica[xc + 2][yc].getValue();
		if (x1 == val && x2 == val)
			return true;
	}
	return false;

}

bool Plansza::gotYNeighbour(Pole ** tablica, int xc, int yc, int val)
{
	if (yc > 0 && yc < size - 1)
	{
		int x1 = tablica[xc][yc-1].getValue();
		int x2 = tablica[xc][yc+1].getValue();
		if (x1 == val && x2 == val)
			return true;

	}
	if (yc > 1)
	{
		int x1 = tablica[xc][yc-1].getValue();
		int x2 = tablica[xc][yc-2].getValue();
		if (x1 == val && x2 == val)
			return true;
	}
	if (yc < size - 2)
	{
		int x1 = tablica[xc][yc+1].getValue();
		int x2 = tablica[xc][yc+2].getValue();
		if (x1 == val && x2 == val)
			return true;
	}
	return false;

}

bool Plansza::isXFull(Pole ** tablica, int xc, int yc, int val)
{
	int k = this->size;
	int sum = 1;
	for (int i = 0; i < k; i++)
		if (tablica[i][yc].getValue() == val)
			sum = sum + 1;
	if (sum > k/2)
		return true;


	return false;
}

bool Plansza::isYFull(Pole ** tablica, int xc, int yc, int val)
{
	int k = this->size;
	int sum = 1;
	for (int i = 0; i < k; i++)
		if (tablica[xc][i].getValue() == val)
			sum = sum + 1;
	if (sum > k/2)
		return true;


	return false;
}

void Plansza::newTemplateGame(Pole ** tablica, int sizemap) {

	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;
	int tmp;
	char kek;

	pFile = fopen("szablonglowny.txt", "rb");
	if (pFile == NULL) { cputs("Blad sciezki"); exit(1); }

	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);


	buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL) { cputs("Blad pamieci"); exit(2); }

	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize) { cputs("Blad czytania"); exit(3); }

	tmp = sqrt(result);

	for (int i = 0; i < tmp; i++)
	{
		for (int j = 0; j < tmp; j++)
		{
			kek = *(buffer + i*tmp + j);
			if (kek == '0')
			{
				tablica[i][j].setDefault(false);
				tablica[i][j].setValue(0);
			}
			if (kek == '1')
			{
				tablica[i][j].setDefault(false);
				tablica[i][j].setValue(1);
			}
			if (kek == '2')
			{
				tablica[i][j].setDefault(false);
				tablica[i][j].setValue(2);
			}
			if (kek == '3')
			{
				tablica[i][j].setDefault(true);
				tablica[i][j].setValue(0);
			}
			if (kek == '4')
			{
				tablica[i][j].setDefault(true);
				tablica[i][j].setValue(1);
			}
		}
	}


	fclose(pFile);
	free(buffer);
}

bool Plansza::isXSame(Pole ** tablica, int xc, int yc, int val)
{
	int k = this->size;
	int sum = 0;
	for (int i = 0; i < k; i++)
	{
		if (yc != i)
		{
			sum = 0;
			for (int j = 0; j < k; j++)
			{

				if (tablica[j][yc].getValue() == tablica[j][i].getValue() && tablica[j][i].getValue() != 2)
					sum++;

				if (sum == k - 1)
					if (tablica[xc][i].getValue() == val)
						return true;
			}
		}
	}

		return false;
}

bool Plansza::isYSame(Pole ** tablica, int xc, int yc, int val)
{
	int k = this->size;
	int sum = 0;
	for (int i = 0; i < k; i++)
	{
		if (xc != i)
		{
			sum = 0;
			for (int j = 0; j < k; j++)
			{

				if (tablica[xc][j].getValue() == tablica[i][j].getValue() && tablica[i][j].getValue() != 2)
					sum++;
				if (yc == j)
					if (val == tablica[i][j].getValue())
						sum++;

				if (sum == size)
					return true;
			}
		}
	}

	return false;
}

void Plansza::newRandomGame(Pole ** tablica, int sizemap) {


	int k = this->size;
	int ran = k*k / 4;
	int randomx;
	int randomy;
	int randomvalue;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			tablica[i][j].setDefault(false);
			tablica[i][j].setValue(2);
		}
	}

	while (ran != 0)
	{
		randomx = rand() % k;
		randomy = rand() % k;
		randomvalue = rand() % 2;
		if (tablica[randomx][randomy].getValue() == 2 && this->gotXNeighbour(tablica, randomx, randomy, randomvalue ) == false && this->gotYNeighbour(tablica, randomx, randomy, randomvalue) == false && this->isXFull(tablica, randomx, randomy, randomvalue) == false && this->isYFull(tablica, randomx, randomy, randomvalue) == false && this->isXSame(tablica, randomx, randomy, randomvalue) == false && this->isYSame(tablica, randomx, randomy, randomvalue) == false)
		{
			tablica[randomx][randomy].setValue(randomvalue);
			tablica[randomx][randomy].setDefault(true);
			ran--;
		}

	}

}

void Plansza::tip(Pole ** tablica, int xc, int yc) {

	if (tablica[xc][yc].default == true)
	{
		this->setMsgInfo(0);

	}

	if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 1) == false && this->gotYNeighbour(tablica, xc, yc, 1) == false && this->isXFull(tablica, xc, yc, 1) == false && this->isYFull(tablica, xc, yc, 1) == false && this->isXSame(tablica, xc, yc, 1) == false && this->isYSame(tablica, xc, yc, 1) == false)
	{
		if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 0) == false && this->gotYNeighbour(tablica, xc, yc, 0) == false && this->isXFull(tablica, xc, yc, 0) == false && this->isYFull(tablica, xc, yc, 0) == false && this->isXSame(tablica, xc, yc, 0) == false && this->isYSame(tablica, xc, yc, 0) == false)
		{
			this->setMsgInfo(1);
		}
		else this->setMsgInfo(2);
	}

	if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 0) == false && this->gotYNeighbour(tablica, xc, yc, 0) == false && this->isXFull(tablica, xc, yc, 0) == false && this->isYFull(tablica, xc, yc, 0) == false && this->isXSame(tablica, xc, yc, 0) == false && this->isYSame(tablica, xc, yc, 0) == false)
	{
		if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 1) == false && this->gotYNeighbour(tablica, xc, yc, 1) == false && this->isXFull(tablica, xc, yc, 1) == false && this->isYFull(tablica, xc, yc, 1) == false && this->isXSame(tablica, xc, yc, 1) == false && this->isYSame(tablica, xc, yc, 1) == false)
		{
			this->setMsgInfo(1);
		}
		else this->setMsgInfo(3);
	}

		if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 0) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 1) == true)
			{
				this->setMsgInfo1X(0);
			}
			else this->setMsgInfo1X(1);
		}
		if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 1) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->gotXNeighbour(tablica, xc, yc, 0) == true)
			{
				this->setMsgInfo1X(0);
			}
			else this->setMsgInfo1X(2);
		}
		if (tablica[(xc)][(yc)].default == false && this->gotYNeighbour(tablica, xc, yc, 0) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->gotYNeighbour(tablica, xc, yc, 1) == true)
			{
				this->setMsgInfo1Y(0);
			}
			else this->setMsgInfo1Y(1);
		}
		if (tablica[(xc)][(yc)].default == false && this->gotYNeighbour(tablica, xc, yc, 1) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->gotYNeighbour(tablica, xc, yc, 0) == true)
			{
				this->setMsgInfo1Y(0);
			}
			else this->setMsgInfo1Y(2);
		}
		if (tablica[(xc)][(yc)].default == false && this->isXFull(tablica, xc, yc, 0) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isXFull(tablica, xc, yc, 1) == true)
			{
				this->setMsgInfo2X(0);
			}
			else this->setMsgInfo2X(1);
		}
		if (tablica[(xc)][(yc)].default == false && this->isXFull(tablica, xc, yc, 1) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isXFull(tablica, xc, yc, 0) == true)
			{
				this->setMsgInfo2X(0);
			}
			else this->setMsgInfo2X(2);
		}
		if (tablica[(xc)][(yc)].default == false && this->isYFull(tablica, xc, yc, 0) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isYFull(tablica, xc, yc, 1) == true)
			{
				this->setMsgInfo2Y(0);
			}
			else this->setMsgInfo2Y(1);
		}
		if (tablica[(xc)][(yc)].default == false && this->isYFull(tablica, xc, yc, 1) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isYFull(tablica, xc, yc, 0) == true)
			{
				this->setMsgInfo2Y(0);
			}
			else this->setMsgInfo2Y(2);
		}

		if (tablica[(xc)][(yc)].default == false && this->isXSame(tablica, xc, yc, 0) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isXSame(tablica, xc, yc, 1) == true)
			{
				this->setMsgInfo3X(0);
			}
			else this->setMsgInfo3X(1);
		}

		if (tablica[(xc)][(yc)].default == false && this->isXSame(tablica, xc, yc, 1) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isXSame(tablica, xc, yc, 0) == true)
			{
				this->setMsgInfo3X(0);
			}
			else this->setMsgInfo3X(2);
		}
		if (tablica[(xc)][(yc)].default == false && this->isYSame(tablica, xc, yc, 0) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isYSame(tablica, xc, yc, 1) == true)
			{
				this->setMsgInfo3Y(0);
			}
			else this->setMsgInfo3Y(1);
		}
	
		if (tablica[(xc)][(yc)].default == false && this->isYSame(tablica, xc, yc, 1) == true)
		{
			if (tablica[(xc)][(yc)].default == false && this->isYSame(tablica, xc, yc, 0) == true)
			{
				this->setMsgInfo3Y(0);
			}
			else this->setMsgInfo3Y(2);
		}

	

}

void Plansza::outputMsg()
{
	if (this->msgInfo == 0)
		cputs("Wartosc domyslna - niemodyfikolwana ");
	if (this->msgInfo == 1)
		cputs("Dostepne : 0,1 ");
	if (this->msgInfo == 2)
		cputs("1 jest dostepne. ");
	if (this->msgInfo == 3)
		cputs("0 jest dostepne. ");
	if (this->msgInfo1X == 0)
		cputs("W wierszu sasiaduje za duzo 1 i 0. ");
	if (this->msgInfo1X == 1)
		cputs("W wierszu sasiaduje za duzo 1. ");
	if (this->msgInfo1X == 2)
		cputs("W wierszu sasiaduje za duzo 0. ");
	if (this->msgInfo1Y == 0)
		cputs("W kolumnie sasiaduje za duzo 1 i 0. ");
	if (this->msgInfo1Y == 1)
		cputs("W kolumnie sasiaduje za duzo 1. ");
	if (this->msgInfo1Y == 2)
		cputs("W kolumnie sasiaduje za duzo 0. ");
	if (this->msgInfo2X == 0)
		cputs("W wierszu jest za duzo 1 i 0. ");
	if (this->msgInfo2X == 1)
		cputs("W wierszu jest za duzo 1. ");
	if (this->msgInfo2X == 2)
		cputs("W wierszu jest za duzo 0. ");
	if (this->msgInfo2Y == 0)
		cputs("W kolumnie jest za duzo 1 i 0. ");
	if (this->msgInfo2Y == 1)
		cputs("W kolumnie jest za duzo 1. ");
	if (this->msgInfo2Y == 2)
		cputs("W kolumnie jest za duzo 0. ");
	if (this->msgInfo3X == 0)
		cputs("Po wpisaniu 1 i 0 wiersze beda sie powtarzac. ");
	if (this->msgInfo3X == 1)
		cputs("Po wpisaniu 1 wiersze beda sie powtarzac. ");
	if (this->msgInfo3X == 2)
		cputs("Po wpisaniu 0 wiersze beda sie powtarzac. ");
	if (this->msgInfo3Y == 0)
		cputs("Po wpisaniu 1 i 0 kolumny beda sie powtarzac. ");
	if (this->msgInfo3Y == 1)
		cputs("Po wpisaniu 1 kolumny beda sie powtarzac. ");
	if (this->msgInfo3Y == 2)
		cputs("Po wpisaniu 0 kolumny beda sie powtarzac. ");

	this->setMsgInfo(4);
	this->setMsgInfo1X(4);
	this->setMsgInfo1Y(4);
	this->setMsgInfo2X(4);
	this->setMsgInfo2Y(4);
	this->setMsgInfo2X(4);
	this->setMsgInfo2Y(4);
	this->setMsgInfo3X(4);
	this->setMsgInfo3Y(4);
}

int  Plansza::countNumbersX0(int y, Pole ** tab)
{
	int k = 0;

	for (int i = 0; i < this->size; i++)
	{
		if (tab[i][y].getValue() == 0)
			k++;
	}

	return k;
}

int  Plansza::countNumbersX1(int y, Pole ** tab)
{
	int k = 0;

	for (int i = 0; i < this->size; i++)
	{
		if (tab[i][y].getValue() == 1)
			k++;
	}

	return k;
}

int  Plansza::countNumbersY0(int x, Pole ** tab)
{
	int k = 0;

	for (int i = 0; i < this->size; i++)
	{
		if (tab[x][i].getValue() == 0)
			k++;
	}

	return k;
}

int  Plansza::countNumbersY1(int x, Pole ** tab)
{
	int k = 0;

	for (int i = 0; i < this->size; i++)
	{
		if (tab[x][i].getValue() == 1)
			k++;
	}

	return k;
}

void Plansza::checkLight(Pole ** tablica)
{
	int k = this->size;
	for (int i=0;i<k;i++)
		for (int j = 0; j < k; j++)
		{
			if (tablica[i][j].value == 2) 
				if(this->gotXNeighbour(tablica, i, j, 1) == true || this->gotYNeighbour(tablica, i, j, 1) == true || this->isXFull(tablica, i, j, 1) == true || this->isYFull(tablica, i,j, 1) == true || this->isXSame(tablica, i, j, 1) == true || this->isYSame(tablica, i,j, 1) == true || this->gotXNeighbour(tablica, i, j, 1) == true || this->gotYNeighbour(tablica, i, j, 1) == true || this->isXFull(tablica, i, j, 1) == true || this->isYFull(tablica, i, j, 1) == true)
					if (this->isXSame(tablica, i, j, 0) == true || this->isYSame(tablica, i, j, 0) == true || this->gotXNeighbour(tablica, i, j, 0) == true || this->gotYNeighbour(tablica, i, j, 0) == true || this->isXFull(tablica, i, j, 0) == true || this->isYFull(tablica, i, j, 0) == true || this->isXSame(tablica, i, j, 0) == true || this->isYSame(tablica, i, j, 0) == true)
					{
						tablica[i][j].setTheLight(true);
						this->setsubTipEnd(1);
					}
		}
}

void Plansza::uncheckLight(Pole ** tablica)
{
	int k = this->size;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			tablica[i][j].setTheLight(false);
}

void Plansza::startGame(Pole ** tablica,int sizemap) {

	this->setSize(sizemap);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			tablica[i][j].setX(i);
			tablica[i][j].setY(j);
		}
	int zn = 0, x = XGAME, y = YGAME, zero = 0;
	gotoxy(35, 2);
	char txt[40];

	settitle("Krystian Prajwowski 165140");

	do {
		textbackground(BLACK);
		clrscr();
		gotoxy(LEGENDAX, LEGENDAY);
		cputs("Krystian Prajwowski 165140 a-j , l");
		gotoxy(LEGENDAX, LEGENDAY + 2);
		cputs("   esc   - wyjscie z gry");
		gotoxy(LEGENDAX, LEGENDAY + 3);
		cputs("strzalki - przemieszczanie sie");
		gotoxy(LEGENDAX, LEGENDAY + 4);
		cputs("    n    - nowa gra");
		gotoxy(LEGENDAX, LEGENDAY + 5);
		cputs("   0 1   - wpisanie 0 lub 1");
		gotoxy(LEGENDAX, LEGENDAY + 6);
		cputs("    o    - losowanie planszy");
		gotoxy(LEGENDAX, LEGENDAY + 7);
		cputs("    p    - prosta podpowiedz");
		gotoxy(LEGENDAX, LEGENDAY + 8);
		cputs("    r    - zmiana rozmiaru planszy");
		gotoxy(LEGENDAX, LEGENDAY + 9);
		cputs("    k    - proste sprawdzanie mozliwosci");
		gotoxy(LEGENDAX, LEGENDAY + 10);
		cputs("           ukonczenia gry");
		gotoxy(LEGENDAX, LEGENDAY + 11);
		cputs("    a    -  tryb autodetekcji konca gry");
		gotoxy(LEGENDAX, LEGENDAY + 12);
		cputs("    d    -  wypisanie liczb 0 i 1");
		gotoxy(LEGENDAX, LEGENDAY + 13);
		cputs("    j    -  zaznaczenie pewnych pol");
		gotoxy(LEGENDAX, LEGENDAY + 14);
		cputs("    d    -  wpisanie pewnych pol");
		gotoxy(LEGENDAX, LEGENDAY + 15);
		if (tipEnd == 1)
		{

			this->checkLight(tablica);
			for (int i = 0; i < this->size; i++)
				for (int j = 0; j < this->size; j++)
					if (tablica[i][j].lightUp == true)
						this->setsubTipEnd(1);

			if (zn != 'k')
			this->uncheckLight(tablica);

		}
		if (this->subtipEnd == 1)
		{
			cputs("Niemozliwosc ukonczenia gry");
			this->setsubTipEnd(0);
		}
		gotoxy(LEGENDAX, YGAME + this->size + 8);
		this->outputMsg();
		if (countNumbers == true)
		{
			textbackground(14);
			gotoxy(XGAME - 2, YGAME - 2);
			cputs("1"); 
			textbackground(2);
			gotoxy(XGAME - 3, YGAME - 3);
			cputs("0");

			for (int i = 0; i < size; i++)
			{
				textbackground(14);
				gotoxy(XGAME+i, YGAME - 2);
				if (countNumbersY1(i, tablica) < 10)
					putch('0'+ countNumbersY1(i, tablica));
				else putch('A' -10 + countNumbersY1(i, tablica));
			}

			for (int i = 0; i < size; i++)
			{
				textbackground(2);
				gotoxy(XGAME + i, YGAME - 3);
				if (countNumbersY0(i, tablica) < 10)
					putch('0' + countNumbersY0(i, tablica));
				else putch('A' - 10 + countNumbersY0(i, tablica));
			}
			for (int i = 0; i < size; i++)
			{
				textbackground(14);
				gotoxy(XGAME - 2 , YGAME + i);
				if (countNumbersX1(i, tablica) < 10)
					putch('0' + countNumbersX1(i, tablica));
				else putch('A' - 10 + countNumbersX1(i, tablica));
			}
			for (int i = 0; i < size; i++)
			{
				textbackground(2);
				gotoxy(XGAME -3, YGAME + i);
				if (countNumbersX0(i, tablica) < 10)
					putch('0' + countNumbersX0(i, tablica));
				else putch('A' - 10 + countNumbersX0(i, tablica));
			}

			setCountNumbers(false);
		}
		gotoxy(40, 12);
		textcolor(7);


		// Ramka

		textbackground(RED);

		gotoxy(XGAME-1, YGAME-1);
		for (int i = 0; i < size+2; i++)
			cputs(" ");
		for (int i = 0; i < size+1; i++)
		{
			gotoxy(XGAME - 1, YGAME + i);
			cputs(" ");
			gotoxy(XGAME+size, YGAME + i);
			cputs(" ");
		}
		gotoxy(XGAME-1, YGAME+size);
		for (int i = 0; i < size+2; i++)
			cputs(" ");



		// Plansza
		textbackground(LIGHTCYAN);
		for (int i = 0; i < size; i++)
		{

			for (int j = 0; j < size; j++)
			{

				gotoxy(XGAME + i, YGAME + j);
				if (tablica[i][j].value == 1 && tablica[i][j].default == true)
				{
					textbackground(CYAN);
					cputs("1");
					textbackground(LIGHTCYAN);
				}
				if (tablica[i][j].value == 0 && tablica[i][j].default == true)
				{
					textbackground(CYAN);
					cputs("0");
					textbackground(LIGHTCYAN);
				}
				if (tablica[i][j].lightUp == true )
				{
					textbackground(RED);
					cputs(".");
					textbackground(LIGHTCYAN);
				}
				if (tablica[i][j].value == 1 && tablica[i][j].default == false)
					cputs("1");
				if (tablica[i][j].value == 0 && tablica[i][j].default == false)
					cputs("0");
				if (tablica[i][j].value == 2 && tablica[i][j].default == false)
				{
					if (this->showNeighbours == true)
					if (tablica[i][j].default == false && this->gotXNeighbour(tablica, i, j, 1) == false && this->gotYNeighbour(tablica, i, j, 1) == false && this->isXFull(tablica, i, j, 1) == false && this->isYFull(tablica, i, j, 1) == false && this->isXSame(tablica, i, j, 1) == false && this->isYSame(tablica, i, j, 1) == false)
					{
						if (tablica[(i)][(j)].default == false && this->gotXNeighbour(tablica, i, j, 0) == false && this->gotYNeighbour(tablica, i, j, 0) == false && this->isXFull(tablica, i, j, 0) == false && this->isYFull(tablica, i, j, 0) == false && this->isXSame(tablica, i, j, 0) == false && this->isYSame(tablica, i, j, 0) == false)
						{

						}
						else textbackground(BROWN);
					}
					if (this->showNeighbours == true)
					if (tablica[i][j].default == false && this->gotXNeighbour(tablica, i, j, 0) == false && this->gotYNeighbour(tablica, i, j, 0) == false && this->isXFull(tablica, i, j, 0) == false && this->isYFull(tablica, i, j, 0) == false && this->isXSame(tablica, i, j, 0) == false && this->isYSame(tablica, i, j, 0) == false)
					{
						if (tablica[(i)][(j)].default == false && this->gotXNeighbour(tablica, i, j, 1) == false && this->gotYNeighbour(tablica, i, j, 1) == false && this->isXFull(tablica, i, j, 1) == false && this->isYFull(tablica, i, j, 1) == false && this->isXSame(tablica, i, j, 1) == false && this->isYSame(tablica, i, j, 1) == false)
						{

						}
						else textbackground(BROWN);
					}
					cputs(".");
					textbackground(LIGHTCYAN);
				}
			}
		}
		textbackground(BLACK);




		textcolor(7);
		sprintf(txt, "X: %01d Y: %01d  Rozmiar: %01d x %01d Tryb a: %01d ", x - XGAME +1, y-YGAME+1,size, size, this->tipEnd);
		gotoxy(40, 2);
		cputs(txt);

		gotoxy(x, y);
		textcolor(7);
		textbackground(BLACK);
		putch('*');
		zero = 0;
		zn = getch();
		this->uncheckLight(tablica);
		// Poruszanie siê tylko po planszy
		if (zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == 0x48 && y >= YGAME+1 && y <= YGAME+size-1) y--;
			else if (zn == 0x50 && y >= YGAME && y <= YGAME+size-2) y++;
			else if (zn == 0x4b && x >= XGAME+1 && x <= XGAME+size-1) x--;
			else if (zn == 0x4d && x >= XGAME && x <= XGAME+size-2) x++;
		
		}
		// Wpisanie 1
		else if (zn == '1') {
			if (x >= XGAME && x <= XGAME + size - 1 && y >= YGAME && y <= YGAME + size - 1)
			{
				if (tablica[(x - XGAME)][(y - YGAME)].default == 0 && this->gotXNeighbour(tablica, x - XGAME, y - YGAME, 1) == false && this->gotYNeighbour(tablica, x - XGAME, y - YGAME, 1) == false && this->isXFull(tablica, x - XGAME, y - YGAME, 1) == false && this->isYFull(tablica, x - XGAME, y - YGAME, 1) == false && this->isXSame(tablica, x - XGAME, y - YGAME, 1) == false && this->isYSame(tablica, x - XGAME, y - YGAME, 1) == false)
					tablica[(x - XGAME)][(y - YGAME)].setValue(1);
			}
		
		}
		// Wpisanie 0
		else if (zn == '0') {
			if (x >= XGAME && x <= XGAME + size - 1 && y >= YGAME && y <= YGAME + size - 1)
			{
				if (tablica[(x - XGAME)][(y - YGAME)].default == 0 && this->gotXNeighbour(tablica, x - XGAME, y - YGAME, 0) == false && this->gotYNeighbour(tablica, x - XGAME, y - YGAME, 0) == false && this->isXFull(tablica, x - XGAME, y - YGAME, 0) == false && this->isYFull(tablica, x - XGAME, y - YGAME, 0) == false && this->isXSame(tablica, x - XGAME, y - YGAME, 0) == false && this->isYSame(tablica, x - XGAME, y - YGAME, 0) == false)
					tablica[(x - XGAME)][(y - YGAME)].setValue(0);
			}
			
		}
		else if (zn == 'n') {
			this->clearTable(size, tablica);
			this->setSize(12);
			this->setTable(size);
			tablica = this->setTable(size);
			this->newTemplateGame(tablica, size);
			x = XGAME;
			y = YGAME;
			
			
		}
		else if (zn == 'o') {
			this->clearTable(size, tablica);
			this->setTable(size);
			tablica = this->setTable(size);
			this->newRandomGame(tablica, size);
			x = XGAME;
			y = YGAME;
			

		}
		else if (zn == 'p') {
			this->tip(tablica, x-XGAME,y-YGAME);
		

		}
		else if (zn == 'r') {
			this->gamble();
			this->clearTable(size, tablica);
			this->setSize(this->gambling);
			tablica = this->setTable(size);
			this->newRandomGame(tablica, size);
			x = XGAME;
			y = YGAME;
			

			

		}
		else if (zn == 'k') {
			this->checkLight(tablica);

		}
		else if (zn == 'a') {
			if (this->tipEnd == 0)
				this->setTipEnd(1);
			else if (this->tipEnd == 1)
				this->setTipEnd(0);

		}
		else if (zn == 'd') {
			this->setCountNumbers(true);

		}
		else if (zn == 'j') {
			if (this->showNeighbours==false)
			this->setShowNeighbours(true);
			else this->setShowNeighbours(false);

		}
		else if (zn == 'w') {
			if (this->showNeighbours == true)
			{
				for (int i = 0; i < size; i++)
				{

					for (int j = 0; j < size; j++)
					{
						if (tablica[i][j].default == false && this->gotXNeighbour(tablica, i, j, 1) == false && this->gotYNeighbour(tablica, i, j, 1) == false && this->isXFull(tablica, i, j, 1) == false && this->isYFull(tablica, i, j, 1) == false && this->isXSame(tablica, i, j, 1) == false && this->isYSame(tablica, i, j, 1) == false)
						{
							if (tablica[(i)][(j)].default == false && this->gotXNeighbour(tablica, i, j, 0) == false && this->gotYNeighbour(tablica, i, j, 0) == false && this->isXFull(tablica, i, j, 0) == false && this->isYFull(tablica, i, j, 0) == false && this->isXSame(tablica, i, j, 0) == false && this->isYSame(tablica, i, j, 0) == false)
							{

							}
							else tablica[i][j].setValue(1);
						}
						if (tablica[i][j].default == false && this->gotXNeighbour(tablica, i, j, 0) == false && this->gotYNeighbour(tablica, i, j, 0) == false && this->isXFull(tablica, i, j, 0) == false && this->isYFull(tablica, i, j, 0) == false && this->isXSame(tablica, i, j, 0) == false && this->isYSame(tablica, i, j, 0) == false)
						{
							if (tablica[(i)][(j)].default == false && this->gotXNeighbour(tablica, i, j, 1) == false && this->gotYNeighbour(tablica, i, j, 1) == false && this->isXFull(tablica, i, j, 1) == false && this->isYFull(tablica, i, j, 1) == false && this->isXSame(tablica, i, j, 1) == false && this->isYSame(tablica, i, j, 1) == false)
							{

							}
							else tablica[i][j].setValue(0);
						}

					}
				}

			}

		}
	} while (zn != 27);

	this->clearTable(size, tablica);


}


Plansza::~Plansza()
{
	
	
}
