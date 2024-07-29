#pragma once
#include "../Player/Player.h"

//宙に浮くブロックの数
const int BROCK_NUM = 3;

class CBrock
{
	int BrockX[BROCK_NUM] = { 0 };			//座標
	int BrockY[BROCK_NUM] = { 0 };			
	int BrockGraph[BROCK_NUM] = { 0 };		//画像
	float time;								//インターバル
public:
	CBrock();
	~CBrock();

	void Init();		//初期化
	void Load();		//ロード
	void Step(CPlayer &cPlayer);//ステップ
	void Draw();		//描画
	void Exit();		//破棄
};





