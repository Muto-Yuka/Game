#pragma once
#include "../Player3/Player3.h"
#include "../HitPoint/HitPoint.h"

class CDrop
{
	int DropX, DropY, DropY2;//座標
	int DropGraph;     //プレイヤー画像
	bool life;
	float time;

public:
	CDrop();
	~CDrop();

	void Init();		//初期化
	void Load();		//ロード
	void Step(CPlayer3& cPlayer);//ステップ
	void Draw();		//描画
	void Exit();		//破棄

	//１：クリア　２：ゲームオーバー
	int Hit(CHitPoint &cHitPoint);
};





