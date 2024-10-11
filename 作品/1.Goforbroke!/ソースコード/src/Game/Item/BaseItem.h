#pragma once
#include "DxLib.h"

//食料/水分ゲージイラストをずらす
#define SHIFT_ITEM_PICTURE	(28)

class CItemBase
{
protected:
	int m_iHndl;		//画像ハンドル
	bool m_bSurvival;	//生存フラグ
	float m_fRadius;	//半径
	VECTOR m_vPos;		//座標
	int m_RespawnTime;	//新たにスポーンするまでの時間
	float m_fHp;

public:
	//コンストラクタ
	CItemBase();
	//デストラクタ
	~CItemBase();
	//初期化 半径をセット
	void Init(float Radius);
	//ループ
	void Step();
	//リスポーンするループ処理 描画範囲xz, アイテムの数
	void RespawnStep(int x, int z, int ItemNum);
	//通常ロード 出現範囲をセット
	void Load(int x, int y);
	//データを複製ロード
	void DuplicateLoad(int iMdlHndl, int x, int z);
	//描画
	void Draw();
	//終了
	void Exit();


	//アイテムリスポーンの処理 描画する範囲、経過時間
	void RespawnItem(int x, int z, int ItemNum);
	//アイテムがヒットし,フラグをoffに
	void HitItem() { m_bSurvival = false; }
	//ただの複製ロード
	void DuplicateLoad(int Hndl) { m_iHndl = MV1DuplicateModel(Hndl); }


	//**ゲッター・セッター**==

		//アイテムがフィールドにあるか　falseかtrueか
	inline 	bool RequestItem(const VECTOR& vPos);
	//当たり判定用（半径取得）
	inline 	float GetRadius() { return m_fRadius; }
	//座標取得
	inline 	VECTOR GetPosition() { return m_vPos; }
	//生存フラグ取得　true:生存　false:死亡
	inline 	bool GetSurvivalFrg() { return m_bSurvival; }
	//初期座標をセット
	inline 	void SetInitPos(VECTOR pos) { m_vPos = pos; }
	//hpをセット
	inline  void SetHp(float hp) { m_fHp = hp; }
	//hpをゲット
	inline float GetHp() { return m_fHp; }

};






