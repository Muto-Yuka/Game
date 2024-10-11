#pragma once
#include "../Player/Player.h"

class CFlag
{
	int FlagX = 0, FlagY = 0;//座標
	int FlagGraph = 0;     //画像
	bool life = 0;
public:
	void Init();		//初期化
	void Load();		//ロード
	void Step(CPlayer& cPlayer);	//ステップ
	void Draw();		//描画
	void Exit();		//破棄
	void Hit();
};






