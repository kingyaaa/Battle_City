#pragma once
#include"Map.h"
#include"Bullet.h"
//enum Dir { UP, DOWN, LEFT, RIGHT };
#define random(a,b) (rand() % (b - a + 1)) + a //�����꣺ 4 �� 76
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
	//��ȡ�ĸ������λ����Ϣ
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
	//virtual void Disappear();
	//��Move�����ı䷽���������ƶ�
	//virtual void Display() = 0;
	//�ı䷽��
	virtual void Move(int& right, int& down, Dir dir) = 0;
	//void setBrickLocation(vector<BrickLocation>&brick);
	bool WillKnockWall();
	void gotoxy(int x, int y);
protected:
	//���Ի���һ������
	int m_x1;
	int m_x2;
	int m_y;
	Dir m_dir;
	Bullet bullet;
	int state;//��״̬��¼̹���Ƿ������ӵ�
	//vector<BrickLocation>MonitorBrick;
};
class MainTank :public Tank
{
public:
	MainTank() :Tank()
	{
		//�~
		//���ó�ʼ�ƶ���
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
	//void Disappear();
};
class EnemyTank :public Tank
{
public:
	EnemyTank() :Tank()
	{ }
	~EnemyTank() {}
	void Display(int& right, int& down, int& changeDir);
	void initLocation(int x) {
		srand((int)time(0));
		limStep = random(12, 15);
		//if (m_x1 % 2 == 1)
		m_x1 = x;
		m_x2 = m_x1 + 1;
		m_y = 2;
		m_dir = Dir::DOWN;
		state = 1;
	}
	int getCenterX() const { return m_x1; }
	int getCenterY() const { return m_y; }
	void DrawTankBody();
	void Shoot(vector<Bullet*>& listBullet, int& x, int& y);
	void Move(int& right, int& down, Dir dir);
	//bool WillKnockTank();
	bool WillKnockBullet();
	//void Disappear();
private:
	int cur_dir;
	//�޶�10����һ������
	int limStep;
	int changeDir;
};