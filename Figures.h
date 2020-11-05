#pragma once
#include "level.h"
const unsigned char cellSymbolFigure = '*';

// Массив фигурок-тетрамино
const int figures[7][4] =
{
	3,5,7,9, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Point
{
	
	int x, y;
} structA[4], structB[4];