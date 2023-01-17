#pragma once
//#include <windows.h>

//bool hinit(HANDLE &);

enum {COL_BLACK=0,COL_RED,COL_GREEN,COL_YELLOW,
	  COL_BLUE,COL_PURPLE,COL_CYAN,COL_WHITE};
enum HBST {
	STT_MAIN = 0,
	STT_HELP,
	STT_CHOOSE,
	STT_WALL
};
#define cls printf("\033[2J")

void outch(char ch, int textcol=7, int bgcol=0);

int getk();
