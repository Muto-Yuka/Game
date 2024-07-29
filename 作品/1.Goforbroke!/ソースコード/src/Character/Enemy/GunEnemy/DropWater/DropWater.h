#pragma once
#include "DxLib.h"
#include "../../../../Character/Player/Player.h"

class CDropWater
{
private:
	int		m_iDropHndl;		//画像ハンドル
	VECTOR	m_vWaterPos;		//水の座標
	float	m_fRadius;			//水の半径
	bool	m_bSurvival;		//生存フラグ true:描画する　false:しない
	bool	m_bMove;			//水の座標を更新するか true:更新する　false:待機
	bool	m_bPlayerHit;		//プレイヤーとHITした

public:
	void Init();						//初期化
	void DuplicateLoad(int DropHndl);	//複製ロード
	void Step();						//ループ
	void Draw();						//描画
	void Exit();						//破棄

	//プレイヤーとHITした時の処理
	void HitCalc(CPlayer& cPlayer);
	//プレイヤーと接触した時プレイヤーが水を飲む
	void HitDrink();
	//プレイヤーと接触した時水場に水を戻す
	void HitReturn();


	//**ゲッター・セッター**

	//敵の座標をセットする
	inline void SetWaterPos(VECTOR EnemyPos) { m_vWaterPos = EnemyPos; }
	//座標を取得
	inline VECTOR GetPosition() { return m_vWaterPos; }
	//半径取得
	inline float GetRadius(void) { return m_fRadius; }
	//生存フラグをtrueにセットする　再描画する
	inline void SetSurvival() { m_bSurvival = true; }
	//生存フラグをゲットする
	inline bool GetSurvival() { return m_bSurvival; }

	//座標更新フラグをセット・ゲットする
	inline bool GetMove() { return m_bMove; } //move true:座標更新　false:更新しない
	inline void SetMove(bool frg) { m_bMove = frg; }

};



