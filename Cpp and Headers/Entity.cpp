#include "Entity.h"

void Entity::move() {

	int row = getPoint().getPointX();
	int col = getPoint().getPointY();

	switch (direction)
	{
	case RIGHT1:
	case RIGHT2:
		setPoint(row, col + 1);
		break;

	case LEFT1:
	case LEFT2:
		setPoint(row, col - 1);
		break;

	case DOWN1:
	case DOWN2:
		setPoint(row + 1, col);
		break;

	case UP1:
	case UP2:
		setPoint(row - 1, col);
		break;

	case STAY2:
	case STAY1:
		setPoint(row, col);
		break;

	}

}
char Entity::calcNextRandomDir(const Board& b, int colEdge, int rowEdge, Point& pointToSendTo) {

	int gRow = getPoint().getPointX();
	int gCol = getPoint().getPointY();
	char optionalDir[4] = { UP1, DOWN1, RIGHT1, LEFT1 };
	int randNum;
	bool valid = false;

	do
	{
		randNum = rand() % 4;
		direction = optionalDir[randNum];
		valid = (isNextMoveIsValid(b) && !isEntityTouchTunnel(b,colEdge,rowEdge,pointToSendTo));

	} while (!valid);

	return optionalDir[randNum];
}
Point Entity::getNextMove()
{
	Point nP;
	int row = getPoint().getPointX();
	int col = getPoint().getPointY();
	switch (direction)
	{
	case RIGHT2:
	case RIGHT1:
		nP.setPoint(row, col + 1);
		break;

	case LEFT2:
	case LEFT1:
		nP.setPoint(row, col - 1);
		break;

	case DOWN2:
	case DOWN1:
		nP.setPoint(row + 1, col);
		break;

	case UP2:
	case UP1:
		nP.setPoint(row - 1, col);
		break;

	case STAY2:
	case STAY1:
		nP.setPoint(row , col);
		break;
	}
	return nP;
}
bool Entity::isNextMoveIsValid(const Board& b) {
	Point pNext;
	pNext = getNextMove();
	int nRow = pNext.getPointX();
	int nCol = pNext.getPointY();
	if (b.getPointofBoard(nRow, nCol) == WALL)
		return false;
	return true;
}
bool Entity::isEntityTouchTunnel(const Board& b, int colEdge, int rowEdge, Point& pointToSendTo) {

	int row = getPoint().getPointX();
	int col = getPoint().getPointY();
	char ch = b.getPointofBoard(row, col);

	if (b.getPointofBoard(row, col) != WALL)
	{
		if (row == rowEdge  && (direction == DOWN1 || direction == DOWN2)) {
			if (b.getPointofBoard(firstROW, col) != WALL)
			{
				pointToSendTo.setPoint(firstROW, col);
				return true;
			}
			else if (sign == GSIGN || sign == SIGN){
				setDirection(STAY1);
			}
		}
		else if (row == firstROW  && (direction == UP1 || direction == UP2))
		{
			if (b.getPointofBoard(rowEdge, col) != WALL)
			{
				pointToSendTo.setPoint(rowEdge, col);
				return true;
			}
			else if (sign == GSIGN || sign == SIGN) {
				setDirection(STAY1);
			}
		}
		else if (col == firstCOL && (direction == LEFT1 || direction == LEFT2))
		{
			if (b.getPointofBoard(row, colEdge -1) != WALL)
			{
				pointToSendTo.setPoint(row, colEdge -1);
				return true;
			}
			else if (sign == GSIGN || sign == SIGN) {
				setDirection(STAY1);
			}
		}
		else if (col == colEdge -1 && (direction == RIGHT1 || direction == RIGHT2))
		{
			if (b.getPointofBoard(row, firstCOL) != WALL)
			{
				pointToSendTo.setPoint(row, firstCOL);
				return true;
			}
			else if (sign == GSIGN || sign == SIGN) {
				setDirection(STAY1);
			}
		}
	}
	return false;
}
