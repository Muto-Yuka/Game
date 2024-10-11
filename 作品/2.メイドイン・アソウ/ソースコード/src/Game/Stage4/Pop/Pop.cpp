#include "Pop.h"
#include <DxLib.h>

//無→豆　回転回数
#define POP_BEAN (5)
//豆→ちょいはじける　回転回数
#define POP_BEANBURST (10)
//ちょいから全部はじける
#define POP_BURST (15)

CPop::CPop()
{
	Init();
}
CPop::~CPop()
{
	Exit();
}

void CPop::Init()//初期化
{
	// キャラクターの初期データをセット
	PopX = 0;
	PopY = 0;
	nothing = true;
	little = false;
	half = false;
	full = false;
}
void CPop::Load()//ロード
{
	// グラフィックのロード
	PopGraph[0] = LoadGraph("data/Game/Stage4/Bg.png");
	PopGraph[1] = LoadGraph("data/Game/Stage4/popstate1.png");
	PopGraph[2] = LoadGraph("data/Game/Stage4/popstate2.png");
	PopGraph[3] = LoadGraph("data/Game/Stage4/popstate3.png");

}
void CPop::Step(int num)//ステップ
{
	if (num > POP_BEAN)
	{
		nothing = false;
		little = true;
	}
	if (num > POP_BEANBURST)
	{
		little = false;
		half = true;
	}
	if (num > POP_BURST)
	{
		half = false;
		full = true;
	}
}
void CPop::Draw()//描画
{
	DrawGraph(PopX, PopY, PopGraph[0], true);

	if (little == true)
		DrawGraph(PopX, PopY, PopGraph[1], true);
	else if (half == true)
		DrawGraph(PopX, PopY, PopGraph[2], true);
	else if (full == true)
		DrawGraph(PopX, PopY, PopGraph[3], true);

}
void CPop::Exit()//破棄
{
	for (int i = 0; i < 4; i++ )
		DeleteGraph(PopGraph[i]);
}





