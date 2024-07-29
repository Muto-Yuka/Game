#pragma once
#include "DxLib.h"

class CNumber
{
public:
	//	初期化
	void InitNumber(void);
	//	画像のロード
	void LoadNumber(void);
	//	更新
	void UpdateNumber(void);
	//	２ｄ描画
	void Draw2dNumber(void);
	//  ３ｄ描画 引数で表示する座標を受け取る
	void Draw3dNumber(VECTOR DrawPos, float Size);
	//	画像破棄
	void ExitNumber(void);

	//	加算する
	void AddNumber(int score);
	//	強制的にセットする
	void SetNumber(int score);
	//	取得する
	int GetNumber(void);

};


