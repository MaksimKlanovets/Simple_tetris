// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <assert.h>
#include <strsafe.h>
#include <malloc.h>

#pragma warning(disable : 4996)

#define MY_PERFORMENCE_COUNTER

#include "PerformanceCounter.h"
#include "level.h"


BaseApp::BaseApp(int xSize, int ySize) :
	X_SIZE(xSize), Y_SIZE(ySize),X_SIZE_FIELD(xSize-8), Y_SIZE_FIELD(xSize - 4)
{
	SMALL_RECT windowSize = {0, 0, X_SIZE, Y_SIZE};
	COORD windowBufSize = {X_SIZE+1, Y_SIZE+1};
	
	mConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleScreenBufferSize(mConsoleOutput, windowBufSize);
	SetConsoleWindowInfo(mConsoleOutput, TRUE, &windowSize);
	
	if(!SetConsoleScreenBufferSize(mConsoleOutput,  windowBufSize))
	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
	}
	if(!SetConsoleWindowInfo(mConsoleOutput, TRUE, &windowSize))
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsoleOutput, &cursorInfo);

	mChiBuffer = (CHAR_INFO*)malloc(((X_SIZE+1) * (Y_SIZE+1)) * sizeof(CHAR_INFO));

	mDwBufferSize.X = X_SIZE + 1;
	mDwBufferSize.Y = Y_SIZE + 1;		// размер буфера данных

	mDwBufferCoord.X = 0;
	mDwBufferCoord.Y = 0;				// координаты €чейки

	mLpWriteRegion.Left = 0;
	mLpWriteRegion.Top = 0;
	mLpWriteRegion.Right = X_SIZE + 1;
	mLpWriteRegion.Bottom = Y_SIZE + 1;	// пр€моугольник дл€ чтени€

	for (int y = 0; y < Y_SIZE + 1; y++)
	{
		for (int x = 0; x < X_SIZE + 1; x++)
		{

			switch (levelData0[y][x])
			{
			case wall:		SetChar(x, y, wall);	break;
			case cpnt:		SetChar(x, y, cpnt);	break;
			case infG:		SetChar(x, y, infG);	break;
			default:
				SetChar(x, y, ' ');		break;
			}
		}
	}
}

BaseApp::~BaseApp()
{
	free(mChiBuffer);
}

void BaseApp::SetChar(int x, int y, wchar_t c)
{
	mChiBuffer[x + (X_SIZE+1)*y].Char.UnicodeChar = c;
	mChiBuffer[x + (X_SIZE+1)*y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
	WriteConsoleOutput(mConsoleOutput, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion);

}

wchar_t BaseApp::GetChar(int x, int y)
{
	return mChiBuffer[x + (X_SIZE+1)*y].Char.AsciiChar;
}

void BaseApp::DownFigure(float sum)
{
	
}

void BaseApp::Render(HANDLE mConsoleOutput, const CHAR_INFO *mChiBuffer, COORD mDwBufferSize,
	COORD mDwBufferCoord, SMALL_RECT& mLpWriteRegion)
{
	if (!WriteConsoleOutput(mConsoleOutput, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion)) 
	{
		printf("WriteConsoleOutput failed - (%d)\n", GetLastError()); 
	}
	WriteConsoleOutput(mConsoleOutput, mChiBuffer, mDwBufferSize, mDwBufferCoord, &mLpWriteRegion);
}

void BaseApp::Run()
{
	///
	CStopwatch timer;
	int sum = 0;
	int counter = 0;
	int deltaTime = 0;
	/////
	int sumFigure = 0;

	int cnt =-1;
	while (1)
	{
		timer.Start();
		if (kbhit())
		{
			KeyPressed (getch());
		
			if (!FlushConsoleInputBuffer(mConsoleIn))
				cout<<"FlushConsoleInputBuffer failed with error "<<GetLastError();
		}
		

		UpdateF((float)deltaTime / 1000.0f);
		Render(mConsoleOutput, mChiBuffer, mDwBufferSize, mDwBufferCoord, mLpWriteRegion);
		Sleep(1);

		while (1)
		{
			deltaTime = timer.Now();
			if (deltaTime > 20)
				break;
		}

		sum += deltaTime;
		counter++;

		sumFigure += deltaTime;
		if (sumFigure > 100 && cnt == 0 )
		{
			DownFigure(sumFigure);
			cnt++;
			sumFigure = 0;
			cnt = 0;
		}
	
		

		if (sum >= 1000)
		{
			TCHAR  szbuff[255];
			StringCchPrintf(szbuff, 255, TEXT("FPS: %d"), counter);
			SetConsoleTitle(szbuff);
			DownFigure(sum);
			counter = 0;
			sum = 0;
			cnt = 0;
			
		}


	}
}