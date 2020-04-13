#include "Brick.h"
void Brick::DrawBrick()
{
	//绘制整个地图
	//边框
	for (int j = 0; j <= 80; j +=2) {
		gotoxy(j, 0);
		cout << "▇";
	}
	for (int i = 1; i < 39; i++) {
		gotoxy(0, i);
		cout << "▇";
	}
	for (int j = 1; j < 39; j++) {
		gotoxy(80, j);
		cout << "▇";
	}
	for (int i = 2; i < 80; i+=2) {
		gotoxy(i, 38);
		cout << "▇";
	}
	//cout << endl;
	//绘制普通墙壁
	for (int y = 4; y <= 12; ++y) {
		for (int x = 8; x <= 12; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 20; x <= 24; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 56; x <= 60; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 68; x <= 72; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 21; y <= 33; ++y) {
		for (int x = 8; x <= 12; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 20; x <= 24; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 56; x <= 60; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 68; x <= 72; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 4; y <= 9; ++y) {
		for (int x = 32; x <= 36; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 44; x <= 48; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 21; y <= 30; ++y) {
		for (int x = 32; x <= 36; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 44; x <= 48; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 13; y <= 15; ++y) {
		for (int x = 32; x <= 36; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 44; x <= 48; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 16; y <= 17; y++) {
		for (int x = 2; x <= 6; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 14; x <= 24; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 56; x <= 66; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
		for (int x = 74; x <= 78; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	for (int y = 21; y <= 24; ++y) {
		for (int x = 38; x <= 42; x += 2) {
			gotoxy(x, y);
			cout << "〓";
		}
	}
	//绘制铁墙
	for (int y = 7; y <= 8; ++y) {
		for (int x = 38; x <= 42; x += 2) {
			gotoxy(x, y);
			cout << "▇";
		}
	}
	for (int x = 2; x <= 6; x += 2) {
		gotoxy(x, 18);
		cout << "▇";
	}
	for (int x = 74; x <= 78; x += 2) {
		gotoxy(x, 18);
		cout << "▇";
	}
	for (int x = 36; x <= 44; x += 2) {
		gotoxy(x, 35);
		cout << "〓";
	}
	for (int y = 36; y <= 37; y++) {
		gotoxy(36, y);
		cout << "〓";
		gotoxy(44, y);
		cout << "〓";
	}
	gotoxy(40, 37);
	cout << "╬";
	cout << endl;
}
void Brick::setBrick()
{
	BrickLocation bl;
	for (int j = 0; j < 80; j += 2) {
		//BrickLocation bl;
		bl.x = j;
		bl.y = 0;
		BrickList.push_back(bl);
	}
	for (int j = 0; j < 80; j += 2) {
		//BrickLocation bl;
		bl.x = j;
		bl.y = 29;
		BrickList.push_back(bl);
	}
	for (int i = 1; i < 29; i++) {
		//BrickLocation bl;
		bl.x = 0;
		bl.y = i;
		BrickList.push_back(bl);
	}
	for (int i = 1; i < 29; ++i) {
		bl.x = 78;
		bl.y = i;
		BrickList.push_back(bl);
	}
}
void Brick::gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}