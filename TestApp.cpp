// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

//перегрузить  инкременты mObj1OldY-Y


#include "TestApp.h"
#include "Figures.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include "PerformanceCounter.h"
 // задаём тип тетрамино
int gPreviewNextFigure ;

TestApp::TestApp() : Parent(24 , 24){

	mObj1XOld = mObj1X = 7; 
	mObj1YOld = mObj1Y = 1;

	mObj2X = 19;
	mObj2Y = 1;

	mDirection = false;
	mRotate = false;
	srand(static_cast<unsigned int>(time(0)));

	createNewFigure = true;
	figureFall = false;
	gCreateFigure = rand() % 7;
}
//void TestApp::DownFigure(float sum){
//	if (sum >= 100 && figureFall == true){
//		figureStepDown();
//	}
//	else if (sum >=1000){
//		figureStepDown();
//	}
//}

void TestApp::KeyPressed(int btnCode)
{
	

	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;

	
	switch (btnCode)
	{
	case 119://w
	{
		mObj1Y--;
		break;
	}
	case 115: //s
	{
		mObj1Y++;
		break;
	}

	case 97://a
	{
		mObj1X--;
		break;
	}
	case 100://d
	{
		mObj1X++;
		break;
	}

	case 32://space
	{
		mRotate = true;
		break;
	}
	default:
		break;
	}
	
	CanRotateFigure();
	//проверяем следующие координаты
	if (checkCoordForMove())
	{
		//стереть старые коордитаты
		deleteFigure();
		//установить новые
		setFigureNewCoord();
	}

	//если фолс новые коорд = страрым
	else if (!CanStepBelow())
	{
		  
		  createNewFigure = true;
	}
	else {
		  mObj1X = mObj1XOld;
		  mObj1Y = mObj1YOld;
	}
	
	//if (mObj1X < 1) { mObj1X = 1; }

	//проверяем есть ли возможность удалить полосу
	CanDeleteLineBoard();


	//создание новой фигуры
	Initializefigure();
}

bool TestApp::CanStepBelow()
{
	bool bResultWork = true;
	
		deleteFigure();
		for (int i = 0; i < 4; i++)
		{
			if (GetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld+1) == gWallLevelData ||
				GetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld+1) == cellSymbolFigure)
			{
				bResultWork = false;
			}
		}
		setFigureOldCoord();
	
	return bResultWork;
}

void TestApp::deleteFigure()
{
	for (int i = 0; i < 4; i++) {
		SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, gPoingLevelData);
	}
}
void TestApp::setFigureNewCoord()
{
	for (int i = 0; i < 4; i++) {
		SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, cellSymbolFigure);
	}
}
void TestApp::setFigureOldCoord()
{
	for (int i = 0; i < 4; i++) {
		SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, cellSymbolFigure);
	}
}
bool TestApp::CanRotateFigure()
{

	bool bResultWork = true;
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
	}
	deleteFigure();
	// Вращение
		Point p = a[1]; // указываем центр вращения
		for (int i = 0; i < 4; i++) {
			int x = a[i].y - p.y; // y - y0
			int y = a[i].x - p.x; // x - x0

			
		}

		for (int i = 0; i < 4; i++) {
			int x = a[i].y - p.y; // y - y0
			int y = a[i].x - p.x; // x - x0
			
				a[i].x = p.x - x;
				a[i].y = p.y + y;
		
		}
		if (!checkCoordForMove())
		{
			for (int i = 0; i < 4; i++)
			{
				a[i] = b[i];
			}
			bResultWork = false;

		}
		setFigureOldCoord();

	return bResultWork;
}
void TestApp::CanDeleteLineBoard()
{
	/////////////////////////////////
				//----ПРОВЕРКА ЛИНИИ----//
	int tempcnt = Y_SIZE_FIELD - 1;
	for (int y = Y_SIZE_FIELD - 1; y > 0; y--) {
		int count = 0;
		for (int x = 1; x < X_SIZE_FIELD; x++) {
			if (GetChar(x, y) == cellSymbolFigure) {
				count++;
			}
			SetChar(x, tempcnt, GetChar(x, y));
		}
		if (count < (X_SIZE_FIELD - 1)) {
			tempcnt--;
		}
	}
}
bool TestApp::checkCoordForMove()
{
	bool bResultWork = true;
	if (mObj1XOld != mObj1X || mObj1YOld != mObj1Y || mRotate == true)
	{
		deleteFigure();
		for (int i = 0; i < 4; i++)
		{
			if (GetChar(a[i].x + mObj1X, a[i].y + mObj1Y) == gWallLevelData ||
				GetChar(a[i].x + mObj1X, a[i].y + mObj1Y) == cellSymbolFigure)
			{
				bResultWork = false;
			}
		} 
		setFigureOldCoord();
	}
	

	return bResultWork;
}



void TestApp::Initializefigure(){
	
	if (createNewFigure == true)	{

		mObj1XOld = mObj1X = 7;
		mObj1YOld = mObj1Y = 1;

		gPreviewNextFigure = rand() % 7;

		for (int y = 1; y < 10; y++)
		{
			for (int i = X_SIZE_FIELD + 1; i < X_SIZE - 1; i++)
			{
				SetChar(i, y, ' ');
			}
		}

		for (int i = 0; i < 4; i++)	{
			a[i].x = figures[gCreateFigure][i] % 2;
			a[i].y = figures[gCreateFigure][i] / 2;
			SetChar(a[i].x + mObj1X, a[i].y+mObj1Y, cellSymbolFigure);

			// превью следующей фигуры
			b[i].x = figures[gPreviewNextFigure][i] % 2;
			b[i].y = figures[gPreviewNextFigure][i] / 2;
			SetChar(b[i].x + mObj2X, b[i].y+mObj2Y, cellSymbolFigure);

			
		}
		createNewFigure = false;
		gCreateFigure = gPreviewNextFigure;
	}
	
}
 

void TestApp::UpdateF(float deltaTime){
	
	
	Initializefigure();
	


	
}

