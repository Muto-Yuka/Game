#pragma once
#include "../BaseItem.h"

class CBranch : public CItemBase
{
public:

	//コンストラクタ
	CBranch();
	//デストラクタ
	~CBranch();

	//初期化
	void Init();
	//ロード
	void Load();
	//ループ
	void Step();

	//プレイヤーと当たった後の処理
	void HitItem();
	//リスポーン処理
	void RespawnApple();


};




