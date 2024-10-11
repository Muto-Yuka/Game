#pragma once
#include "../BaseItem.h"
#include "../../../Character/Player/Player.h"

//同時に出現するアイテムの数
#define APPLE_NUM		(5)


class CApple : public CItemBase
{
private:
	int m_iHp;						//食料・体力
	int m_iOnHndl[PLAYER_HP];		//2D食料ゲージ画像ハンドル(うえに描画)
	int m_iUnderHndl[PLAYER_HP];	//2D食料ゲージ画像ハンドル（下に影として描画）
	int StartTime;					//スタート時間
	int MaxPlayerHp;				//プレイヤーのマックスｈｐ
	bool ResultFrg;					//リザルトに行くかどうか　true:リザルト, false 何もしない
	int m_iWaitCnt;					//アイテムの出現時間管理


public:

	//コンストラクタ
	CApple();
	//デストラクタ
	~CApple();

	//初期化
	void Init(CPlayer &cPlayer);
	//ロード
	void Load();
	//ループ
	void Step();
	//描画
	void Draw();

	CItemBase m_cApple[APPLE_NUM];

//**各関数**==

	//プレイヤーと当たった後の処理
	void HitItem();

//**ゲッター・セッター**==

	//食料ゲージを減らす。変数にセットする
	inline void SetAppleGauge() { m_iHp--; }

	//ミッション成功か失敗か
	//true:リザルトへ　	false:ミッション成功そのまま
	inline bool GetResultFrg() { return ResultFrg; }

};




