#include "BackGround.h"
#include <DxLib.h>

//îwåi
const char BG_PATH[] = { "data/Game/Stage1/Bg.png" };

CBackGround::CBackGround()
{
	Init();
}
CBackGround::~CBackGround()
{
	Exit();
}

//èâä˙âª
void CBackGround::Init()
{
	bgSkyX[0] = 0;
	bgSkyX[1] = -1920;
}
//ÉçÅ[Éh
void CBackGround::Load()		
{
	//îwåi
	for (int i = 0; i < 2; i++)
	{
		bgSkyHandle[i] = LoadGraph(BG_PATH);
	}
}
//ÉXÉeÉbÉv
void CBackGround::Step(CPlayer& cPlayer)
{
	//îwåiÇÃà⁄ìÆ
	for (int i = 0; i < 2; i++)
	{
		if (bgSkyX[i] > 1920)
		{
			int Index = 0;
			if (i == 0)
				Index = 1;
			bgSkyX[i] = bgSkyX[Index] - 1920;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (bgSkyX[i] < -1920)
		{
			int Index = 0;
			if (i == 0)
				Index = 1;
			bgSkyX[i] = bgSkyX[Index] + 1920;
		}
	}
	if (cPlayer.GetLife())
	{
		if (CheckHitKey(KEY_INPUT_D) == 1)
		{
			for (int i = 0; i < 2; i++)
			{
				bgSkyX[i] -= 2;
			}
		}
		if (CheckHitKey(KEY_INPUT_A) == 1)
		{
			for (int i = 0; i < 2; i++)
			{
				bgSkyX[i] += 3;
			}
		}
	}
	
}
//ï`âÊ
void CBackGround::Draw()
{
	//îwåi
	for (int i = 0; i < 2; i++)
		DrawGraph(bgSkyX[i], 0, bgSkyHandle[i], true);
}
//îjä¸
void CBackGround::Exit()	
{
	for (int i = 0; i < 2; i++)
		DeleteGraph(bgSkyHandle[i]);
}








