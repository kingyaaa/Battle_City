#pragma once
#include"Map.h"
#include<Windows.h>
#include<iostream>
#include<ctime>
using namespace std;
enum Dir { UP, DOWN, LEFT, RIGHT };
class Bullet
{
private:
	//记录坐标,移动的方向
	int b_x, b_y;
	int flag;
	Dir b_dir;
	int b_state;//-1表示消失,0是我方子弹，1是你方子弹
public:
	Bullet() {}
	void init(int x, int y, Dir dir, int state);
	void Move();
	int getState() const { return b_state; }
	void Display();
	int getBullet_x() const { return b_x; }
	int getBullet_y() const { return b_y; }
	Dir getBullet_dir() const { return b_dir; }
	bool Disappear();
	void gotoxy(int x, int y);
	bool BulletCrash();
	void setState(int re_state);
	static vector<Bullet*>listBullet;
	~Bullet() { }
};