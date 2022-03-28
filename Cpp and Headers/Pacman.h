#pragma once
#include "Utility.h"
#include "Point.h"
#include "Board.h"
#include "Entity.h"
class Board;
class Ghost;

class Pacman : public Entity{

private:

	int lives = LIVES;
	int crumbsCounter = 0;
	Point firstLoc;

public:
	Pacman(char sign, int x, int y,char dir) : Entity(sign, x, y, dir), firstLoc(x, y){}
	Pacman() {}
	void lowerLive() {lives = lives - 1;}
	int getLives()const {return lives;}
	int getCrumbsCounter()const {return crumbsCounter;}
	void setCrumbs() {crumbsCounter++;}
	void setCrumbsCounter(int num) { crumbsCounter = num; }
	Point getFirstLoc()const { return firstLoc; }
	void setFirstLoc(int x, int y) { firstLoc.setPointX(x); firstLoc.setPointY(y); }

};