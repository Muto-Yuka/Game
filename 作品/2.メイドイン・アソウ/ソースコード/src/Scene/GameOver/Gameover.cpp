#include <DxLib.h>
#include "Gameover.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"

static const char GAMEOVER_PATH[] = { "data/Scene/Gameover/Gameover.png" };

CGameover::CGameover()
{
	Init();
}
CGameover::~CGameover()
{
	Exit();
	CFade::DeleteInstance();
}

//ループ
int CGameover::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (CGameover:: * Operation[])() = {
		&CGameover::Init,& CGameover::Load,& CGameover::Step,& CGameover::Exit, & CGameover::Next
	};
	//idに合わせて処理を実行
	(this->*Operation[m_eSceneID])();

	if (m_eSceneID == SCENE_NEXT)
	{ 
		CSound::AllStop();
		return 1;
	}

	return -1;
}

//初期化
void CGameover::Init()
{
	CSceneBase::Init();
}

//ロード
void CGameover::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(GAMEOVER_PATH);
	}
	CSound::Play(CSound::SOUND_GAMEOVER, DX_PLAYTYPE_BACK, true);

	CSceneBase::Load();
}

//ステップ
void CGameover::Step()
{
	//CSceneBase::Step();
}

//描画
void CGameover::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void CGameover::Exit()
{
	CSceneBase::Exit();
}

//次へ
void CGameover::Next()
{
	CSceneBase::Next();
}


