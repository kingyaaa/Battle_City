#pragma once
#include"Tank.h"
#include"Map.h"
#include"Bullet.h"
#include<iostream>
#include<Windows.h>
#include<cmath>
#include<list>
using namespace std;
class Game {
private:
	int score;
	int times;
	int num;
	int intervalTime;
	int leftTank;
	int sum;
	int mainHP;
	int result;
	Map map;
public:
	Game();
	void hide();//Òþ²Ø¹â±ê
	void BulletDetect();
	void GameStart();
	void CreateEnemy(vector<EnemyTank*>& enemyTanks);
	void EnemyDetect(vector<EnemyTank*>& enemyTanks);
	void GameOver();
	~Game() { }
};