// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		
		
		int mObj1XOld;
		int mObj1YOld;
		
		int mObj1X;
		int mObj1Y;
		int mObj2X;
		int mObj2Y;

		bool mDirection;
		bool mRotate;

		bool createNewFigure;
		bool figureFall;

		int gCreateFigure;
	public:
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		void Initializefigure();


		
		////////////////////////////////////////////////////////////////
		// function checkCoordForMove
		bool checkCoordForMove();

		//проверка на ход вниз
		bool CanStepBelow();
		//стереть фигуру
		void deleteFigure();
		//установить новые координаты фигуры
		void setFigureNewCoord();
		//установить фигуру на старые координаты
		void setFigureOldCoord();
		// function rotatefigure
		bool CanRotateFigure();
		//можно ли удалить полосу
		void CanDeleteLineBoard();
};
