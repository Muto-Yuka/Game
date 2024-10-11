#pragma once

class CPlayer4
{
	enum tag_number
	{
		one,
		two,
		three,
		four,
	};

	int PlayerX, PlayerY;//座標
	int PlayerGraph;     //プレイヤー画像
	bool fast;
	bool second;
	bool third;
	bool forth;
	bool turn;
	int num;
	int times;
public:
	CPlayer4();
	~CPlayer4();

	void Init();		//初期化
	void Load();		//ロード
	void Update();
	void Step();		//ステップ
	void Draw();		//描画
	void Exit();		//破棄

	//時間を取得
	inline int GetTime() { return  times;}

};




