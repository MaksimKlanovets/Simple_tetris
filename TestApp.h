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

		bool testFigure;
		bool figureFall;

		int gCreateFigure;
	public:
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		virtual void DownFigure(float );
		void Initializefigure(bool test);

		bool CanMove();
		bool CheckNewCoord(int objX,int objY, bool r= false );
		void figureStepDown();
};
