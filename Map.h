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
	//��ÿ��שͷ���õ�vector��
	//void setBrick();
	void gotoxy(int x, int y);
	//��������ǽ������
	static vector<BrickLocation>BrickList;
	//��̬�������ö�ά����������Ÿ�ֻ̹�˺��ӵ��ƶ�ʱʵʱ������;
	//��������Ԫ��Ϊ1�����ʾ��̹�˵����꣬����2�������ӵ�������Ϊ0;
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
