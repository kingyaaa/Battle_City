#include"Tank.h"
#include"Brick.h"
#include<iostream>
#include<Windows.h>
using namespace std;
void hide();//Òþ²Ø¹â±ê
int main()
{
	/*HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size;
	size.X = 200;
	size.Y = 200;
	SetConsoleScreenBufferSize(hOut, size);*/
	hide();
	Brick brick;
	brick.DrawBrick();
	//MainTank mainTank;
	//mainTank.DrawTankBody();
	//mainTank.Display();
	//EnemyTank enemy;
	//enemy.DrawTankBody();
	//enemy.Display();
}
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}