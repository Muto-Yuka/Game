#pragma once

class CPlayer3
{
	//手
	int HandX, HandY;	 //座標
	int HandGraph;		 //プレイヤー画像
	bool offer;			 //手を止めるか
	bool left;			
	bool right;
	//プレイヤー（目）
	int HeadX, HeadY;//座標
	int headGraph;     //プレイヤー画像

public:
	CPlayer3();
	~CPlayer3();

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Draw();		//描画
	void Exit();		//破棄
	void Hit();

//ゲッター
	int GetHandX() { return HandX; }
	int GetHandY() { return HandY; }
	bool GetOffer() { return offer; }


};



