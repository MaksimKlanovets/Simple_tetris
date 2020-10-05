#pragma once

const unsigned char cellSymbolFigure = '*';

// Массив фигурок-тетрамино
const int figures[7][4] =
{
	81,82,83,84, // line
	71,81,82,92, // Z
	91,81,82,72, // S
	91,81,71,82, // T
	81,82,83,93, // L
	81,82,83,73, // J
	81,91,82,92, // O
};

struct Point
{
	
	int x, y;
} a[4]{a[0].x =0}, b[4];