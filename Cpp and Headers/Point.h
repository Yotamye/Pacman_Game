#pragma once
class Point
{
protected:

	int x;
	int y;

public:

	Point(int _x, int _y) : x(_x),y(_y) {}
	Point(){};
	void setPointX(int _x) { x=_x;}
	void setPointY(int _y) { y= _y;}
	void setPoint(int _x, int _y) { setPointX(_x); setPointY(_y); }
	int getPointX() const {return x;}
	int getPointY() const {return y;}

	bool operator==(const Point& p) const {
		if (p.getPointX() == x && p.getPointY() == y)
			return true;
		return false;
	}
	void operator=(const Point& p) {setPoint(p.getPointX(), p.getPointY());}

};
