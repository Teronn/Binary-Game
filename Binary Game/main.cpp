// ConsoleApplication1.cpp: Określa punkt wejścia dla aplikacji konsoli.
//
#include <iostream>
#include "Plansza.h"
#include <cstdlib>
#include <ctime>

using namespace std;


int main() {
	srand(time(NULL));
	Pole ** tablica = new Pole *[12];
	for (int i = 0; i < 12; i++)
		tablica[i] = new Pole[12];
	Plansza game(16);
	game.startGame(tablica,12);

	return 0;
}