#include <DxLib.h>
#include "Title.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"

static const char TITLE_PATH[] = { "data/Scene/Title/Title.png" };

CTitle::CTitle()
{
	Init();
}
CTitle::~CTitle()
{
	Exit();
}

//ループ
int CTitle::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (CTitle:: * Operation[])() = {
		&CTitle::Init,& CTitle::Load,& CTitle::Step,& CTitle::Exit, & CTitle::Next
	};
	//idに合わせて処理を実行
	(this->*Operation[m_eSceneID])();

	if (m_eSceneID == SCENE_NEXT)
		return 1;

	return -1;
}

//初期化
void CTitle::Init()
{
	CSceneBase::Init();
	m_fVolume = 1;
	CSound::SetVolume(CSound::SOUND_TITLE, 0.2);

}

//ロード
void CTitle::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(TITLE_PATH);
	}
	CSound::Play(CSound::SOUND_TITLE, DX_PLAYTYPE_BACK, true);

	CSceneBase::Load();
}

//ステップ
void CTitle::Step()
{
	CSceneBase::Step();
	Volume();
}

//描画
void CTitle::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void CTitle::Exit()
{
	CSceneBase::Exit();
}

//次へ
void CTitle::Next()
{
	CSceneBase::Next();
}

//音量調節
void CTitle::Volume()
{
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (m_fVolume < 255)
			m_fVolume++;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (m_fVolume > 0)
			m_fVolume--;
	}

	CSound::SetVolume(CSound::SOUND_TITLE, m_fVolume);
}







