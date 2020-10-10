// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

//перегрузить  инкременты mObj1OldY-Y


#include "TestApp.h"
#include "Figures.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

int n ; // задаём тип тетрамино

TestApp::TestApp() : Parent(24 , 24)
{

	mObj1XOld = mObj1X = 10; 
	mObj1YOld = mObj1Y = 1;

	mObj2X = 20;
	mObj2Y = 3;

	mDirection = false;
	mRotate = false;
	srand(static_cast<unsigned int>(time(0)));
}
void TestApp::DownFigure(float sum)
{
	if (sum > 1000 && checkBordersOut(a[0].x + mObj1XOld, a[0].y + mObj1YOld))
	{
		if (mObj1Y > Y_SIZE - 6)
			mObj1Y = Y_SIZE - 6;
		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, '.');

		}
		mObj1YOld = ++mObj1Y;

		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y,  cellSymbolFigure);
		}
		
	}
}
void TestApp::Initializefigure(bool test)
{
	
	if (testFigure == true)
	{
		n = rand() % 7;
		
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] / 2;
			a[i].y = figures[n][i] % 2;

			SetChar(a[i].x + mObj1X, a[i].y+ mObj1Y, cellSymbolFigure);

		}
		testFigure = false;
	}
	
}

bool TestApp::checkBordersOut(int x, int y)
{
	//проверка выхода горизонт
	for (int i = 0; i < 4; i++)
	{
		if (a[i].x+ mObj1X  > (X_SIZE -9) || a[i].y+mObj1Y > (Y_SIZE -6))
		{
			mObj1X= mObj1XOld ;
			mObj1Y = mObj1YOld;
			return false;
			
		}
		if (mObj1X < 1)
		{
			mObj1X = 0;
			false;
		}
	}

	return	true;
	// нижняя граница
	//
	
	
}

void TestApp::KeyPressed(int btnCode)
{
	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y ;
	if (btnCode == 119) //w
		mObj1Y--;
	else if (btnCode == 115) //s
		mObj1Y++;
	else if (btnCode == 97) //a
		mObj1X--;
	else if (btnCode == 100) //d
		mObj1X++;
	else if (btnCode == 32)
	{
		mRotate = true;
		return;
	}
	
	mDirection = true;

	/*if (mObj1X < 1)
		mObj1X = 1;*/
	/*else if (mObj1X >= X_SIZE - 8)
		mObj1X = X_SIZE - 9;

	if (mObj1Y > Y_SIZE - 6)
		mObj1Y = Y_SIZE - 6;*/
	/*
	else if (mObj1X >= X_SIZE)
		mObj1X = X_SIZE - 1;

	if (mObj1Y < 0)
		mObj1Y = 0;
	else if (mObj1Y >=Y_SIZE)
		mObj1Y = Y_SIZE - 1;*/
}

void TestApp::UpdateF(float deltaTime)
{
	
	/*SetChar(mObj1XOld, mObj1YOld, L' ');
	SetChar(mObj1X, mObj1Y, L'O');
	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;*/
	
	////////////////////////////////////////////////
	
	Initializefigure(testFigure);
	// Вращение
	if (mRotate)
	{
		Point p = a[1]; // указываем центр вращения
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y; // y - y0
			int y = a[i].x - p.x; // x - x0
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, '.');
			a[i].x = p.x - x;
			a[i].y = p.y + y;
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, cellSymbolFigure);
		}
		mRotate = false;
		
	}
	// Горизонтальное перемещение
	if (mDirection && checkBordersOut(a[0].x + mObj1XOld, a[0].y + mObj1YOld))
	{
		for (int i = 0; i < 4; i++)
		{

			SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, '.');

		}
		
		for (int i = 0; i < 4; i++)
		{
				SetChar(a[i].x+ mObj1X, a[i].y+ mObj1Y, cellSymbolFigure);
		}
		mDirection = false;
		mObj1XOld = mObj1X;
		mObj1YOld = mObj1Y;
	}

	////////////////////////////////////////////////

	//-----------------------------

	/*SetChar(mObj2X, mObj2Y, L' ');
	if (mDirection)
	{
		mObj2X++;
		if (mObj2X == 40)
			mDirection = false;
	}
	else
	{
		mObj2X--;
		if (mObj2X == 10)
			mDirection = true;
	}
	SetChar(mObj2X, mObj2Y, L'F');*/
}
