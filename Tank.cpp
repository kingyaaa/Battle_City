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
	//ˢ��
	//����̹��
	//����
	for (int i = m_x1 - 2; i <= m_x1 + 2; i += 2) {
		for (int j = m_y - 1; j <= m_y + 1; ++j) {
			gotoxy(i, j);
			cout << "�~";
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
//�ı䷽��
void MainTank::Move(int& right,int& down)
{
	//int flag = 1;
	char ch;
	ch = _getch();
	switch (ch) {
		//����
	case 75: {
		if (m_dir == Dir::LEFT) {
			return;
		}
		m_dir = Dir::LEFT;
		right = -1;
		down = 0;
		break;
	}
		   //����
	case 77: {
		m_dir = Dir::RIGHT;
		right = 1;
		down = 0;
		break;
	}
		   //����
	case 72: {
		m_dir = Dir::UP;
		right = 0;
		down = -1;
		break;
	}
		   //����
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
		//��Ҫ��֪��ǰ���ƶ�����
		//10��һת
		if (limStep == 0) {
			Move(right, down);
		}
		//����ֵΪһ�����߻�ײǽ,һ��Ҫ�ҵ�һ������ײǽ�ķ���
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
	//�������ڵķ��������
	vector<BrickLocation>::iterator pv;
	//TODO
	return true;
}
void EnemyTank::Move(int& right,int &down)
{
	//�����ƶ�����������
	srand((int)time(0));
	cur_dir = random(1, 4);
	limStep = 10;
	switch (cur_dir) {
	//����
	case 1: {
		m_dir = Dir::LEFT;
		right = -1;
		down = 0;
	}
	//����
	case 2: {
		m_dir = Dir::RIGHT;
		right = 1;
		down = 0;
		break;
	}
	//����
	case 3: {
		m_dir = Dir::UP;
		right = 0;
		down = -1;
		break;
	}
	//����
	case 4: {
		m_dir = Dir::DOWN;
		right = 0;
		down = 1;
		break;
	}
	default:break;
	}
}