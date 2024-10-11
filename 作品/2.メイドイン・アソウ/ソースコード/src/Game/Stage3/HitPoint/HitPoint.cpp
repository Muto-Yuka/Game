#include "HitPoint.h"
#include <DxLib.h>

const char EYE_PATH[] = { "data/Game/Stage3/Hitpoint.png" };

CHitPoint::CHitPoint()
{
	Init();
}
CHitPoint::~CHitPoint()
{
	Exit();
}
//初期化
void CHitPoint::Init()
{
	// キャラクターの初期データをセット
	EyeX = 1050;
	EyeY = 900;
}
//ロード
void CHitPoint::Load()
{
	// グラフィックのロード
	EyeGraph = LoadGraph("Data/Hitpoint.png");
}
//ステップ
void CHitPoint::Step()
{

}
void CHitPoint::Hit()
{

}
//描画
void CHitPoint::Draw()
{

}
//破棄
void CHitPoint::Exit()
{
	DeleteGraph(EyeGraph);

}
