#pragma once
#include "Entity.h"
#include "Utility.h"
class Fruit : public Entity
{
protected:
	char NextSign;

public:
	char getNextSign()const { return NextSign; }
	void setNextSign(char ch) { NextSign = ch; }
	char RandomNum() {int randNum = (rand() % 5) + '0' + 5; return char(randNum);}
	Fruit() {}
	Fruit(char sign, int x, int y, char dir) : Entity(sign, x, y, dir) {}

};

