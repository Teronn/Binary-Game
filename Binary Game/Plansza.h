#pragma once
#include "Pole.h"
class Plansza
{
public:
	int gambling = 0;
	int size;
	int msgInfo;
	int msgInfo1X;
	int msgInfo1Y;
	int msgInfo2X;
	int msgInfo2Y;
	int msgInfo3X;
	int msgInfo3Y;
	int tipEnd=0;
	int subtipEnd = 0;
	int countNumbersX1(int, Pole**);
	int countNumbersX0(int, Pole**);
	int countNumbersY1(int, Pole**);
	int countNumbersY0(int, Pole**);
	bool countNumbers = false;
	bool showNeighbours = false;
	Plansza(int);
	void gamble();
	Pole** setTable(int);
	void setMsgInfo(int);
	void setMsgInfo1X(int);
	void setMsgInfo1Y(int);
	void setMsgInfo2X(int);
	void setMsgInfo2Y(int);
	void setMsgInfo3X(int);
	void setMsgInfo3Y(int);
	void setCountNumbers(bool);
	void setShowNeighbours(bool);
	void newTemplateGame(Pole**,int);
	void newRandomGame(Pole**, int);
	void outputMsg();
	void setTipEnd(int);
	void setsubTipEnd(int);
	void clearTable(int,Pole**);
	void startGame(Pole**,int);
	void setSize(int);
	void tip(Pole**, int, int);
	bool gotXNeighbour(Pole **, int, int, int);
	bool gotYNeighbour(Pole **, int, int, int);
	bool isXFull(Pole **, int, int,int);
	bool isYFull(Pole **, int, int,int);
	bool isXSame(Pole **, int, int, int);
	bool isYSame(Pole **, int, int, int);
	void checkLight(Pole **);
	void uncheckLight(Pole **);
	~Plansza();
};

