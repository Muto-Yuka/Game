#include <DxLib.h>
#include "SceneBase.h"
#include "../MyLib/Fade/Fade.h"
#include "../MyLib/Input/Input.h"
#include "../MyLib/Sound/Sound.h"

//初期化
void CSceneBase::Init()
{
	m_iHndl = -1;
	m_eSceneID = SCENE_LOAD;
}

//ロード
void CSceneBase::Load()
{
	m_eSceneID = SCENE_STEP;
	CFade::GetInstance()->Request(4.0f, true);
}

//ステップ
void CSceneBase::Step()
{
	if (!CFade::GetInstance()->IsEnd()) return;

	//決定ボタンで次へ
	if (CInput::IsInputPush(CInput::INPUT_NEXT))
	{
		CSound::AllStop();								//サウンド停止
		m_eSceneID = SCENE_EXIT;						//次のシーン
		CFade::GetInstance()->Request(4.0f, false);		//フェードリクエスト
	}
}

//破棄
void CSceneBase::Exit()
{
	if (!CFade::GetInstance()->IsEnd()) return;

	DeleteGraph(m_iHndl);
	CFade::DeleteInstance();

	m_eSceneID = SCENE_NEXT;
}

//次へ
void CSceneBase::Next()
{
	m_eSceneID = SCENE_INIT;
}


