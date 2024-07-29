#include "SceneManager.h"
#include "../MyLib/Input/Input.h"
#include "../MyLib/Fade/Fade.h"
#include "../MyLib/Sound/Sound.h"

#include "Title/Title.h"
#include "Play/Play.h"
#include "Clear/Clear.h"
#include "GameOver/Gameover.h"

CSceneManager::CSceneManager()
{
	Init();
}
CSceneManager::~CSceneManager()
{
	//メモリを解放する
	delete cScene;

	Exit();
	CSound::Exit();
}

//初期化
void CSceneManager::Init()
{
	CSound::Init();
	CSound::AllLoad();

	cScene = new CTitle();
	m_eAllSceneID = SCENE_TITLE;
}

//ループ
int CSceneManager::Loop()
{
	int iRet = 0;

	switch (m_eAllSceneID)
	{
	case SCENE_TITLE:
		if (cScene->Loop() == 1)
		{
			delete cScene;
			cScene = new CPlay();
			m_eAllSceneID = SCENE_PLAY;
		}
		break;
	case SCENE_OPERATION:
		//if (cOperation.Loop())
		//	m_eAllSceneID = SCENE_PLAY;
		break;

	case SCENE_PLAY:
		if (cScene->Loop() == 1)
		{	//クリア
			delete cScene;
			cScene = new CClear();

			m_eAllSceneID = SCENE_CLEAR;
		}
		else if (cScene->Loop() == 2)
		{	//ゲームオーバー
			delete cScene;
			cScene = new CGameover();
			m_eAllSceneID = SCENE_GAMEOVER;
		}
		break;

	case SCENE_CLEAR:
		cScene->Loop();
		break;

	case SCENE_GAMEOVER:
		cScene->Loop();
		break;
	}

	//フェード処理の更新
	CFade::GetInstance()->UpDate();

	return iRet;
}

//更新処理・描画
void CSceneManager::Draw()
{
	switch (m_eAllSceneID)
	{
	//タイトル
	case SCENE_TITLE:
		cScene->Draw();
		break;

	//操作説明
	case SCENE_OPERATION:
		cScene->Draw();
		break;

	//プレイ
	case SCENE_PLAY:
		cScene->Draw();
		break;

	//クリア
	case SCENE_CLEAR:
		cScene->Draw();
		break;

	//ゲームオーバ-
	case SCENE_GAMEOVER:
		cScene->Draw();
		break;
	}

	//フェード関連
	CFade::GetInstance()->Draw();

}

void CSceneManager::Exit()
{

}
