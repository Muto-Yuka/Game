#include "Drop.h"
#include <DxLib.h>
#include "../../../MyLib/Collision/Collision.h"

const char WATER_PATH[] = { "data/Game/Stage3/Drop.png" };

CDrop::CDrop()
{
	Init();
}
CDrop::~CDrop()
{
	Exit();
}
//初期化
void CDrop::Init()
{
	life = false;
	DropY = 400;
	DropX = 0;
	time = 5.0f;
}
//ロード
void CDrop::Load()
{
	// グラフィックのロード
	DropGraph = LoadGraph(WATER_PATH);
}
//ステップ
void CDrop::Step(CPlayer3 &cPlayer)
{
	bool now = cPlayer.GetOffer();

	if (now)
	{
		life = true;
		for (int i = 0; i < 1; i++)
		{
			DropX = cPlayer.GetHandX() + 70;
		}
		now = false;
	}
	if (life == true)
	{
		time = time - 1.0f;
		if (time == 0.0f)
		{
			DropY += cPlayer.GetHandY() + 20;
			time = 5.0f;
		}
	}
}
//１：クリア　２：ゲームオーバー
int CDrop::Hit(CHitPoint& cHitPoint)
{
	//水とヒットポイントの当たり安定
	if (CCollision::IsHitRect(DropX, DropY, 90, 90, cHitPoint.HitX(), cHitPoint.HitY(), 125, 150) == true)
	{
		return 1;
	}
	else if (DropY == 1080)
		return 2;

	return 0;
}
//描画
void CDrop::Draw()
{
	// プレイヤーを描画する
	if (life == true)
	{
		DrawGraph(DropX, DropY, DropGraph, true);
	}
}
//破棄
void CDrop::Exit()
{
	DeleteGraph(DropGraph);
}






