#pragma once

#include "Apple/Apple.h"
#include "Water/Water.h"
#include "Branch/Branch.h"
#include "Straw/Straw.h"
#include "Tree/Tree.h"

class CItemManager
{
public:

	CApple cApple;
	CBranch cBranch;
	//CLeaf cLear;
	//CTent cTent;
	CStraw cStraw;
	CTree cTree;
	CWater cWater;

	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();

	//初期化
	void Init(CPlayer& cPlayer);
	//ロード
	void Load();
	//ループ
	void Step();
	//描画
	void Draw();
	//終了
	void Exit();

	//**各関数**==
		//デバック用当たり判定表示
	void MyDbug();

	//**ゲッター・セッター**==
		//リザルトへ行くか true:リザルトへ false:そのままプレイ
	bool GetResultFrg();
	//わらの個数を返す
	inline int GetStrawNum() { return cStraw.GetItemNum(); }

	//アイテム情報取得
	inline CItemBase& GetApple(int iID) { return cApple.m_cApple[iID]; }
	inline CItemBase& GetStraw(int iID) { return cStraw.m_cStraw[iID]; }
	inline CItemBase& GetTree(int iID) { return cTree.m_cTree[iID]; }

	//水場が達成できているかどうか
	bool GetWaterClearFrg();

};




