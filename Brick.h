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
	//��ÿ��שͷ���õ�vector��
	void setBrick();
	void gotoxy(int x, int y);
	//��������ǽ������
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