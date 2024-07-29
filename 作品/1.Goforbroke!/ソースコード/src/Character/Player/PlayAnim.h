#pragma once
#include "../../MyLib/BaseAnim/BaseAnim.h"

class CPlayAnim : public CBaseAnim
{
	//アニメーションの種類
	enum PLAY_ANIM {
		ANIMID_WAIT,		//待機
		ANIMID_WALK,		//歩き
		ANIMID_RUN,			//走り
		ANIMID_SIDEWALK,	//左右移動
		ANIMID_TAKE,		//ものをとる動作

		ANIMID_NUM			//アニメ総数
	};

public:
	static int Key;
	static DINPUT_JOYSTATE input;		//コントローラー情報

	CPlayAnim();

	void Init();	//初期化
	void Load();	//ロード
	void Loop();	//ループ
	void Update();	//更新

	void AnimLoop();		//アニメーションループ
	void ExecWait();		//待機アニメ関数実行
	void ExecWalk();		//歩きアニメ関数実行
	void ExecRun();			//走りアニメ関数実行
	void ExecSideWalk();	//左右移動アニメ関数実行
	void ExecTake();		//取得アニメーション実行

};




