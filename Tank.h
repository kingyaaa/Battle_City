#pragma once
#include"Map.h"
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
	Tank() 
	{
		//head_x1 = 0;
		//head_x2 = 0;
		//head_y = 0;
		m_x1 = 0;
		m_x2 = 0;
		m_y = 0;
	}
	//��ȡ�ĸ������λ����Ϣ
	int getVertexOne_x();
	int getVertexOne_y();
	int getVertexTwo_x();
	int getVertexTwo_y();
	int getVertexThree_x();
	int getVertexThree_y();
	int getVertexFour_x();
	int getVertexFour_y();
	virtual void DrawTankBody();
	virtual void ClearTankBody();
	//��Move�����ı䷽���������ƶ�
	//virtual void Display() = 0;
	//�ı䷽��
	virtual void Move(int& right, int& down,Dir dir) = 0;
	//void setBrickLocation(vector<BrickLocation>&brick);
	bool WillKnockWall();
	void gotoxy(int x, int y);
protected:
	//���Ի���һ������
	//int UpLeft;
	//int DownRight;
	//int head_x1, head_x2, head_y;
	int m_x1;
	int m_x2;
	int m_y;
	Dir m_dir;
	//Point point;
	//�о�̹�˵��޶������ƶ�����
	int m_step;
	vector<BrickLocation>MonitorBrick;
};
class MainTank :public Tank
{
public:
	MainTank():Tank()
	{
		//�~
		//���ó�ʼ�ƶ���
		m_x1 = 30;
		m_x2 = 31;
		m_y = 36;
		m_dir = Dir::UP;
	}
	~MainTank() {}
	void Display();
	void Move(int& right, int& down,Dir dir);
};
class EnemyTank:public Tank
{
public:
	EnemyTank() :Tank()
	{ }
	~EnemyTank() {}
	void Display(int& right,int& down,int& changeDir);
	void initLocation(int x) {
		srand((int)time(0));
		limStep = random(12, 15);
		//if (m_x1 % 2 == 1)
		m_x1 = x;
		m_x2 = m_x1 + 1;
		m_y = 2;
		m_dir = Dir::DOWN;
		//limStep = 15;
	}
	int getCenterX() const { return m_x1; }
	int getCenterY() const { return m_y; }
	void Move(int& right, int& down,Dir dir);
	bool WillKnockTank();
private:
	int cur_dir;
	//�޶�10����һ������
	int limStep;
	int changeDir;
};