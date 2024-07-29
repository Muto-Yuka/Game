#include "BackGround3.h"
#include <DxLib.h>

const char BG_PATH[] = { "data/Game/Stage3/bg.png" };

CBackGround3::CBackGround3()
{
	Init();
}
CBackGround3::~CBackGround3()
{
	Exit();
}

//初期化
void CBackGround3::Init()		
{
	bgSkyHandle = -1;
}
//ロード
void CBackGround3::Load()		
{
	bgSkyHandle = LoadGraph(BG_PATH);
}
//ステップ
void CBackGround3::Step()		
{

}
//描画
void CBackGround3::Draw()		
{
	DrawGraph(0, 0, bgSkyHandle, true);
}
//破棄
void CBackGround3::Exit()		
{
	DeleteGraph(bgSkyHandle);
}
void CBackGround3::Hit()
{

}