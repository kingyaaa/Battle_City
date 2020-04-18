#include"Tank.h"
#include"Map.h"
#include"Bullet.h"
#include<iostream>
#include<Windows.h>
#include<cmath>
#include<list>
using namespace std;
void hide();//隐藏光标
void GameStart();
int main()
{
	getchar();
	hide();
	GameStart();
}
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void GameStart()
{
	Map map;
	map.DrawBrick();
	list<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	//Bullet::listBullet;
	for (int i = 0; i <= 1; i++) {
		enemyTanks.push_back(new EnemyTank());
	}
	int count = 0;
	for (list<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end(); ++it)
	{
		if (count % 2 == 0) {
			(*it)->initLocation(4);
		}
		if (count % 2 == 1) {
			(*it)->initLocation(76);
		}
		count++;
	}
	MainTank mainTank;
	//ToDo
	int right1 = 0, down1 = 1, changeDir1 = 0;
	int right2 = 0, down2 = 1, changeDir2 = 0;
	int times = 0;
	while (1) {
		mainTank.DrawTankBody();
		if (_kbhit()) {

			mainTank.Display();
		}
		/*int i = 0;
		for (list<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end(); ++it)
		{
			//每160ms跑一次重型坦克
			if (times % 8 == 0 && i % 2 == 0) {
				(*it)->DrawTankBody();
				(*it)->Display(right1, down1, changeDir1);
			}
			//每80ms跑一次装甲车
			if (times % 4 == 0 && i % 2 == 1) {
				(*it)->DrawTankBody();
				(*it)->Display(right2, down2, changeDir2);
			}
			i++;*/
			//每10ms跑一遍子弹的集合
		for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end(); ++it)
		{
			(*it)->Move();
			(*it)->Display();
		}
	//  }
		Sleep(20);
		times++;
	}
}
/*************************
随机刷出坦克
	/*for (int i = 0; i < 3; ++i) {
		//enemy[i].randomLocation();
		//将随机产生的矩阵与现有的各矩阵数据进行位置检测
		int j = 0;
		while(j < i){
			if (pow(enemy[i].getCenterX() - enemy[j].getCenterX(), 2) + pow(enemy[i].getCenterY() - enemy[j].getCenterY(), 2) <= 9)
			{
				j = 0;
				enemy[i].initLocation();
			}
			else
				j++;
		}
		enemy[i].DrawTankBody();
		//enemy[i].Display();
	}
******************************/