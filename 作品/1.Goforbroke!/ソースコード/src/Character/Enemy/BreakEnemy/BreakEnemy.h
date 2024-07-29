#pragma once
#include "../BaseEnemy.h"
#include "../../../Game/Screen/Screen.h"

#define BREAK_ENEMY_NUM (2)	//同時に出現する敵の数

class CBreakEnemy
{
private:
	int m_iWaitRespawn;		//リスポーンするまでの時間をカウント
	int m_iWaitCnt;			//次の敵が出てくるまでの時間管理
	bool NextDayFrg;		//次の日に行くかどうか　true:次の日へ　false:まだ待つ 
	int NextDayCount;		//午後時間が終わって強制で次のシーンへいく時間管理

public:
	//コンストラクタ・デストラクタ
	CBreakEnemy();
	~CBreakEnemy();

	//初期化
	void Init(CApple& cApple);
	void Load();
	void Exit();
	void Step(CWater& cWater, CScreen& cScreen);
	void Draw();


	CEnemyBase m_cBreakEnemy[BREAK_ENEMY_NUM];

	//次の日にすすむか受け取る
	inline bool GetNextDayFrg() { return NextDayFrg; }
	inline void SetNextDayFrg(bool Frg) { NextDayFrg = Frg; }

private:
	//敵のリクエスト
	void RequestEnemy();

};



