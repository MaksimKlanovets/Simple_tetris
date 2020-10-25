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

	testFigure = true;
	figureFall = false;
	gCreateFigure = rand() % 7;
}
void TestApp::DownFigure(float sum){
	if (sum >= 100 && figureFall == true){
		figureStepDown();
	}
	else if (sum >=1000){
		figureStepDown();
	}
}

void TestApp::Initializefigure(bool test){
	
	if (testFigure == true)	{
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
		testFigure = false;
		gCreateFigure = gPreviewNextFigure;
	}
	
}
bool TestApp::CheckNewCoord(int objX, int objY,bool r )
{
	bool tempCanMove = true;
		switch (r)
		{
			case false:	{
				for (int i = 0; i < 4; i++)	{
					if (a[objX].x + mObj1X == a[i].x + mObj1XOld &&
						a[objY].y + mObj1Y == a[i].y + mObj1YOld && objX != i ||
						(GetChar(a[i].x + mObj1X, a[i].y + mObj1Y)) == '#' &&
						GetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld + 1) != '.')	{
						tempCanMove = false;
						break;
					}
				}
				break;
			}
			case true: {

				if (GetChar(objX + mObj1X, objY + mObj1Y) == '.' ||
					GetChar(objX + mObj1X, objY + mObj1Y) == cellSymbolFigure) {
					tempCanMove = false;
				}
				break;
			}
		}
	return tempCanMove;
}
void TestApp::figureStepDown(){
	mObj1Y++;
	if (CanMove()){
		if (mObj1Y > Y_SIZE - 6) {
			mObj1Y = Y_SIZE - 6;
		}
		
		for (int i = 0; i < 4; i++)	{
			SetChar(a[i].x + mObj1XOld, a[i].y + mObj1YOld, '.');
		}
		mObj1YOld = mObj1Y;

		for (int i = 0; i < 4; i++)	{
			SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, cellSymbolFigure);
		}
	}
}

bool TestApp::CanMove(){
	bool isTemp = true;
	for (int i = 0; i < 4; i++)	{
		// проверка на знак фигуры
		if (CheckNewCoord(i, i)== true && 
			GetChar(a[i].x + mObj1X, a[i].y + mObj1Y) == cellSymbolFigure)	{
			testFigure = true;
			mObj1XOld = mObj1X = 7;
			mObj1YOld = mObj1Y = 1;
			isTemp= false;
			figureFall = false;
		}

		//проверка на У 
		else if (a[i].y + mObj1Y == (Y_SIZE - 4)){
			testFigure = true;
			mObj1XOld = mObj1X = 7;
			mObj1YOld = mObj1Y = 1;
			isTemp = false;
			figureFall = false;
		}

		if (GetChar(a[i].x + mObj1X, a[i].y + mObj1Y) == '#'){
			return  false;
		}
	}
	if (!isTemp){
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
	return isTemp;
}


void TestApp::KeyPressed(int btnCode)
{
	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;

	//if (btnCode == 119) //w
	//	mObj1Y--;
	if (btnCode == 115){ //s
		figureFall = true;
	}

	else if (btnCode == 97){ //a
		mObj1X--;
		if(CanMove()){
			mDirection = true; }
		else {
			mObj1X++; 
			mDirection = false;
		}
	}
		
	else if (btnCode == 100){//d
	
		mObj1X++;
		if (CanMove())	{
			mDirection = true;
		}
		else {
			mObj1X--;
			mDirection = false;
		}
	}
	else if (btnCode == 32)	{
		mRotate = true;
		return;
	}
}

void TestApp::UpdateF(float deltaTime){
	
	Initializefigure(testFigure);

	// Вращение
	if (mRotate){
		Point p = a[1]; // указываем центр вращения
		for (int i = 0; i < 4; i++)	{
			int x = a[i].y - p.y; // y - y0
			int y = a[i].x - p.x; // x - x0

			if (CheckNewCoord(p.x - x, p.y + y, mRotate)){
				mRotate = false;
				break;
			}
		}

		for (int i = 0; i < 4; i++)	{
				SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, '.');
		}
		for (int i = 0; i < 4; i++)	{
				int x = a[i].y - p.y; // y - y0
				int y = a[i].x - p.x; // x - x0
				
				if (mRotate ){
					a[i].x = p.x - x;
					a[i].y = p.y + y;
					SetChar(a[i].x + mObj1X, a[i].y + mObj1Y, cellSymbolFigure);
					continue;
				}
				break;
		}
		mRotate = false;
	}

	// Горизонтальное перемещение
	if (mDirection && CanMove()){
		for (int i = 0; i < 4; i++)	{
			SetChar(a[i].x + mObj1XOld,  a[i].y + mObj1YOld, '.');
		}
		for (int i = 0; i < 4; i++)	{
				SetChar(a[i].x+ mObj1X, a[i].y+ mObj1Y, cellSymbolFigure);
		}
		mDirection = false;
		mObj1XOld = mObj1X;
		mObj1YOld = mObj1Y;
	}

	
}
