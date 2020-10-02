#pragma once

/////////////////////////////////////
//Constants
const unsigned char xSizeRender = 26;
const unsigned char ySizeRender = 25;

const unsigned char wall = '#';


const unsigned char levelData0[xSizeRender][ySizeRender +2 ] =
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
	"#                        #",
	"#                        #",
	"#                        #",
	"##########################",
};

//Function
unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case wall:			return 35;
	}
}