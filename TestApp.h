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

		int mLevel;
		int mScore;
		int mPoints;
	public:
		TestApp();
		void DownFigure(float sum);
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		void Initializefigure();

		////////////////////////////////////////////////////////////////
		// function checkCoordForMove
		bool checkCoordForMove(struct Point *ab);

		//�������� �� ��� ����
		bool CanStepBelow();
		//������� ������
		void deleteFigure(struct Point* ab);
		//���������� ����� ���������� ������
		void setFigureNewCoord();
		//���������� ������ �� ������ ����������
		void setFigureOldCoord();
		// function rotatefigure
		bool CanRotateFigure( );
		//����� �� ������� ������
	
		void CanDeleteLineBoard();
		void GameEnded();
		bool CanCreateNewFigure();

		//���������� �������
		void SetLevel();
		//���������� �������� 
		void SetScore();
		//���������� ���� 
		void SetPoints();
		
};
