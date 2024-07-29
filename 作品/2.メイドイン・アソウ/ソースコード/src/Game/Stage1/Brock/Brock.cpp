#include "Brock.h"
#include <DxLib.h>
#include "../../../MyLib/Collision/Collision.h"

const char BROCK_PATH[] = { "data/Game/Stage1/Brock.png" };

CBrock::CBrock()
{
	Init();
}
CBrock::~CBrock()
{
	Exit();
}

//初期化
void CBrock::Init()		
{
	for (int i = 0; i < BROCK_NUM; i++)
	{
		BrockX[i] = (i * 2) * 128;
		BrockY[i] = 128;
	}
}
//ロード
void CBrock::Load()		
{
	for (int i = 0; i < BROCK_NUM; i++)
	{
		BrockGraph[i] = LoadGraph(BROCK_PATH);
	}
}
//ステップ
void CBrock::Step(CPlayer& cPlayer)
{
	//画面に合わせてブロックを移動
	for (int i = 0; i < BROCK_NUM; i++)
	{
		if (!cPlayer.GetLife())
			continue;

		if (BrockY[i] > 765 || BrockY[i] < 256)
		{
			BrockX[i] = GetRand(7) * -128;
			BrockY[i] = GetRand(7) * 128;
		}
		if (CheckHitKey(KEY_INPUT_D) == 1)
		{
			BrockX[i] -= 4;
			if (BrockX[i] < -128)
			{
				BrockX[i] = 1920;
				BrockY[i] = GetRand(6) * 128;
			}
		}
		if (CheckHitKey(KEY_INPUT_A) == 1)
		{
			BrockX[i] += 4;
			if (BrockX[i] > 1920)
			{
				BrockX[i] = GetRand(7) * -128;
				BrockY[i] = GetRand(6) * 128;
			}
		}
	}

	//プレイヤーとの当たり判定
	for (int i = 0; i < BROCK_NUM; i++)
	{
		if (CCollision::IsHitRect(cPlayer.GetPlayerX(), cPlayer.GetPlayerY(),
			75, 75, BrockX[i], BrockY[i], 128, 128))
		{
			cPlayer.SetJump(-3);
			cPlayer.SetPlayerHit(true);
		}
	}
}
//描画
void CBrock::Draw()		
{
	for (int i = 0; i < BROCK_NUM; i++)
	{
		if (BrockY[i] < 765 || BrockY[i] > 256)
		{
			DrawGraph(BrockX[i], BrockY[i], BrockGraph[i], true);
		}
	}
}
//破棄
void CBrock::Exit()		
{
	for (int i = 0; i < BROCK_NUM; i++)
	{
		DeleteGraph(BrockGraph[i]);
	}
}




