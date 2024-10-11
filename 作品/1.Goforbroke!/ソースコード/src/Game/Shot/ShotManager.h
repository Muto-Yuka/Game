#pragma once
#include "shot.h"

#define PL_SHOT_NUM (50)
#define EM_SHOT_NUM (100)

class ShotManager
{
private:
	//プレイヤーのショット
	CShot cPlayerShot[PL_SHOT_NUM];
	//敵のショット
	CShot cEnemyShot[EM_SHOT_NUM];

public:
	//コンストラクタ・デストラクタ
	ShotManager();
	~ShotManager();

	//初期化
	void Init();

	void Load();
	void Exit();
	void Step();
	void Draw();

	//ショットリクエスト
	void RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed);	//プレイヤー
	void RequestEnemyShot(const VECTOR& vPos, const VECTOR& vSpeed);	//敵
	//プレイヤーのショット情報取得
	CShot& GetPLayerShot(int iID) { return cPlayerShot[iID]; }
	CShot& GetEnemyShot(int iID) { return cEnemyShot[iID]; }


};