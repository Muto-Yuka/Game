#pragma once
#include "../BaseEnemy.h"
#include "DropWater/DropWater.h"
#include "../../../Game/Screen/Screen.h"

#define GUN_ENEMY_NUM (2)	//同時に出現する敵の数
#define G_ENEMY_HP	(3)		//何回弾に当たったら消えるか
#define DROP_WATER_MAXNUM	(3)


class CGunEnemy
{
private:
	int m_iWaitRespawn;		//リスポーンするまでの時間をカウント
	int m_iWaitCnt;			//次の敵が出てくるまでの時間管理
	bool NextDayFrg;		//次の日に行くかどうか　true:次の日へ　false:まだ待つ 
	int NextDayCount;		//午後時間が終わって強制で次のシーンへいく時間管理

public:
	//コンストラクタ・デストラクタ
	CGunEnemy();
	~CGunEnemy();

	//初期化
	void Init(CApple& cApple);
	void Load();
	void Exit();
	void Step(CPlayer& cPlayer, ShotManager& cEnemyShot, CScreen& cScreen);
	void Draw();


	//敵の数分用意
	CEnemyBase m_cGunEnemy[GUN_ENEMY_NUM];
	//敵の数分水を用意
	CDropWater m_cDropWater[GUN_ENEMY_NUM];

	//**ゲッター・セッター**
		//次の日にすすむか受け取る
	inline bool GetNextDayFrg() { return NextDayFrg; }
	inline void SetNextDayFrg(bool Frg) { NextDayFrg = Frg; }

private:
	//リクエスト
	void RequestEnemy();



};



