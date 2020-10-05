// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include "Figures.h"
TestApp::TestApp() : Parent(24 , 24)
{

	mObj1XOld = mObj1X = 0;
	mObj1YOld = mObj1Y = 0;

	mObj2X = 10;
	mObj2Y = 12;

	mDirection = true;
}

void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 119) //w
		mObj1Y--;
	else if (btnCode == 115) //s
		mObj1Y++;
	else if (btnCode == 97) //a
		mObj1X--;
	else if (btnCode == 100) //d
		mObj1X++;




	/*if (mObj1X < 0)
		mObj1X = 0;
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

	// Горизонтальное перемещение
	if (mObj1X)
	{
		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x, a[i].y, '.');

		}
		for (int i = 0; i < 4; i++)
		{
			a[i].x += mObj1X;
			SetChar(a[i].x, a[i].y, cellSymbolFigure);
		}
	}
	

	int n = 6; // задаём тип тетрамино
	if (a[0].x == 0)
	{
		for (int i = 0; i < 4; i++)
		{

			a[i].x = figures[n][i] / 10;
			a[i].y = figures[n][i] % 10;

			SetChar(a[i].x, a[i].y, cellSymbolFigure);

		}
	}
	mObj1X = 0;

		
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
