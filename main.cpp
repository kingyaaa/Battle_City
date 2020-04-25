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
	GameStart();
	return 0;
}
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void GameStart()
{
	hide();
	//绘制地图
	Map map;
	map.DrawBrick();
	//敌军的坦克集合
	vector<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	for (int i = 0; i <= 1; i++) {
		enemyTanks.push_back(new EnemyTank(i + 1));
	}
	int count = 0;
	int num = 0, enemyIP = 0, intervalTime = 1,leftTank = 0;
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
	int mainHP = 200, score = 0;
	int times = 0;
	while (1) {
		//检测场上剩余坦克数量,产生新坦克的时间间隔是3秒
		if (leftTank < 4 && intervalTime % 100 == 0) {
			enemyTanks.push_back(new EnemyTank(num + 1));
			num++;
			leftTank++;
			vector<EnemyTank*>::iterator pv = enemyTanks.end() - 1;
			if (num % 2 == 1)
				(*pv)->initLocation(4);
			else
				(*pv)->initLocation(76);
		}
		//绘制主战坦克身体
		mainTank.DrawTankBody();
		//通过方向键实时控制坦克的移动
		if (_kbhit()) {
			mainTank.Display();
		}
		//每5ms跑一遍子弹的集合
		//子弹消失，在vector中删除这个元素;
		int flag = 0;
		for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end();)
		{
			(*it)->Move();
			//检测是否有子弹要来相撞
			for (vector<Bullet*>::iterator pv = it + 1; pv != Bullet::listBullet.end(); ) {
				//子弹与子弹是否方向相对,且相邻;
				if ((*it)->getBullet_dir() == Dir::UP && (*pv)->getBullet_dir() == Dir::DOWN && (((*it)->getBullet_y() == (*pv)->getBullet_y() - 1 && (*pv)->getBullet_x() == (*it)->getBullet_x()) || ((*it)->getBullet_y() == (*pv)->getBullet_y() && (*pv)->getBullet_x() == (*it)->getBullet_x()))) 
				{	
					flag = 1;
					(*pv)->setState(-1);
					pv = Bullet::listBullet.erase(pv);
					break;
				}
				if ((*it)->getBullet_dir() == Dir::DOWN && (*pv)->getBullet_dir() == Dir::UP && (((*it)->getBullet_y() == (*pv)->getBullet_y() + 1 && (*pv)->getBullet_x() == (*it)->getBullet_x()) || ((*it)->getBullet_y() == (*pv)->getBullet_y() && (*pv)->getBullet_x() == (*it)->getBullet_x()))) 
				{
					flag = 1;
					(*pv)->setState(-1);
					pv = Bullet::listBullet.erase(pv);
					break;
				}
				if ((*it)->getBullet_dir() == Dir::RIGHT && (*pv)->getBullet_dir() == Dir::LEFT && (((*it)->getBullet_x() == (*pv)->getBullet_x() - 2 && (*it)->getBullet_y() == (*pv)->getBullet_y()) || ((*it)->getBullet_y() == (*pv)->getBullet_y() && (*pv)->getBullet_x() == (*it)->getBullet_x()))) 
				{
					flag = 1;
					//++pv;
					(*pv)->setState(-1);
					pv = Bullet::listBullet.erase(pv);
					break;
				}
				if ((*it)->getBullet_dir() == Dir::LEFT && (*pv)->getBullet_dir() == Dir::RIGHT && (((*it)->getBullet_x() == (*pv)->getBullet_x() + 2 && (*it)->getBullet_y() == (*pv)->getBullet_y()) || ((*it)->getBullet_y() == (*pv)->getBullet_y() && (*pv)->getBullet_x() == (*it)->getBullet_x()))) 
				{
					flag = 1;
					//++pv;
					(*pv)->setState(-1);
					pv = Bullet::listBullet.erase(pv);
					break;
				}
				++pv;
			}
			if (flag) {
				(*it)->setState(-1);
				it = Bullet::listBullet.erase(it);
				flag = 0;
				continue;
			}
			if ((*it)->Disappear()) {
				it = Bullet::listBullet.erase(it);
				continue;
			}
			(*it)->Display();
			++it;
		}
		//实时检测是否有子弹爆炸
		/*for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end();)
		{
			if ((*it)->Disappear()) {
				it = Bullet::listBullet.erase(it);
				continue;
			}
			++it;
		}*/
		//敌军坦克移动,根据重型坦克和装甲车的速度不同，调用坦克的时间间隔不同，
		//生命值不同，则坦克击毙敌人后的得分不同
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
		{
			//每80ms跑一次重型坦克(奇数序号坦克)
			if (times % 16 == 0 && (*it)->getID() % 2 == 1) {
				(*it)->DrawTankBody();
				(*it)->Display();
			}
			//每50ms跑一次装甲车（偶数序号坦克）
			if (times % 10 == 0 && (*it)->getID() % 2 == 0) {
				(*it)->DrawTankBody();
				(*it)->Display();
			}
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
		Sleep(5);
		times++;
		intervalTime++;
	}
	return;
}
