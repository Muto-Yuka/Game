#include <DxLib.h>
#include "ClearScene.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"

static const char TITLE_PATH[] = { "data/Scene/result/result.png" };

CClearScene::CClearScene()
{
	Init();
}
CClearScene::~CClearScene()
{
	Exit();
	CFade::DeleteInstance();

}

//ループ
bool CClearScene::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (CClearScene:: * Clear[])() = {
		&CClearScene::Init,& CClearScene::Load,& CClearScene::Step,& CClearScene::Exit,& CClearScene::Next
	};
	//idに合わせて処理を実行
	(this->*Clear[m_eClearID])();

	if (m_eClearID == SCENE_NEXT)
		return true;
	else
		return false;

}

//初期化
void CClearScene::Init()
{
	m_iHndl = -1;	
	m_eClearID = SCENE_LOAD;
}

//ロード
void CClearScene::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(TITLE_PATH);
	}
	m_eClearID = SCENE_STEP;
	CFade::GetInstance()->Request(4.0f, true);

}

//ステップ
void CClearScene::Step()
{
	if (!CFade::GetInstance()->IsEnd()) 
		return;

	CSound::Play(CSound::SOUND_CLEAR, DX_PLAYTYPE_NORMAL);

	if (!CSound::IsPlay(CSound::SOUND_CLEAR))
	{
		m_eClearID = SCENE_EXIT;
		CFade::GetInstance()->Request(4.0f, false);

	}
}

//描画
void CClearScene::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void CClearScene::Exit()
{
	CFade::DeleteInstance();

	DeleteGraph(m_iHndl);
	CSound::AllStop();

	m_eClearID = SCENE_NEXT;
}

//次へ
void CClearScene::Next()
{
	m_eClearID = SCENE_INIT;
}




