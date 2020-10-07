// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

//перегрузить  инкременты mObj1OldY-Y

#include "TestApp.h"
#include "Figures.h"
TestApp::TestApp() : Parent(24 , 24)
{

	mObj1XOld = mObj1X = 10; 
	mObj1YOld = mObj1Y = 0;

	mObj2X = 20;
	mObj2Y = 3;

	mDirection = false;
}
void TestApp::DownFigure(float sum)
{
	if (sum > 1000)
	{
		
		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, '.');

		}
		mObj1Y++;

		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y,  cellSymbolFigure);
		}
		
	}
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
	
	mDirection = true;

	if (mObj1X < 1)
		mObj1X = 1;
	else if (mObj1X >= X_SIZE - 8)
		mObj1X = X_SIZE - 8;
	else if (mObj1Y >= Y_SIZE - 5)
		mObj1Y = Y_SIZE - 5;
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
	

	// ¬ращение
	if (mDirection)
	{
		Point p = a[1]; // указываем центр вращени€
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y; // y - y0
			int y = a[i].x - p.x; // x - x0
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, '.');
			a[i].x = p.x - x;
			a[i].y = p.y + y;
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, cellSymbolFigure);
		}
		mDirection = false;
	}
	// √оризонтальное перемещение
	if (mDirection)
	{
		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, '.');

		}
		++mObj1X;
		for (int i = 0; i < 4; i++)
		{
				SetChar(a[i].x+ mObj1X, a[i].y+ mObj1Y, cellSymbolFigure);
		}
		mDirection = false;
	}



	int n = 0; // задаЄм тип тетрамино
	if (a[0].x == -1)
	{
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] / 10;
			a[i].y = figures[n][i] % 10;

			SetChar(a[i].x+10, a[i].y, cellSymbolFigure);

		}
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
