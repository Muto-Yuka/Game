#pragma once

#include "../../Character/Enemy/EnemyManager.h"
#include "../../Game/shot/shotManager.h"
#include "../../Character/Player/Player.h"
#include "../../Game/Item/ItemManager.h"


#define DRAW_COLLISION (1)

class CHitManager
{
public:

	//プレイヤーと弾を撃つ敵(敵１)の当たり判定==========
	//==================================================

		//敵１とプレイヤーの弾
	static void CheckHitShotToEnemy1(CEnemyManager& cEnemyManager, ShotManager& cShotManager, CApple& cApple);
	//敵１とプレイヤー
	static void CheckHitPlayerToEnemy1(CEnemyManager& cEnemyManager, CPlayer& cPlayer, CApple& cApple);
	//敵１の弾とプレイヤー
	static void CheckHitEShotToEnemy1(CPlayer& cPlayer, ShotManager& cShotManager, CApple& cApple);

	//プレイヤーと水場を壊す敵(敵２)の当たり判定==========
	//====================================================

		//敵２とプレイヤーの弾
	static void CheckHitShotToEnemy2(CEnemyManager& cEnemyManager, ShotManager& cShotManager, CApple& cApple);
	//敵２とプレイヤー
	static void CheckHitPlayerToEnemy2(CEnemyManager& cEemyManager, CPlayer& cPlayer, CApple& cApple);
	//敵２と水飲み場
	static void CheckHitWaterToEnemy2(CEnemyManager& cEnemyManager, CWater& cWater);

	//プレイヤーとアイテム================
	//====================================

		//リンゴとプレイヤー
	static void CheckHitApple(CPlayer& cPlayer, CItemManager& cItemManager);
	//水飲み場とプレイヤー
	static void CheckHitWater(CPlayer& cPlayer, CWater& cWater);
	//木の枝とプレイヤー
	static void CheckHitBranch(CPlayer& cPlayer, CBranch& cBranch);
	//わらとプレイヤー
	static void CheckHitStraw(CPlayer& cPlayer, CItemManager& cItemManager);
	//プレイヤーと木の当たり判定
	static void CheckHitTree(CPlayer& cPlayer, CItemManager& cItemManager);
	//プレイヤーと敵が落とした水の当たり判定
	static void CheckHitDropWater(CPlayer& cPlayer, CEnemyManager& cEnemyManager, CWater& cWater);

	//アイテムとアイテム==================
	//====================================

		//リンゴと水飲み場
	static void CheckHitAppleToWater(CApple& cApple, CWater& cWater);
	//木の枝と水飲み場
	static void CheckHitBranchToWater(CBranch& cBranch, CWater& cWater);


};

