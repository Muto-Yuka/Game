#include "Flag.h"
#include <DxLib.h>
#include "../../../MyLib/Collision/Collision.h"

const char FLAG_PATH[] = { "data/Game/Stage1/flag2.png" };
//プレイヤーが到達したらフラグを出現
const int FLAG_X = 400;

//初期化
void CFlag::Init()
{
	FlagX = -100;
	FlagY = 270;
	life = false;
}
//ロード
void  CFlag::Load()
{
	FlagGraph = LoadGraph(FLAG_PATH);
}
//ステップ
void  CFlag::Step(CPlayer &cPlayer)
{
	if (cPlayer.GetPlayerX() < FLAG_X)
	{
		life = true;
	}
	if (life == true)
	{
		//プレイヤーが生きているとき
		if (cPlayer.GetLife() == true)
		{
			if (CheckHitKey(KEY_INPUT_A) == 1)
				FlagX = FlagX + 3;
			if (CheckHitKey(KEY_INPUT_D) == 1)
				FlagX = FlagX - 2;
		}
	}

	//プレイヤーとの当たり判定
	if (CCollision::IsHitRect(cPlayer.GetPlayerX(), cPlayer.GetPlayerY(),
		75, 75, FlagX, FlagY, 50, 208))
	{
		cPlayer.SetClear();
	}

}
//描画
void  CFlag::Draw()
{
	if (life == true)
	{
		DrawGraph(FlagX, FlagY, FlagGraph, TRUE);
	}
}
//破棄
void  CFlag::Exit()
{
	DeleteGraph(FlagGraph);
}
void  CFlag::Hit()
{

}




