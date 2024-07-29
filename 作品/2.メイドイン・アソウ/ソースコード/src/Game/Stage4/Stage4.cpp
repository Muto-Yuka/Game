#include <DxLib.h>
#include "Stage4.h"
#include "../../MyLib/Sound/Sound.h"

//背景
static const char BG_PATH[] = { "data/" };

CStasge4::CStasge4()
{
	Init();
}
CStasge4::~CStasge4()
{
	Exit();
}

//初期化
void CStasge4::Init()
{
	cPlayer4.Init();
	cPop.Init();

	CSound::SetVolume(CSound::SOUND_STAGE4, 0.7);

}
//ロード
void CStasge4::Load()
{
	cPlayer4.Load();
	cPop.Load();

	CSound::Play(CSound::SOUND_STAGE4, DX_PLAYTYPE_BACK, true);
}
//ステップ
int CStasge4::Step()
{
	int ret = -1;
	cPlayer4.Step();
	cPop.Step(cPlayer4.GetTime());

	if (cPlayer4.GetTime() >= POP_FULL)
	{
		ret = 1;
		CSound::AllStop();
	}

	return ret;

}
//描画
void CStasge4::Draw()
{
	cPop.Draw();
	cPlayer4.Draw();
}
//破棄
void CStasge4::Exit()
{
	cPlayer4.Exit();
	cPop.Exit();
}

//リザルト情報を返す
int CStasge4::GetResult()
{
	//0:待機　1:クリア　2:ゲームオーバー
	if (cPlayer4.GetTime() >= POP_FULL)
		return 1;

	return 0;
}


