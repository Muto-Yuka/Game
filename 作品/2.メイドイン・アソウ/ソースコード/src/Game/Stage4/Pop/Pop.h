#pragma once

//クリアに飛ぶ回数
#define POP_FULL (20)

class CPop
{
	int PopX, PopY;//座標
	int PopGraph[4];     //ポップコーン画像
	bool nothing;
	bool little;
	bool half;
	bool full;
public:
	CPop();
	~CPop();

	void Init();		//初期化
	void Load();		//ロード
	void Step(int num);		//ステップ
	void Draw();		//描画
	void Exit();		//破棄
};



