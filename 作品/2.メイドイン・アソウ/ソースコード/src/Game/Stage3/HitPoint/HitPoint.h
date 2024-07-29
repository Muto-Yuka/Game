#pragma once

class CHitPoint
{
	int EyeX, EyeY;	//座標
	int EyeGraph;		//プレイヤー画像
public:
	CHitPoint();
	~CHitPoint();

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Draw();		//描画
	void Exit();		//破棄
	void Hit();

//ゲッター
	int HitX() { return EyeX; }
	int HitY() { return EyeY; }

};




