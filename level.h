#pragma once

/////////////////////////////////////
//Constants
const unsigned char rowsCount = 25;
const unsigned char columnsCount = 25;

const unsigned char wall = '#';
const unsigned char point = '.';



const unsigned char levelData0[rowsCount][columnsCount +1 ] =
{
	"#########################",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#................#      #",
	"#########################",
	"#                       #",
	"#                       #",
	"#                       #",
	"#########################",
};

//Function
unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case wall:			return 35;
	case point:			return 46;

	}
	return '?' ;
}