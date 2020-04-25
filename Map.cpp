#include "Map.h"
//静态成员变量需要再定义一次
vector<BrickLocation>Map::BrickList;
int Map::MoveLocation[80][40] = { 0 };
void Map::color(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void Map::DrawBrick()
{
	//绘制整个地图
	//边框
	BrickLocation bl;
	for (int j = 0; j <= 80; j += 2) {
		bl.x = j;
		bl.y = 0;
		bl.UnAttacked = true;
		Map::BrickList.push_back(bl);
		gotoxy(j, 0);
		cout << "▇";
	}
	for (int i = 1; i < 39; i++) {
		bl.x = 0;
		bl.y = i;
		bl.UnAttacked = true;
		BrickList.push_back(bl);
		gotoxy(0, i);
		cout << "▇";
	}
	for (int j = 1; j < 39; j++) {
		bl.x = 80;
		bl.y = j;
		bl.UnAttacked = true;
		BrickList.push_back(bl);
		gotoxy(80, j);
		cout << "▇";
	}
	for (int i = 2; i < 80; i += 2) {
		bl.x = i;
		bl.y = 38;
		bl.UnAttacked = true;
		BrickList.push_back(bl);
		gotoxy(i, 38);
		cout << "▇";
	}
	color(7);
	//cout << endl;
	//绘制普通墙壁
	for (int y = 4; y <= 12; ++y) {
		for (int x = 8; x <= 12; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 20; x <= 24; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 56; x <= 60; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 68; x <= 72; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 21; y <= 33; ++y) {
		for (int x = 8; x <= 12; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 20; x <= 24; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 56; x <= 60; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 68; x <= 72; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 4; y <= 9; ++y) {
		for (int x = 32; x <= 36; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 44; x <= 48; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 21; y <= 30; ++y) {
		for (int x = 32; x <= 36; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 44; x <= 48; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 13; y <= 15; ++y) {
		for (int x = 32; x <= 36; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 44; x <= 48; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 16; y <= 17; y++) {
		for (int x = 2; x <= 6; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 14; x <= 24; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 56; x <= 66; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 74; x <= 78; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 21; y <= 24; ++y) {
		for (int x = 38; x <= 42; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = false;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "〓";
		}
	}
	color(15);
	//绘制铁墙
	for (int y = 7; y <= 8; ++y) {
		for (int x = 38; x <= 42; x += 2) {
			bl.x = x;
			bl.y = y;
			bl.UnAttacked = true;
			BrickList.push_back(bl);
			gotoxy(x, y);
			cout << "▇";
		}
	}
	/*for (int x = 2; x <= 6; x += 2) {
		bl.x = x;
		bl.y = 18;
		bl.UnAttacked = true;
		BrickList.push_back(bl);
		gotoxy(x, 18);
		cout << "▇";
	}
	for (int x = 74; x <= 78; x += 2) {
		bl.x = x;
		bl.y = 18;
		bl.UnAttacked = true;
		BrickList.push_back(bl);
		gotoxy(x, 18);
		cout << "▇";
	}*/
	color(7);
	for (int x = 36; x <= 44; x += 2) {
		bl.x = x;
		bl.y = 35;
		bl.UnAttacked = false;
		BrickList.push_back(bl);
		gotoxy(x, 35);
		cout << "〓";
	}
	for (int y = 36; y <= 37; y++) {
		bl.x = 36;
		bl.y = y;
		bl.UnAttacked = false;
		BrickList.push_back(bl);
		gotoxy(36, y);
		cout << "〓";
		bl.x = 44;
		bl.y = y;
		bl.UnAttacked = false;
		BrickList.push_back(bl);
		gotoxy(44, y);
		cout << "〓";
	}
	//for(int x = )
	color(7);
	for (int x = 38; x <= 42; x += 2) {
		bl.x = x;
		bl.y = 37;
		bl.UnAttacked = false;
		BrickList.push_back(bl);
		gotoxy(x, 37);
		cout << "〓";
	}
	gotoxy(40, 36);
	bl.x = 40;
	bl.y = 36;
	bl.UnAttacked = false;
	BrickList.push_back(bl);
	cout << "╬";
	Map::MoveLocation[40][36] = 1;
	Map::MoveLocation[40][37] = 1;
	cout << endl;
}
void Map::gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}