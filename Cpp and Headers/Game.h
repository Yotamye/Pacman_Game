#pragma once
#include "Utility.h"
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

class Game {
public:
	//Genral
	int startGame(int mode);
	int getKey();
	void print_Menu();
	void Menu(Board& b, char& menuChoice, Point& legendStart, Ghost* ghostArr, Pacman& p,
		int& ghostCount, int& level, vector<string>& fileArr, int& fileIndex, int& breadCount, int& lastLine, int& lenSize,const int mode, fstream& stepsFile, fstream& resultFile);
	void printInstructions();
	string getFileName(string& fileName,const string& stringToAppend);
	void printWinnigMessage();
	void printLosingMessage();
	void printWinnigMessage2();
	void printErrorFile();
	void printAskLevel();
	bool isValidkey(char key);
	void keyValidation(Board& b, char& key, char& saver, char menuChoice);
	void pauseGame(Board& b, char menuChoice);
	void clrscr();
	void gotoxy(int x, int y);

	//Board

	void updateBoard(int x, int y, char ch, Board& b, char menuChoice);
	void resetPacmanAndGhosts(Pacman& p, Ghost* ghostArr, const int ghostCount, Board& b, char menuChoice, const int mode, fstream& resultFile, int timeCounter, bool& isTestValid);
	void setTextColor(Color colorToSet) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet); };

	//Pacman
	void pacmanMovement(Pacman& p, Ghost* ghostArr, Fruit& f, Board& b, Point& legend, char& key,
		char menuChoice, int& ghostCount, int colEdge, int rowEdge, int& score, const int mode, fstream& stepsFile, fstream& resultFile, int timeCounter, bool& isTestValid);

	//Ghost
	void moveGhost(Board& b, Ghost& g, Fruit& f, char menuChoice, const int mode, fstream& stepsFile);
	void ghostMovement(Ghost* ghostArr, int ghostCount, Pacman& p, Board& b, Fruit& f, Point& legend,
		char menuChoice, int& level, int colEdge, int rowEdge, int& counter, int& nowDumb, const int mode, fstream& stepsFile, fstream& resultFile, int timeCounter, bool& isTestValid);

	// Fruit

	void putFruitsinBoard(Fruit& f, Board& b, char menuChoice, int lastRow, int lastCol, Point& legend, const int mode, fstream& stepsFile);
	void fruitMovement(Fruit& f, Board& b, Pacman& p, int ghostCount, Ghost* ghostArr, Point& legend, char menuChoice, int lastRow, int lastCol, int& score, const int mode, fstream& stepsFile);
	void moveFruit(Board& b, Fruit& g, Point& nP, char menuChoice, const int mode, fstream& stepsFile);
	bool isPointInLegend(int x, int y, Point& legend);

	//File

	void initFileToBoard(Board& b, char menuChoice, Point& legendStart, Ghost* ghostArr, Pacman& p, int& ghostCount, string& fileName, int& breadCount, int& lastLine, int& lenSize, const int mode, fstream& stepsFile, fstream& resultFile);
	int getLineLen(char* line);
	void getFilesArr(vector<string>& fileArr, const string& fileName);
	void getStepsFileArr(vector<string>& fileArr);
	void setFileIndexTofileName(vector<string>& fileArr, int& fileIndex, string& fileName);
	int minDist(Board& b, const Point& pacPoint, Ghost& g, int colEdge, int rowEdge);
	char loadDirFromStepsFile(fstream& stepsFile, Fruit& f);
	void checkTestResult(fstream& resultFile, int timeCounter, bool& isTestValid);
	void printTestFailed();

};