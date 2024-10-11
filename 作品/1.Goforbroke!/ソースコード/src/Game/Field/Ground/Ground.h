#pragma once
#include <DxLib.h>

class CGround
{
	int m_iHndl;		//モデルハンドル
	bool m_isHitFlag;	//地面にヒット　true:している  false:していない

public:
	CGround();
	~CGround();

	void Init();		//初期化
	void Load();		//ロード
	void Loop();		//ループ
	void Draw();		//描画
	void Exit();		//破棄

	//当たり判定用（相手の座標と半径）return:押し戻す距離と方向
	VECTOR	HitCheck(VECTOR anotherPos, float anotherRadius);

};



