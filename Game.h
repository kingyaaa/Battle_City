#pragma once
#include"Tank.h"
#include"Map.h"
#include"Bullet.h"
#include<iostream>
#include<Windows.h>
#include<cmath>
#include<list>
using namespace std;
void hide();//���ع��
void BulletDetect();
void GameStart();
void CreateEnemy(vector<EnemyTank*>& enemyTanks);
void EnemyDetect(vector<EnemyTank*>& enemyTanks);
void Destory();
void GameOver();