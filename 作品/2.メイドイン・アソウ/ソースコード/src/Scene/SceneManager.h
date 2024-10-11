#pragma once
#include "SceneBase.h"

class CSceneManager
{
	enum tagSCENE {
		SCENE_TITLE,		//タイトル
		SCENE_OPERATION,	//操作説明
		SCENE_PLAY,			//プレイ
		SCENE_CLEAR,		//クリア
		SCENE_GAMEOVER,		//ゲームオーバー

		SCENE_NUM
	}m_eAllSceneID;			 // シーン保存

	CSceneBase* cScene;

public:
	CSceneManager();
	~CSceneManager();

	void Init();	//初期化
	int Loop();		//シーン管理

	void Draw();	//描画
	void Exit();	//破棄

};




