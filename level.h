#pragma once

/////////////////////////////////////
//Constants
const unsigned char rowsCount = 25;
const unsigned char columnsCount = 24;

const unsigned char wall = '#';
const unsigned char cpnt = '.';
const unsigned char infG = '>';



const unsigned char levelData0[rowsCount][columnsCount +1 ] =
{
	"#######################",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"#...............#      #",
	"########################",
	"# >                    #",
	"# >                    #",
	"# >                    #",
	"########################",
};

//Function
unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case wall:			return 35;
	case cpnt:			return 46;
	case infG:			return 62;

	}
	return '?' ;
}