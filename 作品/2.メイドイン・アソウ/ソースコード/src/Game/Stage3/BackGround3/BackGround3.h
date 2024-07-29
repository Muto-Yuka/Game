#pragma once

class CBackGround3
{
	int bgSkyHandle;
public:
	CBackGround3();
	~CBackGround3();

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Draw();		//描画
	void Exit();		//破棄
	void Hit();
};