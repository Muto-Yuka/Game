#pragma once

class CScore 
{
public:
	//初期化
	void InitScore();							
	//ロード
	void LoadScore();						
	//２ｄ描画
	void Draw2dScore();							
	//３ｄ描画
	void Draw3dScore(VECTOR DrawPos, float Size);	
	//画像破棄
	void ExitScore();							
	//加算する
	void AddScore(int score);						
	//強制的にセットする
	void SetScore(int score);						
	//取得する
	int GetScore();								

};


