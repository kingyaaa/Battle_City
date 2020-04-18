#include "Tank.h"
//#include"Brick.h"
void Tank::gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
int Tank::getVertexOne_x()
{
	if (m_dir == Dir::UP|| m_dir == Dir::RIGHT)
		return m_x1 + 2;
	if (m_dir == Dir::LEFT || m_dir == Dir::DOWN)
		return m_x1 - 2;
}
int Tank::getVertexOne_y()
{
	if (m_dir == Dir::UP || m_dir == Dir::LEFT)
		return m_y - 1;
	if (m_dir == Dir::RIGHT || m_dir == Dir::DOWN)
		return m_y + 1;
}
int Tank::getVertexTwo_x()
{
	if (m_dir == Dir::DOWN || m_dir == Dir::RIGHT)
		return m_x1 + 2;
	if (m_dir == Dir::UP || m_dir == Dir::LEFT)
		return m_x1 - 2;
}
int Tank::getVertexTwo_y()
{
	if (m_dir == Dir::UP || m_dir == Dir::RIGHT)
		return m_y - 1;
	if (m_dir == Dir::DOWN || m_dir == Dir::LEFT)
		return m_y + 1;
}
int Tank::getVertexThree_x()
{
	if (m_dir == Dir::DOWN || m_dir == Dir::LEFT)
		return m_x1 + 2;
	if (m_dir == Dir::RIGHT || m_dir == Dir::UP)
		return m_x1 - 2;
}
int Tank::getVertexThree_y()
{
	if (m_dir == Dir::RIGHT || m_dir == Dir::DOWN)
		return m_y - 1;
	if (m_dir == Dir::UP || m_dir == Dir::LEFT)
		return m_y + 1;
}
int Tank::getVertexFour_x()
{
	if (m_dir == Dir::DOWN || m_dir == Dir::RIGHT)
		return m_x1 - 2;
	if (m_dir == Dir::LEFT || m_dir == Dir::UP)
		return m_x1 + 2;
}
int Tank::getVertexFour_y()
{
	if (m_dir == Dir::LEFT || m_dir == Dir::DOWN)
		return m_y - 1;
	if (m_dir == Dir::UP || m_dir == Dir::RIGHT)
		return m_y + 1;
}
void Tank::DrawTankBody()
{
	//ˢ��
	//����̹��
	//����

	for (int i = m_x1 - 2; i <= m_x1 + 2; i += 2) {
		for (int j = m_y - 1; j <= m_y + 1; ++j) {
			gotoxy(i, j);
			//cout << "�~";
			Map::MoveLocation[i][j] = 1;
			Map::MoveLocation[i + 1][j] = 1;
		}
	}
	/**
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
	*/
	if (m_dir == Dir::UP || m_dir == Dir::DOWN) {
		for (int i = m_x1 - 2; i <= m_x1 + 2; i+=2) {
			gotoxy(i, m_y);
			cout << "�~";
			gotoxy(0, 0);
		}
	}
	if (m_dir == Dir::DOWN) {
		gotoxy(m_x1, m_y + 1);
		cout << "�~";
		gotoxy(m_x1 - 2, m_y - 1);
		cout << "�~";
		gotoxy(m_x1 + 2, m_y - 1);
		cout << "�~";
		gotoxy(0, 0);
	}
	if (m_dir == Dir::UP) {
		gotoxy(m_x1, m_y - 1);
		cout << "�~";
		gotoxy(m_x1 - 2, m_y + 1);
		cout << "�~";
		gotoxy(m_x1 + 2, m_y + 1);
		cout << "�~";
		gotoxy(0, 0);
	}
	if (m_dir == Dir::RIGHT || m_dir == Dir::LEFT) {
		for (int i = m_y - 1; i <= m_y + 1; i++) {
			gotoxy(m_x1, i);
			cout << "�~";
			gotoxy(0, 0);
		}
	}
	if (m_dir == Dir::LEFT) {
		gotoxy(m_x1 - 2, m_y);
		cout << "�~";
		gotoxy(m_x1 + 2, m_y - 1);
		cout << "�~";
		gotoxy(m_x1 + 2, m_y + 1);
		cout << "�~";
		gotoxy(0, 0);
	}
	if (m_dir == Dir::RIGHT) {
		gotoxy(m_x1 + 2, m_y);
		cout << "�~";
		gotoxy(m_x1 - 2, m_y - 1);
		cout << "�~";
		gotoxy(m_x1 - 2, m_y + 1);
		cout << "�~";
		gotoxy(0, 0);
	}
	//************************************/
	//cout << endl;
}
//�ı䷽��
/*void Tank::setBrickLocation(vector<BrickLocation>&brick)
{
	vector<BrickLocation>::iterator pv;
	for (pv = brick.begin(); pv != brick.end(); ++pv)
		MonitorBrick.push_back(*pv);
}*/
void MainTank::Move(int& right,int& down,Dir last_dir)
{
	//int flag = 1;
	ClearTankBody();
	int tmp_x1 = m_x1, tmp_y = m_y,tmp_head_x,tmp_head_y;
	char ch1,ch2;
	ch1 = _getch();
	ch2 = _getch();
	switch (ch2) {
		//����
	case 75: {
		m_dir = Dir::LEFT;
		if (m_dir != last_dir) {
			return;
		}
		right = -2;
		down = 0;
		m_x1 += right;
		m_x2 += right;
		m_y += down;
		
		if (WillKnockWall()) {
			m_x1 = tmp_x1;
			m_y = tmp_y;
			return;
		}
		break;
	}
		   //����
	case 77: {
		m_dir = Dir::RIGHT;
		if (m_dir != last_dir) {
			return;
		}
		right = 2;
		down = 0;
		m_x1 += right;
		m_x2 += right;
		m_y += down;

		if (WillKnockWall()) {
			m_x1 = tmp_x1;
			m_y = tmp_y;
			return;
		}
		break;
	}
		   //����
	case 72: {
		m_dir = Dir::UP;
		if (m_dir != last_dir) {
			return;
		}
		right = 0;
		down = -1;
		m_x1 += right;
		m_x2 += right;
		m_y += down;

		if (WillKnockWall()) {
			m_x1 = tmp_x1;
			m_y = tmp_y;
			return;
		}
		break;
	}
		   //����
	case 80: {
		m_dir = Dir::DOWN;
		if (m_dir != last_dir) {
			return;
		}
		right = 0;
		down = 1;
		m_x1 += right;
		m_x2 += right;
		m_y += down;

		if (WillKnockWall()) {
			m_x1 = tmp_x1;
			m_y = tmp_y;
			return;
		}
		break;
	}
	default:
		break;
	}
	//DrawTankBody();
}
void Tank::ClearTankBody()
{
	for (int i = m_x1 - 2; i <= m_x1 + 2; i += 2) {
		for (int j = m_y - 1; j <= m_y + 1; ++j) {
			gotoxy(i, j);
			cout << "  ";
			Map::MoveLocation[i][j] = 0;
			Map::MoveLocation[i + 1][j] = 0;
		}
	}
}
void MainTank::Display()
{
	int right = 0, down = 0;
	//while (1) {
	//if (_kbhit()){
			Move(right,down,m_dir);
			DrawTankBody();
	//}
}
/***************************************
	���̹�����ƶ���������һ���Ƿ��ײǽ
	�Ȼ�ȡ̹�˾�����ĸ�����
	����̹�˾���ǹͷ��һ����ǽ��ÿһ��������бȶ�
	�����һ����������ǽ��ĳһ�������غϣ�����һ��������
*********************************/
/********************************
	�򵥵���ײ��⣺
	ͨ������̹�˵��ĸ���������ķ�Χ������̹�˵��ĸ���������ķ�Χ�Ƿ��غ����ж��Ƿ����ײ
*********************************/
bool Tank::WillKnockWall()
{
	//���ݷ�λȷ��̹�˾���ͷһ�е�����
	int tmp1 = 0, tmp2 = 0, tmp3 = 0;
	if (m_dir == Dir::UP) {
		tmp1 = getVertexTwo_x();
		tmp2 = getVertexOne_x();
		tmp3 = getVertexOne_y();
	}
	if (m_dir == Dir::DOWN) {
		tmp1 = getVertexOne_x();
		tmp2 = getVertexTwo_x();
		tmp3 = getVertexOne_y();
	}
	if (m_dir == Dir::LEFT) {
		tmp1 = getVertexOne_y();
		tmp2 = getVertexTwo_y();
		tmp3 = getVertexOne_x();
	}
	if (m_dir == Dir::RIGHT) {
		tmp1 = getVertexTwo_y();
		tmp2 = getVertexOne_y();
		tmp3 = getVertexOne_x();
	}
	//����vector<BrickLocation>;
	vector<BrickLocation>::iterator pv;
	for (pv = Map::BrickList.begin(); pv != Map::BrickList.end(); ++pv){
		for (int j = tmp1; j <= tmp2; ++j) {
			if (((*pv).x == j && (*pv).y == tmp3 && (m_dir == Dir::UP || m_dir == Dir::DOWN))|| ((*pv).y == j && (*pv).x == tmp3 && (m_dir == Dir::LEFT || m_dir == Dir::RIGHT)))
				return true;
		}
	}
	for (int i = m_x1 - 2; i <= m_x1 + 2; i += 2) {
		for (int j = m_y - 1; j <= m_y + 1; ++j) {
			if (Map::MoveLocation[i][j] == 1)
				return true;
		}
	}
	return false;
}
/**********************************
	�о�̹���ƶ�
*********************************/
void EnemyTank::Display(int& right, int& down, int& changeDir)
{
	int tmp1, tmp2;
	//ClearTankBody();
	//m_x1 += right;
	//m_y += down;
	//Sleep(500);
	//Move(right, down,m_dir);
	DrawTankBody();
	//while (1) {
		ClearTankBody();
		tmp1 = m_x1, tmp2 = m_y;
		//��Ҫ��֪��ǰ���ƶ�����
		//10��һת
		if (limStep == 0) {
			//����Ҫ��ת����
			Move(right, down,m_dir);
		}
		if (!changeDir) {
			m_x1 += right;
			m_y += down;
			limStep--;
		}
		if (changeDir == 1)
			changeDir = 0;
		if (WillKnockWall()) {
			m_x1 = tmp1;
			m_y = tmp2;
			//��ս̹�˺͵о�̹�˵Ĳ�ͬ�����ڣ���ս̹���ڿ���ײǽʱ�޷��ƶ����ֶ�ת�Ʒ��򣬵о�̹���ڿ���ײǽʱ��Ҫ�Զ��ı䷽��
			Move(right, down, m_dir);
		}
		DrawTankBody();
		//Sleep(15);
	//}
}
void EnemyTank::Move(int& right,int &down,Dir last_dir)
{
	//ClearTankBody();
	//�����ƶ�����������
	srand((int)time(0));
	cur_dir = random(1, 5);
	srand((int)time(0));
	limStep = random(12,15);
	changeDir = 1;
	switch (cur_dir) {
	//����
	case 1: {
		m_dir = Dir::LEFT;
		right = -2;
		down = 0;
		/*limStep--;
		if (WillKnockWall()) {
			//��Ҫ�л��������޶��ĵ������ƶ���������;
			limStep = 10;
			return;
		}*/
		break;
		//right = -1;
		//down = 0;
	}
	//����
	case 2: {
		m_dir = Dir::RIGHT;
		right = 2;
		down = 0;
		break;
		//right = 1;
		//down = 0;
		//break;
	}
	//����
	/*case 3: {
		m_dir = Dir::UP;
		//right = 0;
		//down = -1;
		//break;
		if (m_dir != last_dir) {
			return;
		}
		right = 0;
		down = -1;
		m_x1 += right;
		m_x2 += right;
		m_y += down;
		break;
	}*/
	//����
	case 3:
	case 4:
	case 5:{
		m_dir = Dir::DOWN;
		//right = 0;
		//down = 1;
		//break;
		right = 0;
		down = 1;
		break;
	}
	default:break;
	}
}