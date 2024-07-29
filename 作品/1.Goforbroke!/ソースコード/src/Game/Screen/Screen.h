#pragma once
#include "../../Character/Enemy/BaseEnemy.h"
#include "../../Game/Mission/Mission.h"
#include "../../Character/Player/Player.h"

#define AM_TIME_COUNT (800)		//午前中が終わる時間カウント
#define PM_TIME_COUNT (4000)	//午後が終わる時間カウント

class CScreen {
private:
	int m_UpHndl;		 //画面上部に表示する画像ハンドル
	int m_AmCount;		//夕方になるまでのカウント
	int m_PmCount;		//朝になるまでのカウント
	int m_PlayerHp;		//Hp（リンゴ）
	float WaterHp;		//水場の体力

public:
	CScreen();
	~CScreen();

	void Init();
	void Load();
	void Step(int SceneId, CPlayer& cPlayer);	//朝か夜かiｄで受け取る
	void Day1Draw(int SceneId);	//朝か夜かiｄで受け取る
	void Day2Draw(int SceneId);	//朝か夜かiｄで受け取る
	void Exit();


	//ゲッター・セッター==========

	inline void SetPlayerHp(int Hp) { m_PlayerHp = Hp; }
	inline int GetAmTimeLimit() { return m_AmCount; }		//朝の時間を取得
	inline int GetPmTimeLimit() { return m_PmCount; }		//午後の時間を取得
	inline void SetWaterHp(float hp) { WaterHp = hp; }		//水場の体力取得
};


