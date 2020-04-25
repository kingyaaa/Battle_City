#include "Bullet.h"
vector<Bullet*>Bullet::listBullet;
//int Bullet::BulletCrash = 0;
/***************************
���캯��
����ֵ��̹��ǹ�ڵ�����
*****************************/
void Bullet::init(int x, int y, Dir dir, int state)
{
	b_x = x;
	b_y = y;
	b_dir = dir;
	b_state = state;
	Map::MoveLocation[b_x][b_y] = 3;
	Map::MoveLocation[b_x + 1][b_y] = 3;
	flag = 1;
}
/*********************************
�ӵ����ݷ���ʱ�ķ����ƶ�
���ӵ�û��ʧʱ���ӵ�һֱ�ڷɣ��������ӵ����ٶȷɵıȽϿ�
*********************************/
void Bullet::Move()
{
	//while (1) {
	gotoxy(b_x, b_y);
	//����о���о�ʱͷ�������bug
	if (flag == 0) {
		cout << "  ";
		//ԭ��̬�������Թ�0����ʾ�ǿյ���
		Map::MoveLocation[b_x][b_y] = 0;
		Map::MoveLocation[b_x + 1][b_y] = 0;
	}
	if (flag == 1) {
		Map::MoveLocation[b_x][b_y] = 0;
		Map::MoveLocation[b_x + 1][b_y] = 0;
		cout << "�~";
		flag = 0;
	}
	//
	if (b_dir == Dir::UP)
		b_y--;
	if (b_dir == Dir::DOWN)
		b_y++;
	if (b_dir == Dir::LEFT)
		b_x -= 2;
	if (b_dir == Dir::RIGHT)
		b_x += 2;
	//}
}
void Bullet::Display()
{
	//if (!Disappear()) {
	gotoxy(b_x, b_y);
	Map::MoveLocation[b_x][b_y] = 3;
	Map::MoveLocation[b_x + 1][b_y] = 3;
	cout << "��";
	//}
}
bool Bullet::BulletCrash()
{
	if (Map::MoveLocation[b_x][b_y] == 3)
	{
		Map::MoveLocation[b_x][b_y] = 0;
		b_state = -1;
		return true;
	}
	return false;
}
void Bullet::setState(int re_state)
{
	b_state = re_state;
	gotoxy(b_x, b_y);
	cout << "  ";
}
/****************************************
����ӵ��Ƿ��ײ��ǽ�ڻ���̹��
��ײ���
����ֵΪ 1 ʱ���ӵ�ײ�϶�������Ҫ��ʧ,ͬʱ��ײ�ϵ�������Ҫ������Ӧ�ķ�Ӧ
******************************************/

bool Bullet::Disappear()
{
	//�ӵ����ӵ�
	//if (Map::MoveLocation[b_x][b_y] == -1)
	//{
	//	b_state = -1;
	//	return true;
	//}
	/*if (Map::MoveLocation[b_x][b_y] == 3)
	{
		Map::MoveLocation[b_x][b_y] = 0;
		b_state = -1;
		return true;
	}*/
	//�ҷ��ӵ�(0)�򵽵з�̹��(2)
	if (Map::MoveLocation[b_x][b_y] == 2 && b_state == 0)
	{
		b_state = -1;
		Map::MoveLocation[b_x][b_y] = -1;
		return true;
		//̹�˼�⵽���ӵ�����,���ñ�ը��ClearBody����;
	}
	//�з��ӵ���1�����ҷ�̹��(1)
	if (Map::MoveLocation[b_x][b_y] == 1 && b_state == 1)
	{
		b_state = -1;
		Map::MoveLocation[b_x][b_y] = -1;
		return true;
		//̹�˼�⵽���ӵ�����,���ñ�ը��ClearBody����;
	}
	//�з��ӵ�(1)��з�̹�ˣ�1��
	if (Map::MoveLocation[b_x][b_y] == 2 && b_state == 1)
	{
		b_state = -1;
		return true;
	}
	vector<BrickLocation>::iterator pv;
	for (pv = Map::BrickList.begin(); pv != Map::BrickList.end();) {
		//��ײ���˲��ɴݻٵ�ש��
		if ((*pv).x == b_x && (*pv).y == b_y && (*pv).UnAttacked)
		{
			b_state = -1;
			return true;
		}
		//שҲҪ��ʧ,��ש��VECTOR������һ��Ԫ��
		if ((*pv).x == b_x && (*pv).y == b_y && !(*pv).UnAttacked)
		{
			if ((b_x == 40 && b_y == 36) || (b_x == 40 && b_y == 37))
				Map::MoveLocation[b_x][b_y] = -1;
			b_state = -1;
			gotoxy(b_x, b_y);
			cout << "  ";
			pv = Map::BrickList.erase(pv);
			return true;
		}
		++pv;
	}
	return false;
}
void Bullet::gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
