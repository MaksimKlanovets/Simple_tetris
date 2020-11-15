#include "TestApp.h"
#include "Figures.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include "PerformanceCounter.h"

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

	mLevel = 1;
	mScore = 1;
	mPoints = 0;
}
void TestApp::DownFigure(float sum){
		
	if (figureFall == true && sum >100)
	{
		KeyPressed(115);
	}
	else if (sum >= 1000)
	{
		
		KeyPressed(1);
	}
}

void TestApp::KeyPressed(int btnCode)
{
	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;

	switch (btnCode)
	{
	case 119://w
	{
		//mObj1Y--;
		break;
	}
	case 115: //s
	{
		figureFall = true;
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
	case 1://падение
	{
		mObj1Y++;
		break;
	}
	default:
		break;
	}
	
	if(mRotate && CanRotateFigure()){ 
		//стереть старые коордитаты
		deleteFigure(structA);
		//установить новые
		setFigureNewCoord();
	}
	
	//проверяем следующие координаты
	if (checkCoordForMove(structA))
	{
		//стереть старые коордитаты
		deleteFigure(structA);
		//установить новые
		setFigureNewCoord();
	}
	//проверяем следующие координаты

	//если фолс новые коорд = страрым
	else if (!CanStepBelow())
	{
		//проверяем есть ли возможность удалить полосу
		CanDeleteLineBoard();
		figureFall = false;
		createNewFigure = true;

	}
	else {
		  mObj1X = mObj1XOld;
		  mObj1Y = mObj1YOld;
	}
	
	//создание новой фигуры
	Initializefigure();
}

bool TestApp::CanStepBelow()
{
	bool bResultWork = true;
	
		deleteFigure(structA);
		for (int i = 0; i < 4; i++)
		{
			if (GetChar(structA[i].x + mObj1XOld, structA[i].y + mObj1YOld+1) == gWallLevelData ||
				GetChar(structA[i].x + mObj1XOld, structA[i].y + mObj1YOld+1) == cellSymbolFigure)
			{
				bResultWork = false;
			}
		}
		setFigureOldCoord();
	
	return bResultWork;
}

void TestApp::deleteFigure(Point* ab)
{
	for (int i = 0; i < 4; i++) {
		SetChar(ab[i].x + mObj1XOld, ab[i].y + mObj1YOld, gPoingLevelData);
	}
}
void TestApp::setFigureNewCoord()
{
	for (int i = 0; i < 4; i++) {
		SetChar(structA[i].x + mObj1X, structA[i].y + mObj1Y, cellSymbolFigure);
	}
}
void TestApp::setFigureOldCoord()
{
	for (int i = 0; i < 4; i++) {
		SetChar(structA[i].x + mObj1XOld, structA[i].y + mObj1YOld, cellSymbolFigure);
	}
}
bool TestApp::CanRotateFigure()
{
	
	bool bResultWork = true;
	for (int i = 0; i < 4; i++)
	{
		structB[i] = structA[i];
	}
	
	// Вращение
		Point p = structA[2]; // указываем центр вращения
	
		for (int i = 0; i < 4; i++) {
			int x = structB[i].y - p.y; // y - y0
			int y = structB[i].x - p.x; // x - x0
			
				structB[i].x = p.x - x;
				structB[i].y = p.y + y;
		
		}
		if (checkCoordForMove(structB))
		{
			deleteFigure(structA);
			for (int i = 0; i < 4; i++)
			{
				structA[i] = structB[i];
			}
		}
		else {
			bResultWork = false;
		}
		mRotate = false;
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
void TestApp::GameEnded()
{
	//SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	unsigned char endGame[]={'Y','O','U', ' ','L','O','S','E','!','\n'};
	for (int i = 0; endGame[i] != '\n'; i++)
	{
		
		SetChar(4 + i, 10, endGame[i]);
	}

}
bool TestApp::CanCreateNewFigure()
{
	bool bResultWork = true;
	for (int i = 0; i < 4; i++)
	{
		if (GetChar(structA[i].x + mObj1X, structA[i].y + mObj1Y) == gWallLevelData ||
			GetChar(structA[i].x + mObj1X, structA[i].y + mObj1Y) == cellSymbolFigure)
		{
			bResultWork = false;
		}
	}
	return bResultWork;
}

void TestApp::SetLevel()
{

}
bool TestApp::checkCoordForMove(Point *ab)
{
	bool bResultWork = true;
	if (mObj1XOld != mObj1X || mObj1YOld != mObj1Y || mRotate == true)
	{
		deleteFigure(structA);
		for (int i = 0; i < 4; i++)
		{
			if (GetChar(ab[i].x + mObj1X, ab[i].y + mObj1Y) == gWallLevelData ||
				GetChar(ab[i].x + mObj1X, ab[i].y + mObj1Y) == cellSymbolFigure)
			{
				bResultWork = false;
			}
		} 
		setFigureOldCoord();
	}
	return bResultWork;
}

void TestApp::Initializefigure(){
	
	if (createNewFigure == true )	{
		
		mObj1XOld = mObj1X = 7;
		mObj1YOld = mObj1Y = 1;
	
		if (!CanCreateNewFigure())
		{
			GameEnded();
		}

		gPreviewNextFigure = rand() % 7;

		for (int y = 1; y < 10; y++)
		{
			for (int i = X_SIZE_FIELD + 1; i < X_SIZE - 1; i++)
			{
				SetChar(i, y, ' ');
			}
		}

		for (int i = 0; i < 4; i++)	{
			
			structA[i].x = figures[gCreateFigure][i] % 2;
			structA[i].y = (figures[gCreateFigure][i] / 2) - 0.9;
			SetChar(structA[i].x + mObj1X, structA[i].y+mObj1Y, cellSymbolFigure);

			// превью следующей фигуры
			structB[i].x = figures[gPreviewNextFigure][i] % 2;
			structB[i].y = (figures[gPreviewNextFigure][i] / 2)-0.9;
			SetChar(structB[i].x + mObj2X, structB[i].y+mObj2Y, cellSymbolFigure);
		}
		createNewFigure = false;
		figureFall = false;
		gCreateFigure = gPreviewNextFigure;
	}

	SetLevel();
}
 
void TestApp::UpdateF(float deltaTime){
	
	Initializefigure();

	/*if (mObj1Y <=  1 && !CanStepBelow())
	{
		GameEnded();
	}*/
	
}

