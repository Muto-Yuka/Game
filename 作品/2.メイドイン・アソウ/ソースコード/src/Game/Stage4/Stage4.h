#pragma once
#include "../GameBase.h"
#include "Player4/Player4.h"
#include "Pop/Pop.h"

//ポップコーン
class CStasge4 : public CGameBase
{
	CPlayer4	cPlayer4;
	CPop		cPop;
public:
	CStasge4();
	~CStasge4();

	void Init();		//初期化
	void Load();		//ロード
	int  Step();		//ステップ
	void Exit();		//破棄
	void Draw();		//描画

	//リザルト情報を返す 0:待機　1:クリア　2:ゲームオーバー
	int GetResult();

};




