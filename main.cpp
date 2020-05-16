#include"Game.h"
#include<iostream>
using namespace std;
int main()
{
	//while (1) {
	cout << "为了有正常的游戏体验，请将屏幕扩展至全屏，按回车键即可开始游戏"<<endl;
	system("pause");
	Game game;
	game.GameStart();
	game.GameOver();
	return 0;
}