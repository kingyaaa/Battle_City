#include "Bullet.h"
vector<Bullet*>Bullet::listBullet;
//int Bullet::BulletCrash = 0;
/***************************
构造函数
参数值：坦克枪口的坐标
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
子弹根据发射时的方向移动
当子弹没消失时，子弹一直在飞，考虑让子弹的速度飞的比较快
*********************************/
void Bullet::Move()
{
	//while (1) {
	gotoxy(b_x, b_y);
	//解决敌军打敌军时头被打掉的bug
	if (flag == 0) {
		cout << "  ";
		//原动态坐标属性归0，表示是空地了
		Map::MoveLocation[b_x][b_y] = 0;
		Map::MoveLocation[b_x + 1][b_y] = 0;
	}
	if (flag == 1) {
		Map::MoveLocation[b_x][b_y] = 0;
		Map::MoveLocation[b_x + 1][b_y] = 0;
		cout << "▇";
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
	cout << "●";
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
检测子弹是否会撞上墙壁或者坦克
碰撞检测
返回值为 1 时：子弹撞上东西，需要消失,同时被撞上的物体需要做出相应的反应
******************************************/

bool Bullet::Disappear()
{
	//子弹打到子弹
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
	//我方子弹(0)打到敌方坦克(2)
	if (Map::MoveLocation[b_x][b_y] == 2 && b_state == 0)
	{
		b_state = -1;
		Map::MoveLocation[b_x][b_y] = -1;
		return true;
		//坦克检测到被子弹打中,调用爆炸和ClearBody函数;
	}
	//敌方子弹（1）打到我方坦克(1)
	if (Map::MoveLocation[b_x][b_y] == 1 && b_state == 1)
	{
		b_state = -1;
		Map::MoveLocation[b_x][b_y] = -1;
		return true;
		//坦克检测到被子弹打中,调用爆炸和ClearBody函数;
	}
	//敌方子弹(1)打敌方坦克（1）
	if (Map::MoveLocation[b_x][b_y] == 2 && b_state == 1)
	{
		b_state = -1;
		return true;
	}
	vector<BrickLocation>::iterator pv;
	for (pv = Map::BrickList.begin(); pv != Map::BrickList.end();) {
		//若撞上了不可摧毁的砖瓦
		if ((*pv).x == b_x && (*pv).y == b_y && (*pv).UnAttacked)
		{
			b_state = -1;
			return true;
		}
		//砖也要消失,从砖的VECTOR中消除一个元素
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
