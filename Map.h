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
class Map
{
public:
	Map() { }
	void color(int x);
	void DrawBrick();
	//将每个砖头放置到vector中
	//void setBrick();
	void gotoxy(int x, int y);
	//放置所有墙的坐标
	static vector<BrickLocation>BrickList;
	//静态变量，该二维数组用来存放各只坦克和子弹移动时实时的坐标;
	//数组中若元素为1，则表示是坦克的坐标，若是2，则是子弹，否则为0;
	static int MoveLocation[80][40];
	~Map() { }
};
//static vector<BrickLocation>Map::BrickList;
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
