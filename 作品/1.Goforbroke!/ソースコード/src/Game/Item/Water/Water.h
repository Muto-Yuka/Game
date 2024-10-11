#pragma once
#include "../BaseItem.h"
#include "Number/Number.h"

//水分ゲージの数
#define GAUGE_NUM	(8)		

class CWater : public CItemBase
{
private:
	float	m_hp;						//水場の体力
	bool	HitFrg;						//水場に当たってるかどうか　true当たってる　false当たってない
	int		interval;					//水分回復する速度（間隔）
	int		m_iOnHndl[GAUGE_NUM];		//2D食料ゲージ画像ハンドル(うえに描画)
	int		m_iUnderHndl[GAUGE_NUM];	//2D食料ゲージ画像ハンドル（下に影として描画）
	int		WaterGauge;					//2d水分ゲージ表示
	int		StartTime;					//ミッションが呼ばれてからの時間
	bool	m_bResult;					//リザルトに行くかどうか
	int		m_iPlayerWater;				//プレイヤーが持ってる水の数
	int		HitCount;					//連続で水場の％をアップしないよう制御する

	//画像ハンドル・モデルハンドル
	int m_2dHpHndl;
	int m_iFoggyHndl;					//水が減ってしにかけの時に青く描画

	CNumber cNumber;

public:

	//コンストラクタ
	CWater();
	//デストラクタ
	~CWater();

	//初期化
	void Init();
	//ロード
	void Load();
	//ループ
	void Step();
	//描画
	void Draw();

	//各関数処理============================
		//敵２と当たった時の処理（水場を壊す）
	void HitBreakWater();
	//プレイヤーと当たった時の処理(水場を修理)
	void HitRepairWater();
	//水場に水を戻す処理 引数で持っている水の数を取ってくる
	void HitReturnWater(int WaterNum);

	//ゲッター・セッター==================
		//水場生存フラグを取得 true 健在　false 壊れている 
	inline 	bool GetSurvivalFrg() { return m_bSurvival; }
	//ｈｐを取得
	inline float GetWaterHp() { return m_hp; }
	//ｈｐをセット
	inline void SetWaterHP(float HP) { m_hp += HP; }
	//水場の生存状態をセットする
	inline void SetSurvivalFrg(bool Frg) { m_bSurvival = Frg; }
	//敵が水場にヒットしてない　false を代入
	inline void SetHitFrg(bool Frg) { HitFrg = Frg; }
	//水分ゲージを減らす。変数にセットする
	inline void SetWaterGauge() { WaterGauge--; }
	//水分ゲージの数を取得する
	inline int GetWaterGauge() { return WaterGauge; }

	//プレイヤーが取った水の数をセットする 
	inline void SetWaterNum(int WaterNum) { m_iPlayerWater = WaterNum; }

	//ミッション成功か失敗か
	//true:リザルトへ　	false:ミッション成功そのまま
	inline bool GetResultFrg() { return m_bResult; }
	//水場の％が達成できてるかどうか
	inline int  GetWaterClearFrg() { return cNumber.GetNumber(); };

};




