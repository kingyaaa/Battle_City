#pragma once
#include"Map.h"
#include"Bullet.h"
//enum Dir { UP, DOWN, LEFT, RIGHT };
#define random(a,b) (rand() % (b - a + 1)) + a //横坐标： 4 到 76
#include<ctime>
#include<Windows.h>
#include<iostream>
#include<conio.h>
using namespace std;
class Tank
{
public:
	Tank()
	{
		m_x1 = 0;
		m_x2 = 0;
		m_y = 0;
	}
	void color(int x);
	//获取四个顶点的位置信息
	int getVertexOne_x();
	int getVertexOne_y();
	int getVertexTwo_x();
	int getVertexTwo_y();
	int getVertexThree_x();
	int getVertexThree_y();
	int getVertexFour_x();
	int getVertexFour_y();
	void Shoot(vector<Bullet*>& listBullet, int& x, int& y);
	virtual void DrawTankBody();
	virtual void ClearTankBody();
	void Boom();
	//void setState(int re_state) { state = re_state; }
	//virtual void Disappear();
	//在Move函数改变方向后就无限移动
	//virtual void Display() = 0;
	//改变方向
	//virtual void Move(int& right, int& down, Dir dir) = 0;
	//void setBrickLocation(vector<BrickLocation>&brick);
	bool WillKnockWall();
	bool WillKnockBullet();
	void gotoxy(int x, int y);
	~Tank() {}
protected:
	//可以画出一个矩阵
	int m_x1;
	int m_x2;
	int m_y;
	Dir m_dir;
	Bullet bullet;
	int state;//该状态记录坦克是否发射了子弹
	//vector<BrickLocation>MonitorBrick;
};
class MainTank :public Tank
{
public:
	MainTank() :Tank()
	{
		//▇
		//设置初始移动点
		m_x1 = 30;
		m_x2 = 31;
		m_y = 36;
		m_dir = Dir::UP;
		state = 1;
	}
	~MainTank() {}
	void Display();
	void DrawTankBody();
	void Shoot(vector<Bullet*>& listBullet, int& x, int& y);
	void Move(int& right, int& down, Dir dir);
	void Reset();
};
class EnemyTank :public Tank
{
public:
	EnemyTank(int my_ip) :Tank()
	{
		ip = my_ip;
	}
	~EnemyTank() {}
	void Display();
	void initLocation(int x) {
		srand((int)time(0));
		limStep = random(12, 15);
		//if (m_x1 % 2 == 1)
		m_x1 = x;
		m_x2 = m_x1 + 1;
		m_y = 2;
		m_dir = Dir::DOWN;
		state = 1;
		right = 0;
		down = 1;
		changeDir = 0;
	}
	int getCenterX() const { return m_x1; }
	int getCenterY() const { return m_y; }
	void DrawTankBody();
	void Shoot(vector<Bullet*>& listBullet, int& x, int& y);
	void Move(Dir dir);
	int getID() const { return ip; }
	//bool WillKnockBullet();
private:
	int cur_dir;
	//限定10步换一个方向
	int limStep;
	int changeDir;
	int ip;
	int right;
	int down;
};
