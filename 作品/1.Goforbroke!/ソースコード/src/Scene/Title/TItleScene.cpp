#include <DxLib.h>
#include "TitleScene.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Sound/Sound.h"

static const char TITLE_PATH[] = { "data/Scene/Title/Title.png" };

CTitleScene::CTitleScene()
{
	Init();
}
CTitleScene::~CTitleScene()
{
	Exit();
	CFade::DeleteInstance();
}

//ループ
bool CTitleScene::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (CTitleScene:: * Title[])() = {
		&CTitleScene::Init,& CTitleScene::Load,& CTitleScene::Step,& CTitleScene::Exit,& CTitleScene::Next
	};
	//idに合わせて処理を実行
	(this->*Title[m_eTitleID])();

	if (m_eTitleID == SCENE_NEXT)
		return true;
	else
		return false;
}

//初期化
void CTitleScene::Init()
{
	m_iHndl = -1;		
	m_eTitleID = SCENE_LOAD;
}

//ロード
void CTitleScene::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(TITLE_PATH);
	}
	CSound::Play(CSound::SOUND_TITLE, DX_PLAYTYPE_LOOP);
	m_eTitleID = SCENE_STEP;
	CFade::GetInstance()->Request(4.0f, true);
}

//ステップ
void CTitleScene::Step()
{
	if (!CFade::GetInstance()->IsEnd()) return;

	//決定ボタンで次へ
	if (CInput::IsInputPush(CInput::INPUT_NEXT) || (CPadInput::PadInput & PAD_INPUT_8))
	{
		m_eTitleID = SCENE_EXIT;
		CFade::GetInstance()->Request(4.0f, false);
	}
}

//描画
void CTitleScene::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void CTitleScene::Exit()
{
	if (!CFade::GetInstance()->IsEnd()) return;
	
	DeleteGraph(m_iHndl);

	m_eTitleID = SCENE_NEXT;
}

//次へ
void CTitleScene::Next()
{
	m_eTitleID = SCENE_INIT;
}


