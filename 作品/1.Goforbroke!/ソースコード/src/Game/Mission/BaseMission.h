#pragma once
#include <DxLib.h>

//食料ゲージの数
#define GAUGE_NUM	(8)		

//ミッション内容文字の初期座標
#define MISSION_WORD_X		(350)	
#define MISSION_WORD_Y		(200)	

class CBaseMission
{
protected:
	int m_iOnHndl[GAUGE_NUM];		//2D食料ゲージ画像ハンドル(うえに描画)
	int m_iUnderHndl[GAUGE_NUM];	//2D食料ゲージ画像ハンドル（下に影として描画）
	int m_iDrawNum;					//2D表示する食料・水の数
	int m_iMissionCnt;				//ミッション中の時間カウント
	int m_iWordX, m_iWordY;			//文字を移動させるための座標を入れる変数
	int FontHandle;					//一時的に文字を変えるためのフォントハンドル
	int m_iDrawPictureY;			//ミッション文字のY座標

	bool m_bClear;					//リザルトへ行くかどうか
	bool HitFlg;					//アイテムにヒットしたか

public:
	//コンストラクタ
	CBaseMission();

	//初期化
	void Init();
	//ループ
	void Step();
	//常に描画
	void AlwaysDraw();
	//終了
	void Exit();

	//アイテムに当たったか
	bool GetHitFlg() { return HitFlg; }
};






