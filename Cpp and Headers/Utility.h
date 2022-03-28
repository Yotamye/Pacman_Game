#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <time.h>
#include <filesystem>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// keys

const char UP1 = 'w'; // Up Arrow 
const char UP2 = 'W'; // Up Arrow 
const char DOWN1 = 'x'; // Down Arrow 
const char DOWN2 = 'X'; // Down Arrow 
const char LEFT1 = 'a';  // Left Arrow 
const char LEFT2 = 'A';  // Left Arrow 
const char RIGHT1 = 'd';// Right Arrow 
const char RIGHT2 = 'D';// Right Arrow 
const char STAY1 = 's';// Stay Arrow 
const char STAY2 = 'S';// Stay Arrow 
const char ESC = 27;  // Escape Key

//settings


const int  COLS = 80;
const int  ROWS = 24;
const char  WALL = '#';
const char  BLANK = ' ';
const char  BREADCRUMB = '*';
const char SIGN = '@';
const char GSIGN = '$';
const char LEGEND = '&';
const char EMPTY = '%';
const int LIVES = 3;
const int firstROW = 0;
const int firstCOL = 0;
const int DUMBSTEPS = 5;
const int maxGHOST = 4;
const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;
const int maxFRUITlife = 120;
const int FRUITSTEP = 8;
const int RANDOMCOUNT = 20;
const int SCREENSIZE = 6;
const int SIMPLE = 0;
const int SAVE = 1;
const int LOAD = 2;
const int SILENCE = 3;



//color
enum class Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
