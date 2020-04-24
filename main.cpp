#include"Tank.h"
#include"Map.h"
#include"Bullet.h"
#include<iostream>
#include<Windows.h>
#include<cmath>
#include<list>
using namespace std;
void hide();//���ع��
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
	vector<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	//Bullet::listBullet;
	for (int i = 0; i <= 1; i++) {
		enemyTanks.push_back(new EnemyTank());
	}
	int count = 0;
	for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end(); ++it)
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
		int i = 0;
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
		{
			//ÿ160ms��һ������̹��
			if (times % 7 == 0 && i % 2 == 0) {
				//if ((*it)->WillKnockBullet()) {
				//	(*it)->ClearTankBody();
					//it = enemyTanks.erase(it);
				//}
				//else {
				(*it)->DrawTankBody();
				(*it)->Display(right1, down1, changeDir1);
				//}
			}
			//ÿ80ms��һ��װ�׳�
			if (times % 4 == 0 && i % 2 == 1) {
				(*it)->DrawTankBody();
				(*it)->Display(right2, down2, changeDir2);
			}
			i++;
			++it;
		}	//ÿ10ms��һ���ӵ��ļ���
		//�ӵ���ʧ����vector��ɾ�����Ԫ��;
		for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end();)
		{
			(*it)->Move();
			if ((*it)->Disappear()) {
				//delete* it;
				it = Bullet::listBullet.erase(it);
				continue;
			}
			(*it)->Display();
			++it;
		}
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();) {
			if ((*it)->WillKnockBullet()) {
				(*it)->ClearTankBody();
				//delete* it;
				it = enemyTanks.erase(it);
				continue;
			}
			++it;
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
		Sleep(20);
		times++;
	}
}
/*************************
���ˢ��̹��
	/*for (int i = 0; i < 3; ++i) {
		//enemy[i].randomLocation();
		//����������ľ��������еĸ��������ݽ���λ�ü��
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