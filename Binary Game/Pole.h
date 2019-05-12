#pragma once
class Pole
{
public:
	Pole();
	int value;
	int x;
	int y;
	bool lightUp = 0;
	bool default;
	int getValue();
	int getX();
	int getY();
	void setX(int);
	void setTheLight(bool);
	void setY(int);
	void setDefault(bool);
	void setValue(int);
	~Pole();
};

