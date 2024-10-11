#include "Player4.h"
#include <Dxlib.h>

const char BG_PATH1[] = { "data/Game/Stage4/pop1.png" };
const char BG_PATH2[] = { "data/Game/Stage4/pop2.png" };
const char BG_PATH3[] = { "data/Game/Stage4/pop3.png" };
const char BG_PATH4[] = { "data/Game/Stage4/pop4.png" };

CPlayer4::CPlayer4()
{
	Init();
}

CPlayer4::~CPlayer4()
{
	Exit();
}
//初期化
void CPlayer4::Init()
{
	// キャラクターの初期データをセット
	PlayerX = 0;
	PlayerY = 0;
	fast = true;
	second = false;
	third = false;
	forth = false;
	turn = false;
	num = one;
	times = 0;

	SetFontSize(130);
}
void CPlayer4::Load()//ロード
{
	// グラフィックのロード
	PlayerGraph = LoadGraph(BG_PATH1);

}
void CPlayer4::Step()//ステップ
{
	switch (num) {
	case one:
		if (fast == true)
		{
			if (CheckHitKey(KEY_INPUT_D) == 1)
			{
				second = true;
				fast = false;
			}
		}
		num = two;
		break;
	case two:
		if (second == true)
		{
			if (CheckHitKey(KEY_INPUT_S) == 1)
			{
				third = true;
				second = false;
			}
		}
		num = three;
		break;
	case three:
		if (third == true)
		{
			if (CheckHitKey(KEY_INPUT_A) == 1)
			{
				forth = true;
				third = false;
			}
		}
		num = four;
		break;
	case four:
		if (forth == true)
		{
			if (CheckHitKey(KEY_INPUT_W) == 1)
			{
				fast = true;
				forth = false;
				turn = true;
			}
		}
		num = one;
		break;
	}

	if (turn == true)
	{
		times = times + 1;
		turn = false;
	}
}
void CPlayer4::Update()
{
	if (fast == true)
	{
		PlayerGraph = LoadGraph(BG_PATH1);
	}
	if (second == true)
	{
		PlayerGraph = LoadGraph(BG_PATH2);
	}
	if (third == true)
	{
		PlayerGraph = LoadGraph(BG_PATH3);
	}
	if (forth == true)
	{
		PlayerGraph = LoadGraph(BG_PATH4);
	}
}
void CPlayer4::Draw()//描画
{
	// プレイヤーを描画する
	DrawGraph(PlayerX, PlayerY, PlayerGraph, true);
	DrawFormatString(0, 0, 0, "回数%d", times);
	if (fast == true)
	{
		PlayerGraph = LoadGraph(BG_PATH1);
		DrawFormatString(500, 400, (255, 0, 255), "D");
	}
	if (second == true)
	{
		PlayerGraph = LoadGraph(BG_PATH2);
		DrawFormatString(500, 400, (255, 0, 255), "S");
	}
	if (third == true)
	{
		PlayerGraph = LoadGraph(BG_PATH3);
		DrawFormatString(500, 400, (255, 0, 255), "A");
	}
	if (forth == true)
	{
		PlayerGraph = LoadGraph(BG_PATH4);
		DrawFormatString(500, 400, (255, 0, 255), "W");
	}
}
void CPlayer4::Exit()//破棄
{
	DeleteGraph(PlayerGraph);
}



