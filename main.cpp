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
	//���Ƶ�ͼ
	Map map;
	map.DrawBrick();
	//�о���̹�˼���
	vector<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	for (int i = 0; i <= 2; i++) {
		enemyTanks.push_back(new EnemyTank(i + 1));
	}
	int count = 0;
	int num = 0, enemyIP = 0, intervalTime = 0,leftTank = 0;
	//�ȳ�������ֻ
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
		//��ⳡ��ʣ��̹������,������̹�˵�ʱ������3��
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
		//������ս̹������
		mainTank.DrawTankBody();
		//ͨ�������ʵʱ����̹�˵��ƶ�
		if (_kbhit()) {
			mainTank.Display();
		}
		//�о�̹���ƶ�,��������̹�˺�װ�׳����ٶȲ�ͬ������̹�˵�ʱ������ͬ��
		//����ֵ��ͬ����̹�˻��е��˺�ĵ÷ֲ�ͬ
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
		{
			//ÿ160ms��һ������̹��(�������̹��)
			if (times % 7 == 0 && (*it)->getID() % 2 == 1) {
				(*it)->DrawTankBody();
				(*it)->Display(right1, down1, changeDir1);
				//right1 = 0; down1 = 1; changeDir1 = 0;
			}
			//ÿ80ms��һ��װ�׳���ż�����̹�ˣ�
			if (times % 4 == 0 && (*it)->getID() % 2 == 0) {
				(*it)->DrawTankBody();
				(*it)->Display(right2, down2, changeDir2);
			}
			++it;
		}	
		//ÿ10ms��һ���ӵ��ļ���
		//�ӵ���ʧ����vector��ɾ�����Ԫ��;
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
		//ʵʱ����Ƿ���̹�˱�ը
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
		//�ж���ս̹���Ƿ�ը������ǣ�������̹��λ�ã�����ֵ��1;
		if (mainTank.WillKnockBullet()) {
			mainHP--;
			if (mainHP >= 0) {
				mainTank.ClearTankBody();
				mainTank.Reset();
			}
			//���û������ֵ�ˣ�������Ϸ�����㲥
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