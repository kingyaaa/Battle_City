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
	//绘制地图
	Map map;
	map.DrawBrick();
	//敌军的坦克集合
	vector<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	for (int i = 0; i <= 2; i++) {
		enemyTanks.push_back(new EnemyTank(i + 1));
	}
	int count = 0;
	int num = 0, enemyIP = 0, intervalTime = 0,leftTank = 0;
	//先出动了两只
	for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end(); ++it)
	{
		if (count % 2 == 0) {
			(*it)->initLocation(4);
			num++;
			leftTank++;
		}
		if (count % 2 == 1) {
			(*it)->initLocation(76);
			num++;
			leftTank++;
		}
		count++;
	}
	MainTank mainTank;
	int mainHP = 2, score = 0;
	//ToDo
	int right1 = 0, down1 = 1, changeDir1 = 0;
	int right2 = 0, down2 = 1, changeDir2 = 0;
	int times = 0;
	while (1) {
		//检测场上剩余坦克数量,产生新坦克的时间间隔是3秒
		/*if (leftTank < 4 && intervalTime % 150 == 0){
			enemyTanks.push_back(new EnemyTank(num + 1));
			num++;
			leftTank++;
			vector<EnemyTank*>::iterator pv = enemyTanks.end() - 1;
			if (num % 2 == 1)
				(*pv)->initLocation(4);
			else
				(*pv)->initLocation(76);
		}*/
		//绘制主战坦克身体
		mainTank.DrawTankBody();
		//通过方向键实时控制坦克的移动
		if (_kbhit()) {
			mainTank.Display();
		}
		//敌军坦克移动,根据重型坦克和装甲车的速度不同，调用坦克的时间间隔不同，
		//生命值不同，则坦克击毙敌人后的得分不同
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
		{
			//每160ms跑一次重型坦克(奇数序号坦克)
			if (times % 7 == 0 && (*it)->getID() % 2 == 1) {
				(*it)->DrawTankBody();
				(*it)->Display(right1, down1, changeDir1);
				//right1 = 0; down1 = 1; changeDir1 = 0;
			}
			//每80ms跑一次装甲车（偶数序号坦克）
			if (times % 4 == 0 && (*it)->getID() % 2 == 0) {
				(*it)->DrawTankBody();
				(*it)->Display(right2, down2, changeDir2);
			}
			++it;
		}	
		//每10ms跑一遍子弹的集合
		//子弹消失，在vector中删除这个元素;
		for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end();)
		{
			(*it)->Move();
			if ((*it)->Disappear()) {
				it = Bullet::listBullet.erase(it);
				continue;
			}
			(*it)->Display();
			++it;
		}
		//实时检测是否有坦克被炸
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();) {
			if ((*it)->WillKnockBullet()) {
				(*it)->ClearTankBody();
				it = enemyTanks.erase(it);
				leftTank--;
				intervalTime = 0;
				continue;
			}
			++it;
		}
		//判断主战坦克是否被炸，如果是，则重置坦克位置，生命值减1;
		if (mainTank.WillKnockBullet()) {
			mainHP--;
			if (mainHP >= 0) {
				mainTank.ClearTankBody();
				mainTank.Reset();
			}
			//如果没有生命值了，发出游戏结束广播
			if (mainHP < 0)
				break;
		}
		//}
			/**********************
			while (pv != cour.myCourse.end()) {
			if ((*pv).couID == dropIDorName)
				pv = cour.myCourse.erase(pv);
			else
				++pv;
		}
			***********************/
		Sleep(15);
		times++;
		intervalTime++;
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