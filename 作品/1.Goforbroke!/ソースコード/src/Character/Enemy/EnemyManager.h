#pragma once
#include "GunEnemy/GunEnemy.h"
#include "BreakEnemy/BreakEnemy.h"

class CEnemyManager {
private:
	CGunEnemy cGunEnemy;		//プレイヤーに向かって弾を撃つ敵
	CBreakEnemy cBreakEnemy;	//水場を壊しに向かう敵

public:
	void Init(CApple& cApple);
	void Load();
	void Exit();
	void Step(CPlayer& cPlayer, ShotManager& cEnemyShot, CWater& cWater, CScreen& cScreen);
	void Draw();


	//**ゲッター・セッター**
		//敵情報取得
	inline CEnemyBase& GetGunEnemy(int iID) { return cGunEnemy.m_cGunEnemy[iID]; }
	inline CEnemyBase& GetBreakEnemy(int iID) { return cBreakEnemy.m_cBreakEnemy[iID]; }
	//敵が落とす水情報取得
	inline CDropWater& GetDropWater(int iID) { return cGunEnemy.m_cDropWater[iID]; }

	//敵の位置情報取得
	VECTOR GetGunEnemyPos() { return cGunEnemy.m_cGunEnemy->GetPos(); }
	VECTOR GetBreakEnemyPos() { return cBreakEnemy.m_cBreakEnemy->GetPos(); }


	//次の日に行くかどうか　true:次の日へ　false:待機
	bool GetNextDayFrg();
	void SetNextDayFrg(bool frg);


};
