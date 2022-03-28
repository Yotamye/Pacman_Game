#pragma once
#include "Utility.h"
#include "Point.h"
#include "Board.h"
#include "Entity.h"

class Board;
class Pacman;

class Ghost : public Entity{

	char NextSign;
	Point firstLoc;
	int dist;

public:
	Ghost() {}
	Ghost(char sign,char ch, int x, int y , char dir, int num) : Entity(sign,x,y,dir), NextSign(ch) ,firstLoc(x,y),dist(num){}
	char getNextSign()const { return NextSign; }
	void setNextSign(char ch) { NextSign = ch; }
	Point getFirstLoc()const { return firstLoc; }
	void setFirstLoc(Point& p) { firstLoc = p; }
	int getDist()const { return dist; }
	void setDist(int dist_) { dist = dist_; }
};