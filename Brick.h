#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>
using namespace std;
struct BrickLocation
{
	int x;
	int y;
	bool UnAttacked;
};
class Brick
{
public:
	Brick(){ }
	//friend class Tank;
	void DrawBrick();
	//将每个砖头放置到vector中
	void setBrick();
	void gotoxy(int x, int y);
	//放置所有墙的坐标
	vector<BrickLocation>BrickList;
};
/*
class IronBrick :public Brick
{
public:
	IronBrick():Brick(){ }
	void DrawBrick();
	void setBrick();
};*/
/*class Point
{
public:
	Point();
private:
	int x;
	int y;
};*/