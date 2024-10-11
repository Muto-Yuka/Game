#include <DxLib.h>
#include "Clear.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"

static const char CLEAR_PATH[] = { "data/Scene/Clear/Clear.png" };

CClear::CClear()
{
	Init();
}
CClear::~CClear()
{
	Exit();
	CFade::DeleteInstance();
}

//ループ
int CClear::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (CClear:: * Operation[])() = {
		&CClear::Init,& CClear::Load,& CClear::Step,& CClear::Exit, & CClear::Next
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
void CClear::Init()
{
	CSceneBase::Init();
}

//ロード
void CClear::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(CLEAR_PATH);
	}
	CSound::Play(CSound::SOUND_CLEAR, DX_PLAYTYPE_BACK, true);

	CSceneBase::Load();
}

//ステップ
void CClear::Step()
{
	//CSceneBase::Step();
}

//描画
void CClear::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void CClear::Exit()
{
	CSceneBase::Exit();
}

//次へ
void CClear::Next()
{
	CSceneBase::Next();
}


