#pragma once

#include "PlayScene/Day1PlayScene.h"
#include "PlayScene/Day2PlayScene.h"
#include "Title/TitleScene.h"
#include "Clear/ClearScene.h"
#include "GameOver/GameOverScene.h"
#include "Operation/Operation.h"

class CSceneManager
{
	int shadowHndl;		//シャドウハンドル

	enum tagSCENE {
		SCENE_TITLE,		//タイトル
		SCENE_OPERATION,	//操作説明
		SCENE_PLAY_DAY1,	//一日目　
		SCENE_PLAY_DAY2,	//二日目
		SCENE_RESULT,		//リザルト
		GAMEOVER,			//ゲームオーバー
		GAMEOVER_PLACE,		//水場が８０以下の場合
		GAMEOVER_LACK,		//水分不足

		SCENE_NUM
	}m_eAllSceneID;			 // シーン保存

	CTitleScene		cTitleScene;		//タイトル
	COperationScene cOperation;		//操作説明
	CClearScene		cClearScene;		//リザルト
	CGameOverScene	cGameOverScene;	//ゲームオーバーシーン
	CDay1PlayScene	cDay1PlayScene;	//プレイヤー処理
	CDay2PlayScene	cDay2PlayScene;	//プレイヤー処理

public:
	CSceneManager();
	~CSceneManager();

	void Init();
	//繰り返し行う処理
	int Loop();
	//描画処理
	void SceneDraw();
	//影含める描画
	void Draw();
	void Exit();

};



