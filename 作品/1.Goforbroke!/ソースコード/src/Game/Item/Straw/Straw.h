#pragma once
#include "../BaseItem.h"
#include "../../../Character/Player/Player.h"

//同時に出現するアイテムの数
#define STRAW_NUM		(5)

class CStraw : public CItemBase
{
private:
	int m_iItemNum;		//取得したアイテムの数

public:

	//コンストラクタ
	CStraw();
	//デストラクタ
	~CStraw();

	//初期化
	void Init();
	//ロード
	void Load();
	//ループ
	void Step();
	//描画
	void Draw();

	CItemBase m_cStraw[STRAW_NUM];

	//**各関数**==
		//プレイヤーと当たった後の処理
	void HitItem();
	////わらのリスポーン処理
	//void Respawn();

//**ゲッター・セッター**==
	//取得したアイテムの数を返す
	inline int GetItemNum() { return m_iItemNum; }
};




