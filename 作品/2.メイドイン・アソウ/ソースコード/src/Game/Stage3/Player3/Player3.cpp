#include "Player3.h"
#include <DxLib.h>

//動く手
const char HAND_PATH[] = { "data/Game/Stage3/Image.png" };
//プレイヤー（目）
const char HEAD_PATH[] = { "data/Game/Stage3/haed.png" };
//左右に動く手の速さ
const int HAND_SPEED = 10;

CPlayer3::CPlayer3()
{
	Init();
}
CPlayer3::~CPlayer3()
{
	Exit();
}
//初期化
void CPlayer3::Init()
{
	//手
	HandX = 0;
	HandY = 0;
	right = true;
	left = false;
	offer = false;

	// キャラクターの初期データをセット
	HeadX = 0;
	HeadY = 400;

	SetFontSize(80);

}
//ロード
void CPlayer3::Load()
{
	HandGraph = LoadGraph(HAND_PATH);
	headGraph = LoadGraph(HEAD_PATH);
}
//ステップ
void CPlayer3::Step()
{
	//画面外にいかないようにする処理
	if (HandX < 0)
	{
		HandX = 0;
	}
	if (HandX > 1720)
	{
		HandX = 1720;
	}
	//右に移動
	if (right == true)//右フラグがオンなら
	{
		if (offer == false)
		{
			HandX += HAND_SPEED;//右に進む
			if (HandX == 1720)//画面端なら
			{
				right = false;//右フラグオフ
				left = true;//左フラグオン
			}
		}
	}
	//左に移動
	if (left == true)//左フラグがオンなら
	{
		if (offer == false)
		{
			HandX -= HAND_SPEED;//左に進む
			if (HandX == 0)//画面端なら
			{
				left = false;//左フラグオフ
				right = true;//右フラグオン
			}
		}
	}
	//手をストップ
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		offer = true;
	}
}
void CPlayer3::Hit()
{

}
//描画
void CPlayer3::Draw()
{
	// 手を描画する
	DrawGraph(HandX, HandY, HandGraph, true);
	// プレイヤー（目）
	DrawGraph(HeadX, HeadY, headGraph, true);

	DrawFormatString(0, 0, GetColor(175, 238, 238), "Spaceキーで目薬をさす");
}
//破棄
void CPlayer3::Exit()
{
	DeleteGraph(HandGraph);
	DeleteGraph(headGraph);
}




