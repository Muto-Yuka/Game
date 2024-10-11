#pragma once

#include "../../Game/Camera/CameraManager.h"
#include "../../Game/shot/shotManager.h"
#include "../../Character/Enemy/EnemyManager.h"
#include "../../Game/Hit/Hit.h"
#include "../../Game/Screen/Screen.h"
#include "../../Game/Item/ItemManager.h"
#include "../../Game/Item/Apple/Apple.h"
#include "../../Game/Mission/Mission.h"
#include "../../Game/Field/FieldManager.h"

class CBaseScene 
{
protected:
	enum tagPLAY_SCENE {
		SCENE_INIT,		//初期化
		SCENE_LOAD,		//ロード
		SCENE_AM_STEP,	//午前の処理
		SCENE_PM_STEP,	//午後の処理
		SCENE_EXIT,		//破棄処理
		SCENE_NEXT,		//次へ

	}m_eSceneID;

	CCameraManager	cCameraManager;	
	CPlayer			cPlayer;		
	ShotManager		cShotManager;
	CEnemyManager	cEnemyManager;
	CScreen			cScreen;
	CMission		cMission;
	CFieldManager	cFieldManager;
	CItemManager	cItemManager;

public:

	//繰り返し行う処理
	void Loop();
	//描画処理
	void Draw();


	//初期化
	void Init();
	//終了処理
	void Exit();
	//データロード
	void Load();
	//毎フレーム呼ぶ処理
	void AmStep();
	void PmStep();
	void Next();


	//当たり判定をまとめた関数
	void Collision();


};



