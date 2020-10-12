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
	mObj1Y++;
	
	if (sum > 1000 && CanMove())
	{
		if (mObj1Y > Y_SIZE - 6)
			mObj1Y = Y_SIZE - 6;


		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, '.');
			

		}
		mObj1YOld = mObj1Y;

		for (int i = 0; i < 4; i++)
		{
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y,  cellSymbolFigure);
			b[i] = a[i];
		}
		
	}

}
void TestApp::Initializefigure(bool test)
{
	
	if (testFigure == true)
	{
		n = rand() % 7;
		//n = 2;
		
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] / 2;
			a[i].y = figures[n][i] % 2;

			SetChar(a[i].x + mObj1X, a[i].y+ mObj1Y, cellSymbolFigure);
			b[i] = a[i];
		}
		testFigure = false;
	}
	
}
bool TestApp::CheckNewCoord(int objX, int objY)
{
	for (int i = 0; i < 4; i++)
	{
		if (a[objX].x + mObj1X == a[i].x + mObj1XOld &&
			a[objY].y + mObj1Y == a[i].y + mObj1YOld && objX !=i || 
			(GetChar(a[i].x + mObj1X, a[i].y + mObj1Y))== '#' )
		{
			return false;
		}
	}

	return true;
}
bool TestApp::CanMove()
{
	bool isTemp = true;
	for (int i = 0; i < 4; i++)
	{
		// проверка на знак фигуры
		if (CheckNewCoord(i, i)== true && 
			GetChar(a[i].x + mObj1X, a[i].y + mObj1Y) == cellSymbolFigure )
		{
			testFigure = true;
			mObj1XOld = mObj1X = 10;
			mObj1YOld = mObj1Y = 1;
			isTemp= false;
		}

		//проверка на У 
		else if (a[i].y + mObj1Y == (Y_SIZE - 4)   )
		{
			testFigure = true;
			mObj1XOld = mObj1X = 10;
			mObj1YOld = mObj1Y = 1;
			isTemp = false;
		}

		if (GetChar(a[i].x + mObj1X, a[i].y + mObj1Y) == '#')
		{
			
			return  false;
		}
	
		 
	}

	if (isTemp == true) 
	{
		return true; }
	else {
		return false; }
}



void TestApp::KeyPressed(int btnCode)
{
	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y ;
	//if (btnCode == 119) //w
	//	mObj1Y--;
	if (btnCode == 115) //s
	{
		mObj1Y++;
	}

		
	else if (btnCode == 97) //a
	{
		mObj1X--;
		if(CheckNewCoord(0,0))
		{ mDirection = true; }
		else {
			mObj1X++; 
			mDirection = false;
		}
		
	}
		
	else if (btnCode == 100) //d
	{
		mObj1X++;
		if (CanMove())
		{
			mDirection = true;
		}
		else {
			mObj1X--;
			mDirection = false;
		}
	}
		
	else if (btnCode == 32)
	{
		mRotate = true;
		return;
	}
	
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
	if (mDirection && CanMove())
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

}
