#include <DxLib.h>
#include "Stage1.h"
#include "../../MyLib/Sound/Sound.h"

CStage1::CStage1()
{
	Init();
}
CStage1::~CStage1()
{
	Exit();
}

//初期化
void CStage1::Init()
{
	cBackGround.Init();
	cPlayer.Init();
	cEnemy.Init();
	cBrock.Init();
	cFlag.Init();

	CSound::SetVolume(CSound::SOUND_STAGE1, 1);
}
//ロード
void CStage1::Load()
{
	cBackGround.Load();
	cPlayer.Load();
	cEnemy.Load();
	cBrock.Load();
	cFlag.Load();

	CSound::Play(CSound::SOUND_STAGE1, DX_PLAYTYPE_BACK, true);
}
//ステップ　-1：待機
int  CStage1::Step()
{
	int ret = -1;

	cBackGround.Step(cPlayer);
	cPlayer.Step();
	cEnemy.Step(cPlayer);
	cBrock.Step(cPlayer);
	cFlag.Step(cPlayer);

	//破棄へすすむ
	if (cPlayer.GetClear() || cPlayer.GetGameover())
	{
		ret = 0;
		CSound::AllStop();
	}

	return ret;
}
//描画
void CStage1::Draw()
{
	cBackGround.Draw();
	cPlayer.Draw();
	cEnemy.Draw();
	cBrock.Draw();
	cFlag.Draw();
}
//破棄
void CStage1::Exit()
{
	cBackGround.Exit();
	cPlayer.Exit();
	cEnemy.Exit();
	cBrock.Exit();
	cFlag.Exit();
}
//リザルト情報を返す
int CStage1::GetResult()
{
	//0:待機　1:クリア　2:ゲームオーバー

	if (cPlayer.GetClear())
		return 1;
	if (cPlayer.GetGameover())
		return 2;

	return 0;
}




