#include "plane_console_functios.h"

void gotoxy(int x, int y)//Функция манипуляции курсором
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}