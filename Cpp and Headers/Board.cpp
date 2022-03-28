#include "Board.h"

void Board::printBoard(char menuChoice)const {
	char ch;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (menuChoice == '2') {
				ch = board[i][j];
				switch (ch) {
				case(WALL):
					setTextColor(Color::BLUE);
					break;
				case(SIGN):
					setTextColor(Color::YELLOW);
					break;
				case(GSIGN):
					setTextColor(Color::RED);
					break;
				case(BREADCRUMB):
					setTextColor(Color::LIGHTGREY);
					break;
				case(BLANK):
					setTextColor(Color::BLACK);
					break;
				}
			}
			cout << board[i][j];
		}
		cout << endl;
		setTextColor(Color::WHITE);

	}
}
char Board::getPointofBoard(int row, int col) const{
	return board[row][col];
}
void Board::setPointToBoard(int x, int y, char ch) {

	board[x][y] = ch;
}
void Board::printPointinBoard(int x, int y, char menuChoice) {
	char ch = getPointofBoard(x, y);
	if (menuChoice == '2') {
		switch (ch) {
		case(WALL):
			setTextColor(Color::BLUE);
			break;
		case(SIGN):
			setTextColor(Color::YELLOW);
			break;
		case(GSIGN):
			setTextColor(Color::RED);
			break;
		case(BREADCRUMB):
			setTextColor(Color::LIGHTGREY);
			break;
		case(BLANK):
		case(LEGEND):
			setTextColor(Color::BLACK);
			break;

		}
	}
	if (ch == LEGEND)
		ch = BLANK;
	else
	cout << ch;
	setTextColor(Color::WHITE);

}
