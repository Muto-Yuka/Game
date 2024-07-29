#pragma once
#include "../tagStage.h"
#include "../../Game/GameBase.h"
#include "../SceneBase.h"
#include "../../MyLib/Fade/Fade.h"

class CGameBase;

class CPlay : public CSceneBase
{
	enum tagPlay
	{
		STATEID_INIT,
		STATEID_LOAD,
		STATEID_STEP,
		STATEID_FIN,

		STATEID_NUM
	};

	CGameBase* m_base;			//各シーン格納
	int m_ePlayID;				//現在の状態 init~Exit
	int m_next;					//シーンを関数ポインタで管理(ステージ管理)
	int m_eClearCount;			//何回クリアしたか
	void (CPlay::* m_step[STAGE_NUM])();	// シーンを関数ポインタで管理するためのもの


public:
	CPlay();
	~CPlay();

	int  Loop();		//ループ 
	void Draw();		//描画

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Exit();		//破棄

	//次のシーンを作成
	void CreateScene();
};
