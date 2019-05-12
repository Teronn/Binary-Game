#include "Pole.h"



Pole::Pole():
	default(0),value(2)
{
}

int Pole::getValue() {
	return value;
}
int Pole::getX() {
	return x;
}

int Pole::getY() {
	return y;
}

void Pole::setTheLight(bool newbool)
{
	lightUp = newbool;
}

void Pole::setValue(int newval)
{
	value = newval;
}

void Pole::setDefault(bool newdef)
{
	default = newdef;
}

void Pole::setX(int newx)
{
	x = newx;
}

void Pole::setY(int newy)
{
	y = newy;
}

Pole::~Pole()
{
}
