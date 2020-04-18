#include "Bullet.h"
vector<Bullet*>Bullet::listBullet;
/***************************
构造函数
参数值：坦克枪口的坐标
*****************************/
void Bullet::init(int x,int y,Dir dir,int state)
{
	b_x = x;
	b_y = y;
	b_dir = dir;
	b_state = state;
}
/*********************************
子弹根据发射时的方向移动
当子弹没消失时，子弹一直在飞，考虑让子弹的速度飞的比较快
*********************************/
void Bullet::Move()
{
	//while (1) {
	gotoxy(b_x, b_y);
	cout << "  ";
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
	if (!Disappear()) {
		gotoxy(b_x, b_y);
		cout << "❤";
		gotoxy(0, 0);
	}
}
/****************************************
检测子弹是否会撞上墙壁或者坦克
碰撞检测
返回值为 1 时：子弹撞上东西，需要消失,同时被撞上的物体需要做出相应的反应
******************************************/
bool Bullet::Disappear()
{
	vector<BrickLocation>::iterator pv;
	for (pv = Map::BrickList.begin(); pv != Map::BrickList.end(); ++pv) {
		//若撞上了不可摧毁的砖瓦
		if ((*pv).x == b_x && (*pv).y == b_y && (*pv).UnAttacked)
		{
			//gotoxy(b_x, b_y);
			//cout << "▇";
			b_state = -1;
			return true;
		}
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
