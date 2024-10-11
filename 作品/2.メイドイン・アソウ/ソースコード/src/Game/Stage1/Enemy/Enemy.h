#pragma once
#include "../Player/Player.h"

//敵の数
const int ENEMY_NUM = 2;

class CEnemy
{
	int EnemyX[ENEMY_NUM] = { 0 }, EnemyY[ENEMY_NUM] = { 0 };//座標
	int EnemyGraph[ENEMY_NUM] = { 0 };     //画像
	float time;							 //インターバル
	bool life[ENEMY_NUM] = { 0 };
public:
	void Init();				//初期化
	void Load();				//ロード
	void Step(CPlayer& cPlayer);//ステップ
	void Draw();				//描画
	void Exit();				//破棄

};






