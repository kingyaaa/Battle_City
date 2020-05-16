#include"Game.h"
Game::Game()
{
	score = 0;
	times = 0;
	num = 0;
	intervalTime = 1;
	leftTank = 0;
	//sum和mainHP是比较灵活的两个数据，可以根据喜好直接修改
	//sum：敌人的数量
	sum = 10;
	//mainHP:玩家的生命值
	mainHP = 500;
	result = 0;
}
void Game::hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//游戏控制流程
void Game::GameOver()
{
	system("cls");
	map.color(4);
	map.gotoxy(40, 18);
	if (result == 1) {
		cout << "基地已被摧毁";
	}
	if (result == 2) {
		cout << "玩家生命已耗尽";
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
	//绘制地图
	map.DrawBrick();
	//敌军的坦克集合
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
		//绘制主战坦克身体
		mainTank.DrawTankBody();
		//通过方向键实时控制坦克的移动
		if (_kbhit()) {
			mainTank.Display();
		}
		//子弹
		BulletDetect();
		//敌军
		EnemyDetect(enemyTanks);
		//判断主战坦克是否被炸，如果是，则重置坦克位置，生命值减1;
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
			//如果没有生命值了，发出游戏结束广播
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
//每5ms跑一遍子弹的集合
void Game::BulletDetect()
{
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
}
void Game::EnemyDetect(vector<EnemyTank*>& enemyTanks)
{
	//敌军坦克移动,根据重型坦克和装甲车的速度不同，调用坦克的时间间隔不同
	//生命值不同，则坦克击毙敌人后的得分不同
	for (vector<EnemyTank*>::iterator it = enemyTanks.begin(); it != enemyTanks.end();)
	{
		//每80ms跑一次重型坦克(奇数序号坦克)
		if (times % 13== 0 && (*it)->getID() % 2 == 1) {
			(*it)->DrawTankBody();
			(*it)->Display();
		}
		//每50ms跑一次装甲车（偶数序号坦克）
		if (times % 7 == 0 && (*it)->getID() % 2 == 0) {
			(*it)->DrawTankBody();
			(*it)->Display();
		}
		++it;
	}
	//实时检测是否有坦克被炸
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
	//检测场上剩余坦克数量,产生新坦克的时间间隔是3秒
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