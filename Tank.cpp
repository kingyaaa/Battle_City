#include "Tank.h"
#include"Brick.h"
void Tank::gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
void Tank::DrawTankBody()
{
	//刷屏
	//绘制坦克
	//矩阵
	for (int i = m_x1 - 2; i <= m_x1 + 2; i += 2) {
		for (int j = m_y - 1; j <= m_y + 1; ++j) {
			gotoxy(i, j);
			cout << "▇";
		}
	}
	if (m_dir == Dir::UP) {
		gotoxy(m_x1 - 2, m_y - 1);
		cout << "  ";
		gotoxy(m_x1 + 2, m_y - 1);
		cout << "  ";
		gotoxy(m_x1, m_y + 1);
		cout << "  ";
	}
	if (m_dir == Dir::DOWN) {
		gotoxy(m_x1 - 2, m_y + 1);
		cout << "  ";
		gotoxy(m_x1 + 2, m_y + 1);
		cout << "  ";
		gotoxy(m_x1, m_y - 1);
		cout << "  ";
	}
	if (m_dir == Dir::LEFT) {
		gotoxy(m_x1 - 2, m_y - 1);
		cout << "  ";
		gotoxy(m_x1 - 2, m_y + 1);
		cout << "  ";
		gotoxy(m_x1 + 2, m_y);
		cout << "  ";
	}
	if (m_dir == Dir::RIGHT) {
		gotoxy(m_x1 + 2, m_y - 1);
		cout << "  ";
		gotoxy(m_x1 + 2, m_y + 1);
		cout << "  ";
		gotoxy(m_x1 - 2, m_y);
		cout << "  ";
	}
	//cout << endl;
}
//改变方向
void MainTank::Move(int& right,int& down)
{
	//int flag = 1;
	char ch;
	ch = _getch();
	switch (ch) {
		//向左
	case 75: {
		if (m_dir == Dir::LEFT) {
			return;
		}
		m_dir = Dir::LEFT;
		right = -1;
		down = 0;
		break;
	}
		   //向右
	case 77: {
		m_dir = Dir::RIGHT;
		right = 1;
		down = 0;
		break;
	}
		   //向上
	case 72: {
		m_dir = Dir::UP;
		right = 0;
		down = -1;
		break;
	}
		   //向下
	case 80: {
		m_dir = Dir::DOWN;
		right = 0;
		down = 1;
		break;
	}
	default:
		break;
	}
}
void Tank::ClearTankBody()
{
	for (int i = m_x1 - 2; i <= m_x1 + 2; i += 2) {
		for (int j = m_y - 1; j <= m_y + 1; ++j) {
			gotoxy(i, j);
				cout << "  ";
		}
	}
}
void MainTank::Display()
{
	int right = 0, down = 0;
	while (1) {
		if (_kbhit()) {
			Move(right,down);
			ClearTankBody();
			m_x1 += right;
			m_x2 += right;
			m_y += down;
			DrawTankBody();
		}
	}
}
void EnemyTank::Display()
{
	int right = 0, down = 0;
	Move(right, down);
	while (1) {
		//需要得知当前的移动方向
		//10步一转
		if (limStep == 0) {
			Move(right, down);
		}
		//返回值为一，再走会撞墙,一定要找到一个不会撞墙的方向
		while (WillKnockWall()) {
			Move(right, down);
		}
		ClearTankBody();
		m_x1 += right;
		m_x2 += right;
		m_y += down;
		limStep--;
		DrawTankBody();
		Sleep(500);
	}
}
bool Tank::WillKnockWall()
{
	//根据现在的方向和中心
	vector<BrickLocation>::iterator pv;
	//TODO
	return true;
}
void EnemyTank::Move(int& right,int &down)
{
	//产生移动方向的随机数
	srand((int)time(0));
	cur_dir = random(1, 4);
	limStep = 10;
	switch (cur_dir) {
	//向左
	case 1: {
		m_dir = Dir::LEFT;
		right = -1;
		down = 0;
	}
	//向右
	case 2: {
		m_dir = Dir::RIGHT;
		right = 1;
		down = 0;
		break;
	}
	//向上
	case 3: {
		m_dir = Dir::UP;
		right = 0;
		down = -1;
		break;
	}
	//向下
	case 4: {
		m_dir = Dir::DOWN;
		right = 0;
		down = 1;
		break;
	}
	default:break;
	}
}