#pragma once
#include "../../Game/shot/shotManager.h"
#include "../../Game/Item/Water/Water.h"
#include "PlayAnim.h"

//プレイヤーHP
static const int PLAYER_HP = (5);

class CPlayer : public CPlayAnim
{
	int		m_iRepairHndl;			//修理する際に描画する
	int		m_iWaitBulletCnt;		//０以下で弾再発射
	int		m_iRepair_time;			//水場の修理時間　０以下で修理完了
	int		m_iWaterNum;			//取った水の数

public:

	CPlayer();
	~CPlayer();

	void Init();	//初期化
	void Load();	//ロード
	void Loop(ShotManager& cShotManager, CWater& cWater);	//ループ

	//行動処理
	void PlayerMove();
	//ショット関数
	void PlayerShot(ShotManager& cShotManager);
	//当たり判定
	void HitCalc();
	//現在位置に座標更新
	void ReflectCollision(VECTOR vAddVec);
	//水場を修理する
	void WatrRepair(CWater& cWater);

	//フィールド用当たり判定
	VECTOR GetCenter();

//ゲッター
	inline int GetPlayerHP() { return m_HP; }		//HP
	inline float GetRadius() { return m_fRadius; }	//半径
	inline float GetRotateY() { return m_vRot.y; }	//ｙ軸角度
	inline int GetWaterNum() { return m_iWaterNum; }//持っている水の数を取得

//セッター
	inline void SetWaterNum() { m_iWaterNum++; }	//水を持たせる

};




