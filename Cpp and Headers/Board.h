#pragma once
#include "Utility.h"
#include <fstream>

class Pacman;
class Ghost;
class Board {
private:
	char board[ROWS][COLS];

public:

	Board() {
		for (int i = 0; i < 24; i++)
			for (int j = 0; j < 80; j++) 
				board[i][j] = BLANK; }
	void printBoard(char menuChoice) const;
	char getPointofBoard(int row, int col)const;
	void setPointToBoard(int x, int y, char ch);
	void setTextColor(Color colorToSet)const {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);};
	void printPointinBoard(int x, int y, char menuChoice);

};