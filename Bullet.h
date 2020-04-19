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
	int b_state;//-1表示消失
public:
	Bullet() {}
	void init(int x,int y,Dir dir,int state);
	void Move();
	int getState() const { return b_state; }
	void Display();
	bool Disappear();
	void gotoxy(int x, int y);
	static vector<Bullet*>listBullet;
};
//❤