#pragma once

class CPlayer
{
	int PlayerX, PlayerY;//座標
	int PlayerGraph;     //プレイヤー画像
	int Deadpath;		//リスポーン画像
	int Respawn;		 //プレイヤーリスポーン
	int RespawnTime;	//リスポーンできるまでの時間
	float JumpPower;     //ジャンプ力
	float time;          //インターバル
	bool life;			//生存フラグ
	bool BrockHit;		//ブロックとHITしたか
	bool Clear,Gameover;

	const int MaxFrame = 10;
	int Ani_image[10];
	int Frame = 0;
	int Frame_adjust = 0;

public:	
	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Draw();		//描画
	void Exit();		//破棄

	void Hit();
	void Jump();		//ジャンプ処理

//ゲッター
	inline int GetPlayerX() { return PlayerX; }		//X座標
	inline int GetPlayerY() { return PlayerY; }		//Y座標
	inline bool GetClear() { return Clear; }		//true:Clear　false:待機
	inline bool GetGameover() { return Gameover; }	//true:Gameover　false:待機
	inline bool GetLife() { return life; }			//ライフ取得
	//セッター
	inline void SetJump(float power) { JumpPower = power; }	//ジャンプパワー
	inline void SetPlayerLife(bool Frg) { life = Frg; }		//プレイヤーHP
	inline void SetPlayerHit(bool Frg) { BrockHit = Frg; }	//Hitしたか
	inline void SetClear() { Clear = true; }
};




