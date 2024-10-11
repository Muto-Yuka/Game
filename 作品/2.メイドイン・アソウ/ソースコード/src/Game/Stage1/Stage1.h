#pragma once
#include "../GameBase.h"
#include "BackGround/BackGround.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Brock/Brock.h"
#include "Flag/Flag.h"

//ジャンプし続けているキャラを左右に動かしステージを進む
class CStage1 : public CGameBase
{
	CBackGround	cBackGround;	//背景
	CPlayer		cPlayer;		//プレイヤー
	CEnemy		cEnemy;			//敵
	CBrock		cBrock;			//ブロック
	CFlag		cFlag;			//ゴール（旗）

public:
	CStage1();
	~CStage1();

	void Init();		//初期化
	void Load();		//ロード
	int  Step();		//ステップ
	void Exit();		//破棄
	void Draw();		//描画

	//リザルト情報を返す 0:待機　1:クリア　2:ゲームオーバー
	int GetResult();

};




