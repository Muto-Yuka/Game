#pragma once
#include <DxLib.h>
#include "../Player/Player.h"
#include "../../Game/shot/shotManager.h"
#include "../../MyLib/BaseAnim/BaseAnim.h"
#include "../../Game/Item/Apple/Apple.h"
#include "../../Game/Item/Water/Water.h"

#define PLAYER_ATTACK	(5) //プレイヤーの一回の攻撃量


class CEnemyBase : public CBaseAnim
{
private:
	float m_fAngle;		//角度
	int m_iHp, spare;				//敵のｈｐ
	int m_DropItem;					//ドロップするアイテムハンドル
	float m_fTransparency;	//モデルの透明度
	bool m_bStopBEnemy;		//壊す敵が移動するかどうか　true:止まる（ヒットした）false:動く

//ベクトル
	VECTOR m_vInitPos;		//敵が逃げ帰る座標
	VECTOR SubVector;	//敵からプレイヤーに向かうベクトル

//boolフラグ
	bool Clear;

	//時間カウント変数
	int m_enemy_count;
	int m_iWaitBulletCnt;	//敵の弾の出現時間管理

//画像ハンドル・モデルハンドル1
	int m_iHpGaugeHndl;		//hpゲージハンドル

public:

	void Init(CApple& cApple);
	void Draw();
	void Exit();

	//データ関連の通常画像ロード
	void Load(int iMdlHndl);
	//ドロップアイテム関連３ｄモデルロード
	//void DropItemLoad(int DropItem);
	//毎フレーム呼ぶ処理
	void GunEnemyStep(CPlayer& cPlayer, ShotManager& cEnemyShot);
	void BreakEnemyStep(CWater& cWater);


	//各関数化した処理===================================================
	//===================================================================

	//弾発射処理
	void EnemyShot(ShotManager& cEnemyShot);
	//当たり判定処理
	void HitCalc(CApple& cApple);
	//常に指定された方向に向く
	void EnemyLook(VECTOR TargetPos, VECTOR EnemyPos);
	//向いてる方向に進む関数
	void EnemyMove();
	//水場を壊す処理
	void BreakWater(CWater& cwater);
	//ダメージを受けたときに点滅させる処理 0~1　１のほうがはっきり　０は透明
	void Transparency(int Hndl, float Transparency);

	//ゲッター・セッター==================================================
	//====================================================================

	//敵がフィールドにいるか　falseかtrueか
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);
	//半径取得
	float GetRadius(void) { return m_fRadius; }

	//敵の座標を取得
	VECTOR GetPos() { return m_vPos; }
	//敵のｈｐをセット（初期化）
	void SetEnemyHP(int HP) { m_iHp = HP; spare = HP; }
	//生存フラグをゲットする
	inline bool GetSurvival() { return m_bSurvival; }



};