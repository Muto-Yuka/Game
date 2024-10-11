#include "Enemy.h"
#include <DxLib.h>
#include "../../../MyLib/Collision/Collision.h"

const char ENEMY_PATH[] = { "data/Game/Stage1/TNT.png" };
//敵が右に進む速さ
const int ENEMY_SPEED = 3;

void CEnemy::Init()		//初期化
{
	//X座標
	for (int k = 0; k < ENEMY_NUM; k++)
	{
		EnemyX[k] += k * 300;
	}
	//Y座標
	for (int i = 0; i < ENEMY_NUM; i++)
		EnemyY[i] = 730;
	
	time = 10.0f;
}
//ロード
void CEnemy::Load()	
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// グラフィックのロード
		EnemyGraph[i] = LoadGraph(ENEMY_PATH);
	}
}
//ステップ
void CEnemy::Step(CPlayer &cPlayer)		
{
	//右に進む
	if (time == 0.0f)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			EnemyX[i] = EnemyX[i] + ENEMY_SPEED;
			time = 10.0f;

			if (!cPlayer.GetLife())
				continue;

			if (CheckHitKey(KEY_INPUT_A))
			{
				EnemyX[i] = EnemyX[i] + (ENEMY_SPEED );
				time = 10.0f;
			}
			if (CheckHitKey(KEY_INPUT_D))
			{
				EnemyX[i] = EnemyX[i] - (ENEMY_SPEED-1);
				time = 10.0f;
			}
		}
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		time = time - 5.0f;
	}
	if (time < 0.0f)
	{
		time = 0.0f;
	}
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (EnemyX[i] > 1900)
			EnemyX[i] = 0;
	}

	//プレイヤーと当たったら
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (CCollision::IsHitRect(cPlayer.GetPlayerX(), cPlayer.GetPlayerY(),
			75, 75, EnemyX[i], EnemyY[i], 128, 128))
		{
			cPlayer.Hit();
		}
	}
}
//描画
void CEnemy::Draw()		
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		DrawGraph(EnemyX[i], EnemyY[i], EnemyGraph[i], TRUE);
	}
}
//破棄
void CEnemy::Exit()		
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		DeleteGraph(EnemyGraph[i]);
	}
}
