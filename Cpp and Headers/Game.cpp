#include "Game.h"

int Game::startGame(int mode)
{
	bool ghostsMovementTurns = false,isTestValid = true;
	int  fileIndex = 0, flag = 0, lastLine = 0, lenSize = 0, timeCounter = 0;
	char menuChoice = '2';
	Point legendPoint;

	vector<string> fileArr;
	fstream stepsFile;
	fstream resultFile;
	vector<string> stepsFileArr;
	vector<string> resultFileArr;

	getFilesArr(fileArr,".screen"); //inserts file names to the vector fileArr
	if (mode == LOAD || mode == SILENCE) 
	{
		getFilesArr(stepsFileArr,".steps"); // inserts steps file names to the vector stespsFileArr at load mode
		getFilesArr(resultFileArr, ".result"); // inserts steps file names to the vector stespsFileArr at load mode
	}
	srand(time(nullptr));
	if (!fileArr.size())
	{
		printErrorFile();
		return 0;
	}
	do
	{
		bool win = false, kickAss = true;
		char key = RIGHT1, saver = RIGHT1;
		int ghostCount = 0, level = 0, breadAmount = 0, fruitTurn = 0, fruitLifeSpawn = 0, ghostStepsCount = 0, nowDumb = 0, score = 0;
		Pacman p;
		Fruit f;
		Board b;
		Ghost ghostArr[maxGHOST];
		f.setDirection(RIGHT1);
		while (fileIndex < fileArr.size()) {
			win = false;
			if (!flag && mode != LOAD && mode != SILENCE) {
				Menu(b, menuChoice, legendPoint, ghostArr, p, ghostCount, level, fileArr, fileIndex, breadAmount, lastLine, lenSize, mode, stepsFile,resultFile);
				flag++;
			}
			else {
				initFileToBoard(b, menuChoice, legendPoint, ghostArr, p, ghostCount, fileArr[fileIndex], breadAmount, lastLine, lenSize, mode, stepsFile, resultFile);
			}
			if (mode == LOAD || mode == SILENCE) {
				stepsFile.open(stepsFileArr[fileIndex], ios_base::in);
				resultFile.open(resultFileArr[fileIndex], ios_base::in);

			}
			fileIndex++;
			if (menuChoice == '9')
				return 0;
			putFruitsinBoard(f, b, menuChoice, lastLine, lenSize, legendPoint, mode, stepsFile);
			if (mode == SAVE || mode == SIMPLE)
				while (!_kbhit()); // wait untill a key is pressed

			while (p.getLives() > 0 && !win)
			{
				if (mode != SILENCE) {
					Sleep(100);
					if (mode == SAVE || mode == SIMPLE)
						keyValidation(b, key, saver, menuChoice);
				}
				else
					Sleep(0);
				//Pacman move
				pacmanMovement(p, ghostArr, f, b, legendPoint, key, menuChoice, ghostCount, lenSize, lastLine, score, mode, stepsFile, resultFile,timeCounter, isTestValid);
				if ((mode == LOAD || mode == SILENCE) && !isTestValid)
					return 0;
				//Ghost move
				if (ghostsMovementTurns) 
				{
					ghostMovement(ghostArr, ghostCount, p, b, f, legendPoint, menuChoice, level, lenSize, lastLine, ghostStepsCount, nowDumb, mode, stepsFile, resultFile, timeCounter, isTestValid);
					ghostsMovementTurns = false;
					ghostStepsCount++;
					if (nowDumb && ghostStepsCount == DUMBSTEPS) {
						level = MEDIUM;
						nowDumb = 0;
						ghostStepsCount = 0;
					}
				}
				else
					ghostsMovementTurns = true;
				if ((mode == LOAD || mode == SILENCE) && !isTestValid)
					return 0;
				//Fruit move

				if (fruitTurn == FRUITSTEP) {
					fruitMovement(f, b, p, ghostCount, ghostArr, legendPoint, menuChoice, lastLine, lenSize, score, mode, stepsFile);
					fruitTurn = 0;
				}
				if (fruitLifeSpawn == maxFRUITlife)
				{
					updateBoard(f.getPoint().getPointX(), f.getPoint().getPointY(), f.getNextSign(), b, menuChoice); // delete fruit from screen
					if (mode == SAVE) // fruit disappearence
					{
						stepsFile << "F disappeared at (" << f.getPoint().getPointX() << "," << f.getPoint().getPointY() << ")" << endl;
					}
					putFruitsinBoard(f, b, menuChoice, lastLine, lenSize, legendPoint, mode, stepsFile);
					fruitLifeSpawn = 0;
				}
				fruitTurn++;
				fruitLifeSpawn++;
				timeCounter++;

				//Print score

				gotoxy(legendPoint.getPointX(), legendPoint.getPointY() + 5);
				cout << "Lives : " << p.getLives();
				gotoxy(legendPoint.getPointX() + 1, legendPoint.getPointY() + 1);
				cout << "Pacman score : " << score;

				if (p.getCrumbsCounter() == breadAmount-1)
					win = true;
			}
			
			if (win) {
				if (mode == SAVE || mode == SIMPLE)
					printWinnigMessage();
				if (mode == SAVE) 
					resultFile << "Sweet Pacman Won screen#" << fileIndex << " at time: " << timeCounter -1 << endl;	
			}

			else {
				if (mode == SAVE)
					resultFile << "Game Over at screen#" << fileIndex << " at time: " << timeCounter -1 << endl;
				if (mode == SAVE || mode == SIMPLE)
				{
					printLosingMessage();
					kickAss = false;
					ghostCount = level = breadAmount = fruitTurn = fruitLifeSpawn = ghostStepsCount = nowDumb = score = fileIndex = 0;
					break;
				}
				break;
			}
			if (mode == LOAD || mode == SILENCE )
			{
				timeCounter--;
				checkTestResult(resultFile, timeCounter, isTestValid);
				if (!isTestValid)
					printTestFailed();
			}

			if(mode != SIMPLE)
				if (fileIndex < fileArr.size())
					resultFile.close();

			timeCounter = 0;
			breadAmount = 0;
			p.setCrumbsCounter(0);

			stepsFile.close();
		}
		if(!win)
			resultFile.close();

		if (kickAss && (mode == SAVE || mode == SIMPLE))
		{
			printWinnigMessage2();
			flag--;
			ghostCount = level = breadAmount = fruitTurn = fruitLifeSpawn = ghostStepsCount = nowDumb = score = fileIndex = timeCounter = 0;
		}
		if (isTestValid && (mode == LOAD || mode == SILENCE))
		{
			system("cls");
			gotoxy(0, 0);
			cout << "test succeeded!";
			return 0;
		}
		flag = 0;
	} while (menuChoice != '9');
	return 0;
}

//Menu functions

void Game::Menu(Board& b, char& menuChoice, Point& legendStart, Ghost* ghostArr, Pacman& p, int& ghostCount, int& level,
	vector<string>& fileArr, int& fileIndex, int& breadCount, int& lastLine, int& lenSize,const int mode, fstream& stepsFile , fstream& resultFile) {
	string fileName;
	bool valid = false;
	do {
		gotoxy(0, 0);
		print_Menu();
		menuChoice = _getch();
		if (menuChoice != '9') {
			system("cls");
			gotoxy(0, 0);
			printAskLevel();
			level = _getch() - '0';
		}
		switch (menuChoice)
		{
		case('1'): //without color from file
		case('2'): //with color from file
			system("cls");
			gotoxy(0, 0);
			initFileToBoard(b, menuChoice, legendStart, ghostArr, p, ghostCount, fileArr[fileIndex], breadCount, lastLine, lenSize, mode, stepsFile, resultFile);
			valid = true;
			break;
		case('3'): //with color from file by searching file name
			system("cls");
			gotoxy(0, 0);
			cout << "Please insert the name of the File: \n\n";
			cin >> fileName;
			initFileToBoard(b, menuChoice, legendStart, ghostArr, p, ghostCount, fileName, breadCount, lastLine, lenSize, mode, stepsFile, resultFile);
			setFileIndexTofileName(fileArr, fileIndex, fileName);
			valid = true;
			break;

		case('8'):
			system("cls");
			gotoxy(0, 0);
			printInstructions();
			system("cls");
			break;

		case('9'):
			cout << "It was a pleasure, Bye!\n\n";
			return;
			break;

		default:
			system("cls");
			gotoxy(18, 15);
			cout << "Invalid Choice!!!" << endl;
		}

	} while (!valid);

}
void Game::print_Menu() {

	cout << "***************************************************" << endl << endl;
	cout << "                  WELCOME TO PACMAN " << endl << endl;
	cout << "                PLEASE CHOOSE OPTION : " << endl << endl;
	cout << "        (1) Start a new game from file :)" << endl << endl;
	cout << "        (2) Start a new game from file with colors :)" << endl << endl;
	cout << "        (3) Start a new game from file by searching file name :)" << endl << endl;
	cout << "        (8) Present instructions and keys" << endl << endl;
	cout << "        (9) EXIT" << endl << endl;
	cout << "***************************************************" << endl << endl;

}
void Game::printAskLevel() {
	cout << "***************************************************" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "          What level would you like to play?" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "      [1] - Beginner  [2] - Hard  [3] - Extreme           " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "***************************************************" << endl << endl;
}
void Game::printInstructions() {
	char trash;
	cout << "***************************************************" << endl << endl;
	cout << "             Instructions and Keys " << endl << endl;
	cout << "Keys:\nW-Up\nD-Right\nA-Left\nX-Down\nS-Stay in place" << endl << endl;
	cout << "Instructions:\nWinning:Pacman eats all the breadcrumbs.\nLosing:The Ghosts ate you 3 times\n" << endl << endl;
	cout << "***************************************************" << endl << endl;
	cout << "             press any key to back to menu          " << endl << endl;
	while (!_kbhit());
	trash = getKey();
}
void Game::printWinnigMessage() {
	char trash;
	system("cls");
	gotoxy(0, 0);
	cout << "***************************************************" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "       Good job, get ready for the next screen!    " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "           press any key to continue           " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "***************************************************" << endl << endl;
	while (!_kbhit());
	trash = getKey();
	system("cls");

}

void Game::printWinnigMessage2() {
	char trash;
	system("cls");
	gotoxy(0, 0);
	cout << "***************************************************" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "       YOU ARE THE CHAMPION!!!  array!! array!!    " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "           press any key to back to menu           " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "***************************************************" << endl << endl;
	while (!_kbhit());
	trash = getKey();
	system("cls");

}
void Game::printLosingMessage() {
	char trash;
	system("cls");
	gotoxy(0, 0);
	cout << "***************************************************" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "             YOU LOSE :( TRY NEXT TIME!" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "             press any key to back to menu           " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "***************************************************" << endl << endl;
	while (!_kbhit());
	trash = getKey();
	system("cls");

}
void Game::printErrorFile()
{
	system("cls");
	gotoxy(0, 0);
	cout << "***************************************************" << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "           There were no screens found.    " << endl << endl;
	cout << "                                                 " << endl << endl;
	cout << "         please enter screen files to the folder          " << endl << endl;
	cout << "                                                   " << endl << endl;
	cout << "***************************************************" << endl << endl;
}

//Keys functions

int Game::getKey() {
	// This function gets keyCodes for special keys such as arrows , escape and others
	// It returns the Key code such as 72 for arrow up, 27 for Escape... 
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}
void Game::pauseGame(Board& b, char menuChoice) {
	int key = 0;
	system("cls");
	gotoxy(12, 15);
	cout << "Game paused, press ESC again to continue";
	while (!_kbhit()); // wait untill a key is pressed
	if (_kbhit()) // if any key was hit
		key = getKey();
	if (key == ESC) {
		system("cls");
		b.printBoard(menuChoice);
	}
}
void Game::keyValidation(Board& b, char& key, char& saver, char menuChoice) {

	if (_kbhit()) {
		key = getKey();  // change direction
		if (key != ESC && isValidkey(key))
			saver = key;
	}
	if (!isValidkey(key))
		key = saver;

	if (key == ESC) {
		pauseGame(b, menuChoice);
		key = saver;
	}
}
bool Game::isValidkey(char key) {

	if (key == STAY1 || key == STAY2 ||
		key == RIGHT1 || key == RIGHT2 ||
		key == LEFT1 || key == LEFT2 ||
		key == UP1 || key == UP2 ||
		key == DOWN1 || key == DOWN2 ||
		key == ESC) {

		return true;
	}
	return false;
}
void Game::clrscr()
{
	system("cls");
}
void Game::gotoxy(int y, int x)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

//Board functions

void Game::updateBoard(int x, int y, char ch, Board& b, char menuChoice) {

	b.setPointToBoard(x, y, ch);

	gotoxy(x, y);
	b.printPointinBoard(x, y, menuChoice);
}
void Game::resetPacmanAndGhosts(Pacman& p, Ghost* ghostArr, const int ghostCount, Board& b, char menuChoice, const int mode, fstream& resultFile , int timeCounter, bool& isTestValid) {
	//pacman
	if (mode == SAVE)
	resultFile << "Our sweet Pacman died at time: " << timeCounter << endl;
	if (mode == LOAD || mode == SILENCE)
	{
		checkTestResult(resultFile, timeCounter, isTestValid);
		if (!isTestValid) {
			printTestFailed();
			return;
		}
	}
	int pX = p.getFirstLoc().getPointX();
	int pY = p.getFirstLoc().getPointY();
	updateBoard(p.getPoint().getPointX(), p.getPoint().getPointY(), BLANK, b, menuChoice);
	p.setPoint(pX, pY);
	p.lowerLive();
	if (p.getLives() == 0)
		return;
	updateBoard(pX, pY, p.getSign(), b, menuChoice);

	// Ghosts

	for (int i = 0; i < ghostCount; i++)
	{
		updateBoard(ghostArr[i].getPoint().getPointX(), ghostArr[i].getPoint().getPointY(), ghostArr[i].getNextSign(), b, menuChoice);
		int gX = ghostArr[i].getFirstLoc().getPointX();
		int gY = ghostArr[i].getFirstLoc().getPointY();
		char signToUpdate = b.getPointofBoard(gX, gY);
		ghostArr[i].setNextSign(signToUpdate);
		ghostArr[i].setPoint(gX, gY);
		updateBoard(gX, gY, GSIGN, b, menuChoice);

	}
}

//Pacman movement

void Game::pacmanMovement(Pacman& p, Ghost* ghostArr, Fruit& f, Board& b, Point& legend, char& key,
	char menuChoice, int& ghostCount, int colEdge, int rowEdge, int& score, const int mode, fstream& stepsFile, fstream& resultFile, int timeCounter, bool& isTestValid) {
	Point pointToSendTo;
	int x = p.getPoint().getPointX(), y = p.getPoint().getPointY();
	if (mode == SAVE || mode == SIMPLE)
	{
		p.setDirection(key);
		if (isValidkey(key) && (p.isNextMoveIsValid(b))) {
			if (key != STAY1 && key != STAY2) {

				if (key != ESC)
					updateBoard(x, y, BLANK, b, menuChoice);
				if (p.isEntityTouchTunnel(b, colEdge, rowEdge, pointToSendTo))
					p.setPoint(pointToSendTo.getPointX(), pointToSendTo.getPointY());
				else
				{
					p.move();
				}

				x = p.getPoint().getPointX();
				y = p.getPoint().getPointY();
				if (b.getPointofBoard(x, y) == BREADCRUMB) {
					score++;
					p.setCrumbs();
				}
				updateBoard(x, y, p.getSign(), b, menuChoice);

			}
		}
		else {
			p.setDirection(STAY1);
		}
		if (mode == SAVE)
			stepsFile << "P" << " --> " << p.getDirection() <<" to: " << p.getPoint().getPointX() << " " << p.getPoint().getPointY() << endl;
	}
	
	else if (mode == LOAD || mode == SILENCE)
	{

		p.setDirection(loadDirFromStepsFile(stepsFile, f));

		if (p.isEntityTouchTunnel(b, colEdge, rowEdge, pointToSendTo))
			p.setPoint(pointToSendTo.getPointX(), pointToSendTo.getPointY());
		else
		{
			p.move();
		}
		if (p.getDirection() != STAY1 && p.getDirection() != STAY2)
			updateBoard(x, y, BLANK, b, menuChoice);

		x = p.getPoint().getPointX();
		y = p.getPoint().getPointY();
		if (b.getPointofBoard(x, y) == BREADCRUMB) {
			score++;
			p.setCrumbs();
		}
		updateBoard(x, y, p.getSign(), b, menuChoice);
	}

	if (p.getPoint() == f.getPoint())
	{
		score += (f.getSign() - '0');
		if(f.getNextSign() == BREADCRUMB)
			p.setCrumbs();
		updateBoard(p.getPoint().getPointX(), p.getPoint().getPointY(), SIGN, b, menuChoice);
		if (mode == SAVE) // fruit disappearence
		{
			stepsFile << "F disappeared at: (" << f.getPoint().getPointX() << "," << f.getPoint().getPointY() << ")" << endl;
		}
		putFruitsinBoard(f, b, menuChoice, rowEdge, colEdge, legend, mode, stepsFile);
	}

	for (int i = 0; i < ghostCount; i++)
	{
		if (p.getPoint() == ghostArr[i].getPoint()) {
			resetPacmanAndGhosts(p, ghostArr, ghostCount, b, menuChoice, mode, resultFile, timeCounter,isTestValid);
			if (mode == LOAD || mode == SILENCE && !isTestValid) 
				return;
			
			if (mode == SAVE || mode == SIMPLE) {
				if (p.getLives() > 0)
					while (!_kbhit());
				if (mode == SAVE) {
					p.setDirection(STAY1);
					//stepsFile << "P" << " --> " << p.getDirection() << endl;
				}
			}
			else {
				p.setDirection(STAY1);
			}
		}
	}

}

//Ghost movement

void Game::ghostMovement(Ghost* ghostArr, int ghostCount, Pacman& p, Board& b, Fruit& f, Point& legend, char menuChoice, int& level,
	int colEdge, int rowEdge, int& counter, int& nowDumb, const int mode, fstream& stepsFile, fstream& resultFile, int timeCounter, bool& isTestValid) {
	Point point;
	char newDir;
	for (int i = 0; i < ghostCount; i++)
	{
		if (mode == SAVE || mode == SIMPLE) {
			if (level == EASY) {

				if (ghostArr[i].isNextMoveIsValid(b) && !ghostArr[i].isEntityTouchTunnel(b, colEdge, rowEdge, point) && counter != 20)
				{
					moveGhost(b, ghostArr[i], f, menuChoice, mode, stepsFile);
					if (mode == SAVE)
					{
						stepsFile << "G #" << i + 1 << " --> " << ghostArr[i].getDirection() << endl;
					}

				}
				else { //ghost get into a wall
					if (counter == RANDOMCOUNT)
						counter = 0;
					newDir = ghostArr[i].calcNextRandomDir(b, colEdge, rowEdge, point);
					ghostArr[i].setDirection(newDir);
					moveGhost(b, ghostArr[i], f, menuChoice, mode, stepsFile);
					if (mode == SAVE)
					{
						stepsFile << "G #" << i + 1 << " --> " << ghostArr[i].getDirection() << endl;
					}


				}
			}
			if (level == HARD || level == MEDIUM)
			{
				if (level == MEDIUM && counter == RANDOMCOUNT) {
					counter = 0;
					newDir = ghostArr[i].calcNextRandomDir(b, colEdge, rowEdge, point);
					ghostArr[i].setDirection(newDir);
					moveGhost(b, ghostArr[i], f, menuChoice, mode, stepsFile);
					level = EASY;
					nowDumb = 1;
					if (mode == SAVE)
					{
						stepsFile << "G #" << i + 1 << " --> " << ghostArr[i].getDirection() << endl;
					}
				}
				else {
					char optionalDir[maxGHOST] = { UP1, DOWN1, RIGHT1, LEFT1 };
					int mindis[maxGHOST] = { ROWS + COLS, ROWS + COLS ,ROWS + COLS ,ROWS + COLS };
					int min, minIndex = 0;
					Point tmp = ghostArr[i].getPoint();
					for (int j = 0; j < maxGHOST; j++)
					{
						ghostArr[i].setDirection(optionalDir[j]);
						if (ghostArr[i].isNextMoveIsValid(b) && !ghostArr[i].isEntityTouchTunnel(b, colEdge, rowEdge, point))
							mindis[j] = minDist(b, p.getPoint(), ghostArr[i], colEdge, rowEdge);
						ghostArr[i].setPoint(tmp.getPointX(), tmp.getPointY());

					}
					min = mindis[0];
					for (int k = 1; k < 4; k++)
					{
						if (mindis[k] < min) {
							min = mindis[k];
							minIndex = k;
						}
					}
					ghostArr[i].setDirection(optionalDir[minIndex]);
					moveGhost(b, ghostArr[i], f, menuChoice, mode, stepsFile);
					if (mode == SAVE)
					{
						stepsFile << "G #" << i + 1 << " --> " << ghostArr[i].getDirection() << endl;
					}
				}
			}
		}
		else // load
		{
			ghostArr[i].setDirection(loadDirFromStepsFile(stepsFile, f));
			moveGhost(b, ghostArr[i], f, menuChoice, mode, stepsFile);

		}
			
		if (p.getPoint() == ghostArr[i].getPoint()) { // if meet pacman
			resetPacmanAndGhosts(p, ghostArr, ghostCount, b, menuChoice, mode, resultFile, timeCounter, isTestValid);
			if (mode == SAVE || mode == SIMPLE) {
				if (p.getLives() > 0)
					while (!_kbhit());
				if (mode == SAVE) {
					p.setDirection(STAY1);
					//stepsFile << "P" << " --> " << p.getDirection() << endl;
				}
			}
			return;
		}
		if (ghostArr[i].getPoint() == f.getPoint()) { // if meet fruit
			updateBoard(f.getPoint().getPointX(), f.getPoint().getPointY(), ghostArr[i].getNextSign(), b, menuChoice);
			if (mode == SAVE) // fruit disappearence
			{
				stepsFile << "F disappeared at: (" << f.getPoint().getPointX() << "," << f.getPoint().getPointY() << ")" << endl;
			}
			putFruitsinBoard(f, b, menuChoice, rowEdge, colEdge, legend, mode, stepsFile);
		}
	}
}
void Game::moveGhost(Board& b, Ghost& g, Fruit& f, char menuChoice, const int mode, fstream& stepsFile)
{
	Point nP = g.getNextMove();

	int row = g.getPoint().getPointX();
	int col = g.getPoint().getPointY();
	int Brow = nP.getPointX();
	int Bcol = nP.getPointY();
	char nextSign = g.getNextSign(); // what sign is infront of thr ghost
	char lastSign = b.getPointofBoard(Brow, Bcol);
	g.move();
	updateBoard(Brow, Bcol, g.getSign(), b, menuChoice);
	//update the prev move so the ghost hover the board
	if (lastSign != WALL && lastSign != g.getSign() && lastSign != SIGN && lastSign != f.getSign()) {
		updateBoard(row, col, g.getNextSign(), b, menuChoice); // erease ghost to blank
		g.setNextSign(lastSign); // update ghost next sign to what was before the movement
	}

	else
		updateBoard(row, col, g.getNextSign(), b, menuChoice);// erease ghost to blank

}
int Game::minDist(Board& b, const Point& pacPoint, Ghost& g, int colEdge, int rowEdge)
{

	bool visited[ROWS][COLS];
	for (int i = 0; i < rowEdge; i++) {
		for (int j = 0; j < colEdge; j++)
		{
			if (b.getPointofBoard(i, j) == WALL)
				visited[i][j] = true;
			else
				visited[i][j] = false;
		}
	}

	// applying BFS on matrix cells starting from source
	queue<Ghost> q;
	Point pq = g.getNextMove();
	int x = pq.getPointX();
	int y = pq.getPointY();
	g.setPoint(x, y);
	q.push(g);
	visited[x][y] = true;
	while (!q.empty()) {
		Ghost front = q.front();
		q.pop();

		x = front.getPoint().getPointX();
		y = front.getPoint().getPointY();

		// Pacman found;
		if (b.getPointofBoard(front.getPoint().getPointX(), front.getPoint().getPointY()) == SIGN)
			return front.getDist();

		// moving up
		if (x - 1 >= 0 && visited[x - 1][y] == false) {
			q.push(Ghost(GSIGN, front.getNextSign(), x - 1, y, UP1, front.getDist() + 1));
			visited[x - 1][y] = true;

		}

		// moving down
		if (x + 1 <= rowEdge && visited[x + 1][y] == false) {
			q.push(Ghost(GSIGN, front.getNextSign(), x + 1, y, DOWN1, front.getDist() + 1));
			visited[x + 1][y] = true;
		}

		// moving left
		if (y - 1 >= 0 && visited[x][y - 1] == false) {
			q.push(Ghost(GSIGN, front.getNextSign(), x, y - 1, LEFT1, front.getDist() + 1));
			visited[x][y - 1] = true;
		}

		// moving right
		if (y + 1 <= colEdge && visited[x][y + 1] == false) {
			q.push(Ghost(GSIGN, front.getNextSign(), x, y + 1, RIGHT1, front.getDist() + 1));
			visited[x][y + 1] = true;
		}

	}
	return -1;
}

// Fruit

void Game::fruitMovement(Fruit& f, Board& b, Pacman& p, int ghostCount, Ghost* ghostArr, Point& legend, char menuChoice, int lastRow, int lastCol, int& score, const int mode, fstream& stepsFile)
{
	Point point;
	char newDir;
	Point nP = f.getNextMove();
	if (mode == SAVE || mode == SIMPLE) {

		if (f.isNextMoveIsValid(b) && !f.isEntityTouchTunnel(b, lastCol, lastRow, point))
		{
			moveFruit(b, f, nP, menuChoice, mode, stepsFile);
		}
		else { //fruit get into a wall
			newDir = f.calcNextRandomDir(b, lastCol, lastRow, point);
			f.setDirection(newDir);
			nP = f.getNextMove();
			moveFruit(b, f, nP, menuChoice, mode, stepsFile);
		}

		if (mode == SAVE)
		{
			stepsFile << "F --> " << f.getDirection() << endl;
		}
	}
	else // load
	{
		f.setDirection(loadDirFromStepsFile(stepsFile, f));
		nP = f.getNextMove();
		moveFruit(b, f, nP, menuChoice, mode, stepsFile);
	}

	if (p.getPoint() == f.getPoint()) // if meet pacman
	{
		score += (f.getSign() - '0');
		updateBoard(p.getPoint().getPointX(), p.getPoint().getPointY(), SIGN, b, menuChoice);// delete fruit

		if (mode == SAVE) // fruit disappearence
		{
			stepsFile << "F disappeared at: (" << f.getPoint().getPointX() << "," << f.getPoint().getPointY() << ")" << endl;
		}

		putFruitsinBoard(f, b, menuChoice, lastRow, lastCol, legend,mode,stepsFile);
	}
	for (int i = 0; i < ghostCount; i++)
	{
		if (ghostArr[i].getPoint() == f.getPoint()) { // if meet ghost
			updateBoard(f.getPoint().getPointX(), f.getPoint().getPointY(), ghostArr[i].getSign(), b, menuChoice);
			if (mode == SAVE) // fruit disappearence
			{
				stepsFile << "F disappeared at: (" << f.getPoint().getPointX() << "," << f.getPoint().getPointY() << ")" << endl;
			}
			putFruitsinBoard(f, b, menuChoice, lastRow, lastCol, legend, mode, stepsFile);

		}
	}
}
void Game::moveFruit(Board& b, Fruit& f, Point& nP, char menuChoice, const int mode, fstream& stepsFile)
{
	int row = f.getPoint().getPointX();
	int col = f.getPoint().getPointY();
	int Brow = nP.getPointX();
	int Bcol = nP.getPointY();
	char nextSign = f.getNextSign(); // what sign is infront of thr fruit
	char lastSign = b.getPointofBoard(Brow, Bcol);
	f.move();
	updateBoard(Brow, Bcol, f.getSign(), b, menuChoice);
	//update the prev move so the fruit hover the board
	if (lastSign != WALL && lastSign != GSIGN && lastSign != SIGN) {
		updateBoard(row, col, f.getNextSign(), b, menuChoice); // erease fruit to blank
		f.setNextSign(lastSign); // update fruit next sign to what was before the movement
	}
	else
		updateBoard(row, col, f.getNextSign(), b, menuChoice);// erease fruit to blank
}
void Game::putFruitsinBoard(Fruit& f, Board& b, char menuChoice, int lastRow, int lastCol, Point& legend, const int mode, fstream& stepsFile) {
	if (mode == SAVE || mode == SIMPLE) {
		char fruitSign = f.RandomNum();
		f.setSign(fruitSign);
		bool valid = false;
		int x, y;
		do
		{
			y = rand() % lastCol;
			x = rand() % lastRow;

			if ((b.getPointofBoard(x, y) == BREADCRUMB || b.getPointofBoard(x, y) == BLANK) && !isPointInLegend(x, y, legend))
			{
				f.setPoint(x, y);
				f.setNextSign(b.getPointofBoard(x, y));
				updateBoard(x, y, f.getSign(), b, menuChoice);
				if (mode == SAVE)
				{
					stepsFile << "F created at: ( " << x << " , " << y << " ) " << ", val is: " << f.getSign() << endl;
				}
				valid = true;
			}

		} while (!valid);
	}
	else //load
	{
		char newDir = loadDirFromStepsFile(stepsFile, f);
		if(newDir == '1')
			f.setDirection(loadDirFromStepsFile(stepsFile, f));
		int row = f.getPoint().getPointX();
		int col = f.getPoint().getPointY();
		f.setNextSign(b.getPointofBoard(row,col));
		updateBoard(f.getPoint().getPointX(), f.getPoint().getPointY(), f.getSign(), b, menuChoice);

	}
}
bool Game::isPointInLegend(int x, int y, Point& legend) {
	int pX = legend.getPointX();
	int pY = legend.getPointY();
	if (x >= pX && x <= pX + 3 && y >= pY && y <= pY + 20)
		return true;
	return false;

}
// Files

void Game::initFileToBoard(Board& b, char menuChoice, Point& legendStart, Ghost* ghostArr, Pacman& p
	, int& ghostCount, string& fileName, int& breadCount, int& lastLine, int& lenSize, const int mode, fstream& stepsFile, fstream& resultFile) {
	system("cls");
	gotoxy(0, 0);
	char line[COLS];
	char ch = BLANK;
	ifstream myFile;
	string stepsName;
	string resultName;
	int curLegendindexX;
	int curLegendindexY;
	int legendCount = 0,pacmanCounter=0,ghostCounter=0;
	breadCount = 0;
	ghostCount = 0;
	myFile.open(fileName);
	if (!myFile)
	{
		cout << "Error in opening the file";
		return;
	}
	if (mode == SAVE)
	{
		stepsName = getFileName(fileName, "steps");
		stepsFile.open(stepsName, ios_base::out);
		if (!stepsFile.is_open()) {
			cout << "Error in opening the stepsFile";
			return;
		}

		resultName = getFileName(fileName, "result");
		resultFile.open(resultName, ios_base::out);
		if (!resultFile.is_open()) {
			cout << "Error in opening the resultFile";
			return;
		}
	}
	myFile.getline(line, COLS * sizeof(char));
	//lenSize = getLineLen(line);
	lenSize = strlen(line);
	for (int i = 0; !myFile.eof(); i++)
	{
		if (i != 0)
			myFile.getline(line, COLS * sizeof(char));

		for (int j = 0; j < lenSize; j++)
		{
			ch = line[j];
			if (line[j] == LEGEND) {
				curLegendindexX = i;
				curLegendindexY = j;
				legendStart.setPoint(i, j);
				ch = BLANK;
				j += 19;
				legendCount++;
			}
			else if (legendCount > 0 && legendCount < 3 && j == curLegendindexY)
			{
				j += 19;
				legendCount++;
			}
			else if (ch == SIGN) {
				if (pacmanCounter == 1)
				{
					system("cls");
					gotoxy(0, 0);
					cout << "Error in reading sceen - Pacman appear more than one";
					return;
				}
				p.setPoint(i, j);
				p.setSign(SIGN);
				p.setFirstLoc(i, j);
				pacmanCounter++;
			}
			else if (ch == GSIGN) {
				if (ghostCounter == 4)
				{
					system("cls");
					gotoxy(0, 0);
					cout << "Error in reading sceen - Ghost appear more than 4";
					return;
				}
				Ghost g(GSIGN, b.getPointofBoard(i, j), i, j, DOWN1, 0);
				ghostArr[ghostCount] = g;
				ghostCount++;
				ghostCounter++;
			}
			else if (ch == BLANK) {
				ch = BREADCRUMB;
				breadCount++;
			}
			else if (ch == EMPTY)
				ch = BLANK;
			updateBoard(i, j, ch, b, menuChoice);
		}
		lastLine = i;
	}
	if (pacmanCounter == 0)
	{
		system("cls");
		gotoxy(0, 0);
		cout << "Error in reading sceen - Pacman not inserted at all";
		return;
	}
	myFile.close();
}
string Game::getFileName(string& fileName,const string& stringToAppend)
{
	string str = fileName;
	str.resize(fileName.size() - SCREENSIZE);
	str.append(stringToAppend);
	return str;
}
int Game::getLineLen(char* line)
{
	int lenSize = 0;
	for (int i = 0; i < strlen(line); i++)
	{
		if (line[i] == LEGEND) {
			i += 19;
			lenSize += 20;
		}
		else
			lenSize++;
	}
	return lenSize;
}
void Game::getFilesArr(vector<string>& fileArr,const string& fileName) {
	string pathStr;
	for (const auto& entry : filesystem::directory_iterator(filesystem::current_path()))
	{
		pathStr = entry.path().filename().u8string();
		if (pathStr.size() > fileName.size() && pathStr.size() - fileName.size() == pathStr.rfind(fileName))
			fileArr.push_back(pathStr);
	}
	sort(fileArr.begin(), fileArr.end());
}
void Game::getStepsFileArr(vector<string>& fileArr) {
	string pathStr;
	for (const auto& entry : filesystem::directory_iterator(filesystem::current_path()))
	{
		pathStr = entry.path().filename().u8string();
		if (pathStr.size() >  6 && pathStr.size() - 6  == pathStr.rfind(".steps"))
			fileArr.push_back(pathStr);
	}
	sort(fileArr.begin(), fileArr.end());
}
void Game::setFileIndexTofileName(vector<string>& fileArr, int& fileIndex, string& fileName) {
	for (int i = 0; i < fileArr.size(); i++)
	{
		if (fileArr[i] == fileName)
		{
			fileIndex = i;
		}
	}
}

// load

char Game::loadDirFromStepsFile(fstream& stepsFile, Fruit& f) {

	string str, word;
	char dirFromFile;
	getline(stepsFile, str);
	stringstream iss(str);
	iss >> word;
	int x, y;
	if (word.compare("P")==0) {
		iss >> word;
		iss >> word;
	}
	else if (word.compare("F") == 0)
	{	
		iss >> word;
		if (word.compare("created") == 0)
		{
			for (int i = 0; i < 3; i++)
				iss >> word;
			
			x = word[0] - '0';
			if (word[1])
				x = x * 10 + word[1] - '0';
			iss >> word;
			iss >> word;
			y = word[0] - '0';
			if (word[1])
				y = y * 10 + word[1] - '0';
			
			f.setPoint(x, y);

			for (int i = 0; i < 5; i++)
				iss >> word;
			
			f.setSign(word[0]);

			return RIGHT1;
		}
		else if (word.compare("disappeared") == 0)
			return '1';
		else {
			iss >> word;
			iss >> word;
		}
	}
	else if (word.compare("G") == 0) {
		for (int i = 0; i < 4; i++)
			iss >> word;
	}

	dirFromFile = word[0];
	return dirFromFile;
}
void Game::checkTestResult(fstream& resultFile, int timeCounter,bool& isTestValid) {
	string str,word;
	//int num = takeNumFromWord(string & word);
	int num;
	getline(resultFile, str);
	stringstream iss(str);
	for (int i = 0; i < 6; i++)
		iss >> word;
	iss >> num;

	if (timeCounter != num )
	{
		isTestValid = false;
		return;
	}
}

void Game::printTestFailed() {
	system("cls");
	gotoxy(0, 0);
	cout << "test failed!";
	return;
}