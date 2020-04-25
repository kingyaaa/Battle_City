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
	//���Ƶ�ͼ
	Map map;
	map.DrawBrick();
	//�о���̹�˼���
	vector<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	for (int i = 0; i <= 1; i++) {
		enemyTanks.push_back(new EnemyTank(i + 1));
	}
	int count = 0;
	int num = 0, enemyIP = 0, intervalTime = 1,leftTank = 0;
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
	int mainHP = 200, score = 0;
	int times = 0;
	while (1) {
		//��ⳡ��ʣ��̹������,������̹�˵�ʱ������3��
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
		//������ս̹������
		mainTank.DrawTankBody();
		//ͨ�������ʵʱ����̹�˵��ƶ�
		if (_kbhit()) {
			mainTank.Display();
		}
		//ÿ5ms��һ���ӵ��ļ���
		//�ӵ���ʧ����vector��ɾ�����Ԫ��;
		int flag = 0;
		for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end();)
		{
			(*it)->Move();
			//����Ƿ����ӵ�Ҫ����ײ
			for (vector<Bullet*>::iterator pv = it + 1; pv != Bullet::listBullet.end(); ) {
				//�ӵ����ӵ��Ƿ������,������;
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
		//ʵʱ����Ƿ����ӵ���ը
		/*for (vector<Bullet*>::iterator it = Bullet::listBullet.begin(); it != Bullet::listBullet.end();)
		{
			if ((*it)->Disappear()) {
				it = Bullet::listBullet.erase(it);
				continue;
			}
			++it;
		}*/
		//�о�̹���ƶ�,��������̹�˺�װ�׳����ٶȲ�ͬ������̹�˵�ʱ������ͬ��
		//����ֵ��ͬ����̹�˻��е��˺�ĵ÷ֲ�ͬ
		for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
		{
			//ÿ80ms��һ������̹��(�������̹��)
			if (times % 16 == 0 && (*it)->getID() % 2 == 1) {
				(*it)->DrawTankBody();
				(*it)->Display();
			}
			//ÿ50ms��һ��װ�׳���ż�����̹�ˣ�
			if (times % 10 == 0 && (*it)->getID() % 2 == 0) {
				(*it)->DrawTankBody();
				(*it)->Display();
			}
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
		Sleep(5);
		times++;
		intervalTime++;
	}
	return;
}
