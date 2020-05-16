#include"Game.h"
Game::Game()
{
	score = 0;
	times = 0;
	num = 0;
	intervalTime = 1;
	leftTank = 0;
	//sum��mainHP�ǱȽ������������ݣ����Ը���ϲ��ֱ���޸�
	//sum�����˵�����
	sum = 10;
	//mainHP:��ҵ�����ֵ
	mainHP = 500;
	result = 0;
}
void Game::hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//��Ϸ��������
void Game::GameOver()
{
	system("cls");
	map.color(4);
	map.gotoxy(40, 18);
	if (result == 1) {
		cout << "�����ѱ��ݻ�";
	}
	if (result == 2) {
		cout << "��������Ѻľ�";
	}
	if (result == 3) {
		cout << "VICTORY";
	}
	map.color(15);
	map.gotoxy(40, 20);
	cout << "SCORE: " << score;
	map.color(15);
	Sleep(2000);
	system("cls");
}
void Game::GameStart()
{
	system("cls");
	hide();
	//���Ƶ�ͼ
	map.DrawBrick();
	//�о���̹�˼���
	//int sum = 20, mainHP = 500;
	map.gotoxy(90, 15);
	cout << "1P:" << mainHP;
	map.gotoxy(90, 20);
	cout << "Enemy:" << sum;
	vector<EnemyTank*>enemyTanks;
	enemyTanks.clear();
	for (int i = 0; i <= 1; i++) {
		enemyTanks.push_back(new EnemyTank(i + 1));
	}
	int count = 0;
	//int num = 0, intervalTime = 1, leftTank = 0;
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
	while (1) {
		if (Map::MoveLocation[40][36] != 1 || Map::MoveLocation[40][37] != 1) {
			result = 1;
			break;
		}
		map.gotoxy(90, 15);
		cout << "         ";
		map.gotoxy(90, 15);
		cout << "1P:";
		cout << mainHP;
		map.gotoxy(90, 20);
		cout << "            ";
		map.gotoxy(90, 20);
		cout << "Enemy:";
		cout << sum;
		CreateEnemy(enemyTanks);
		//������ս̹������
		mainTank.DrawTankBody();
		//ͨ�������ʵʱ����̹�˵��ƶ�
		if (_kbhit()) {
			mainTank.Display();
		}
		//�ӵ�
		BulletDetect();
		//�о�
		EnemyDetect(enemyTanks);
		//�ж���ս̹���Ƿ�ը������ǣ�������̹��λ�ã�����ֵ��1;
		if (sum == 0)
		{
			result = 3;
			break;
		}
		if (mainTank.WillKnockBullet()) {
			mainHP -= 100;
			map.gotoxy(90, 15);
			cout << "         ";
			map.gotoxy(90, 15);
			cout << "1P:";
			cout << mainHP;
			if (mainHP >= 0) {
				mainTank.Boom();
				Sleep(30);
				mainTank.ClearTankBody();
				mainTank.Reset();
			}
			//���û������ֵ�ˣ�������Ϸ�����㲥
			if (mainHP < 0) {
				result = 2;
				break;
			}
		}
		Sleep(10);
		times++;
		intervalTime++;
	}
	for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end(); ++it)
	{
		delete* it;
		*it = NULL;
	}
	enemyTanks.clear();
	//Bullet::listBullet.clear();
}
//ÿ5ms��һ���ӵ��ļ���
void Game::BulletDetect()
{
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
}
void Game::EnemyDetect(vector<EnemyTank*>& enemyTanks)
{
	//�о�̹���ƶ�,��������̹�˺�װ�׳����ٶȲ�ͬ������̹�˵�ʱ������ͬ
	//����ֵ��ͬ����̹�˻��е��˺�ĵ÷ֲ�ͬ
	for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
	{
		//ÿ80ms��һ������̹��(�������̹��)
		if (times % 13== 0 && (*it)->getID() % 2 == 1) {
			(*it)->DrawTankBody();
			(*it)->Display();
		}
		//ÿ50ms��һ��װ�׳���ż�����̹�ˣ�
		if (times % 7 == 0 && (*it)->getID() % 2 == 0) {
			(*it)->DrawTankBody();
			(*it)->Display();
		}
		++it;
	}
	//ʵʱ����Ƿ���̹�˱�ը
	for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();) {
		if ((*it)->WillKnockBullet()) {
			if ((*it)->getID() % 2 == 1)
				score += 100;
			else
				score += 200;
			(*it)->Boom();
			Sleep(40);
			(*it)->ClearTankBody();
			it = enemyTanks.erase(it);
			leftTank--;
			sum--;
			map.gotoxy(90, 20);
			cout << "            ";
			map.gotoxy(90, 20);
			cout << "Enemy:" << sum;
			intervalTime = 0;
			continue;
		}
		++it;
	}
}
void Game::CreateEnemy(vector<EnemyTank*>& enemyTanks) {
	//��ⳡ��ʣ��̹������,������̹�˵�ʱ������3��
	if (leftTank < 4 && intervalTime % 100 == 0 && sum > leftTank) {
		enemyTanks.push_back(new EnemyTank(num + 1));
		num++;
		leftTank++;
		vector<EnemyTank*>::iterator pv = enemyTanks.end() - 1;
		if (num % 2 == 1)
			(*pv)->initLocation(4);
		else
			(*pv)->initLocation(76);
	}
}