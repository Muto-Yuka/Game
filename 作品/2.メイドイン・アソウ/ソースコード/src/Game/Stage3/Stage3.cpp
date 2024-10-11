#include <DxLib.h>
#include "Stage3.h"
#include "../../MyLib/Sound/Sound.h"

CStasge3::CStasge3()
{
	Init();
}
CStasge3::~CStasge3()
{
	Exit();
}

//初期化
void CStasge3::Init()
{
	cBackGround.Init();
	cPlayer3.Init();
	cHitPoint.Init();
	cDrop.Init();
}
//ロード
void CStasge3::Load()
{
	cBackGround.Load();
	cPlayer3.Load();
	cHitPoint.Load();
	cDrop.Load();

	CSound::Play(CSound::SOUND_STAGE3, DX_PLAYTYPE_BACK, true);
}
//ステップ
int CStasge3::Step()
{
	int ret = -1;

	cBackGround.Step();
	cPlayer3.Step();
	cHitPoint.Step();
	cDrop.Step(cPlayer3);

	//破棄へ
	if (cDrop.Hit(cHitPoint) != 0)
	{
		CSound::AllStop();
		return 1;
	}

	return ret;
}
//描画
void CStasge3::Draw()
{
	cBackGround.Draw();
	cPlayer3.Draw();
	cHitPoint.Draw();
	cDrop.Draw();
}
//破棄
void CStasge3::Exit()
{
	cBackGround.Exit();
	cPlayer3.Exit();
	cHitPoint.Exit();
	cDrop.Exit();
}

//リザルト情報を返す
int CStasge3::GetResult()
{
	//0:待機　1:クリア　2:ゲームオーバー
	return cDrop.Hit(cHitPoint);
}



