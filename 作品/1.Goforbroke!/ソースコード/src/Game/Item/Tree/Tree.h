#pragma once
#include "../BaseItem.h"

//描画する木の数
#define TREE_NUM (2)

class CTree : public CItemBase
{
private:
	float m_hp;				//体力
	bool HitFrg;			//当たってるかどうか　true当たってる　false当たってない

public:

	//コンストラクタ
	CTree();
	//デストラクタ
	~CTree();

	//初期化
	void Init();
	//ロード
	void Load();
	//ループ
	void Step();
	//描画
	void Draw();

	CItemBase m_cTree[TREE_NUM];

	//**各関数**==
		////プレイヤーと当たった後の処理
		//void HitItem();

	//**ゲッター・セッター**==

};




