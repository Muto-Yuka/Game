#pragma once
#include "../Player/Player.h"

//26ブロック分横に並べる
const int GROUND_NUM = 26;

class CBackGround
{
	int bgSkyHandle[2] = { 0 };
	int bgSkyX[2] = { 0 };
	int bgSkyY[2] = { 0 };

public:
	CBackGround();
	~CBackGround();

	void Init();		//初期化
	void Load();		//ロード
	void Step(CPlayer& cPlayer);//ステップ
	void Exit();		//破棄
	void Draw();		//描画
};




