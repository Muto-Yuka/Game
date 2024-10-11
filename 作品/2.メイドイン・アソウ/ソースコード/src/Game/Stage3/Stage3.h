#pragma once
#include "../GameBase.h"
#include "BackGround3/BackGround3.h"
#include "Player3/Player3.h"
#include "HitPoint/HitPoint.h"
#include "Drop/Drop.h"

//目薬をさす
class CStasge3 : public CGameBase
{
	CBackGround3	cBackGround;	//背景
	CPlayer3		cPlayer3;		//プレイヤー
	CHitPoint		cHitPoint;		//ヒットポイント
	CDrop			cDrop;			//落とす水

public:
	CStasge3();
	~CStasge3();

	void Init();		//初期化
	void Load();		//ロード
	int  Step();		//ステップ
	void Exit();		//破棄
	void Draw();		//描画

	//リザルト情報を返す 0:待機　1:クリア　2:ゲームオーバー
	int GetResult();

};




