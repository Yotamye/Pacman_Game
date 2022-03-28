#pragma once
#include "Point.h"
#include "Board.h"
class Entity 
{
protected:
	char sign;
	Point point;
	char direction;
public:
	Entity() {}
	Entity(char _sign, int _x, int _y, char dir) : point(_x, _y), sign(_sign), direction(dir) {}
	char getSign()const {return sign;}
	void setSign(char _sign) { sign = _sign; }
	const Point& getPoint() const { return point; }
	void setPoint(int _x, int _y) { point.setPoint(_x, _y); }
	char getDirection()const { return direction; }
	void setDirection(char key) { direction = key; }
	void move();
	bool isNextMoveIsValid(const Board& b);
	char calcNextRandomDir(const Board& b, int colEdge, int rowEdge, Point& pointToSendTo);
	bool isEntityTouchTunnel(const Board& b, int colEdge, int rowEdge, Point& pointToSendTo);
	Point getNextMove();

};

