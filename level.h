#pragma once

/////////////////////////////////////
//Constants
const unsigned char xSizeRender = 25;
const unsigned char ySizeRender = 26;

const unsigned char wall = '#';
const unsigned char infoGame = '<';

const unsigned char levelData0[xSizeRender][ySizeRender + 1] =
{
	"##########################",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"#                #       #",
	"##########################",
	"# >                      #",
	"# >                      #",
	"# >                      #",
	"##########################",
};

//Function
unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case wall:			return 35;
	case infoGame:		return 62;
	}
}