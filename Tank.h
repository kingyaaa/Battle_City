#pragma once
enum Dir { UP, DOWN, LEFT, RIGHT };
#define random(a,b) (rand() % (b - a + 1)) + a //�����꣺ 5 �� 76
#include<ctime>
#include<Windows.h>
#include<iostream>
#include<conio.h>
using namespace std;
/*class Point
{
public:
	Point(int x1,int x2,int y)
	void set_x1(int m_x1) { mLeft_x = m_x1; }
	void set_x2(int m_x2) { mRight_x = m_x2; }
	void set_y(int m_y) { mCenter_y = m_y; }
	int get_x1() const { return mLeft_x; }
	int get_x2() const { return mRight_x; }
	int get_y() const { return mCenter_y; }
private:
	//�������ǿ��ַ��Ĵ���
	int mLeft_x;
	int mRight_x;
	int mCenter_y;
};*/
class Tank
{
public:
	Tank() {}
	virtual void DrawTankBody();
	virtual void ClearTankBody();
	//��Move�����ı䷽���������ƶ�
	virtual void Display() = 0;
	//�ı䷽��
	virtual void Move(int& right, int& down) = 0;
	virtual bool WillKnockWall();
	void gotoxy(int x, int y);
protected:
	//���Ի���һ������
	//int UpLeft;
	//int DownRight;
	int head_x1, head_x2, head_y;
	int m_x1;
	int m_x2;
	int m_y;
	Dir m_dir;
	//Point point;
	//�о�̹�˵��޶������ƶ�����
	int m_step;
};
class MainTank :public Tank
{
public:
	MainTank():Tank()
	{
		//�~
		//���ó�ʼ�ƶ���
		m_x1 = 20;
		m_x2 = 21;
		m_y = 30;
		m_dir = Dir::UP;
	}
	~MainTank() {}
	void Display();
	void Move(int& right, int& down);
	bool WillKnockWall();
	//void DrawTankBody();
	//void ClearTankBody();
};
class EnemyTank:public Tank
{
public:
	EnemyTank() :Tank()
	{
		srand((int)time(0));
		m_x1 = random(5, 76);
		m_x2 = m_x1 + 1;
		m_y = 3;
		m_dir = Dir::DOWN;
	}
	~EnemyTank() {}
	void Display();
	void Move(int& right, int& down);
	bool WillKnockWall();
	//void DrawTankBody();
	//void ClearTankBody();
private:
	int cur_dir;
	//�޶�10����һ������
	int limStep;
};