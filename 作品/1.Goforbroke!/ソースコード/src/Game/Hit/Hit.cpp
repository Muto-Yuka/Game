#include "Hit.h"
#include "../../MyLib/Collision/Collision.h"

//プレイヤーと弾を撃つ敵1の当たり判定=========================================================================================
//====================================================================================================================
//プレイヤーの球と敵（球）
void CHitManager::CheckHitShotToEnemy1(CEnemyManager& cEnemyManager, ShotManager& cShotManager, CApple& cApple)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		//弾情報を取得し、発射されていなければ次へ
		CShot& cPlayerShot = cShotManager.GetPLayerShot(i);
		if (!cPlayerShot.CBaseAnim::IsSurvival()) continue;

		for (int j = 0; j < GUN_ENEMY_NUM; j++)
		{
			//敵情報を取得し、生成されていなければ次へ
			CEnemyBase& cEnemy = cEnemyManager.GetGunEnemy(j);
			if (!cEnemy.CBaseAnim::IsSurvival()) continue;

			//座標と半径を取得
			VECTOR vEnemyPos = cEnemy.GetPosition();
			float fEnemyRadius = cEnemy.GetRadius();
			VECTOR vPlayerShotPos = cPlayerShot.GetPosition();

			//弾の当たり判定をさげる
			vPlayerShotPos.y -= 15;
			//敵の方は当たり判定の中心を半分浮かせる
			vEnemyPos.y += fEnemyRadius;

			//球と球の当たり判定 （敵と球）
			if (CCollision::CheckHitSphereToSphere
			(vPlayerShotPos, vEnemyPos, cPlayerShot.GetRadius(), fEnemyRadius))
			{
				//ここまでくれば当たった
				cPlayerShot.HitCalc();
				cEnemy.HitCalc(cApple);
			}
		}
	}
}
//プレイヤーが敵に当たったとき
void CHitManager::CheckHitPlayerToEnemy1(CEnemyManager& cEnemyManager, CPlayer& cPlayer, CApple& cApple)
{
	//敵の数分回す
	for (int j = 0; j < GUN_ENEMY_NUM; j++)
	{
		//敵情報を取得し、生成されていなければ次へ
		CEnemyBase& cEnemy = cEnemyManager.GetGunEnemy(j);
		if (!cEnemy.CBaseAnim::IsSurvival()) continue;

		VECTOR vEnemyPos = cEnemy.GetPosition();
		float fEnemyRadius = cEnemy.GetRadius();

		//敵の方は当たり判定の中心を半分浮かせる
		vEnemyPos.y += fEnemyRadius;

		//球と球の当たり判定 （敵とプレイヤー）
		if (CCollision::CheckHitSphereToSphere
		(cPlayer.GetPosition(), vEnemyPos, cPlayer.GetRadius(), fEnemyRadius))
		{
			//ここまでくれば当たった
			cPlayer.HitCalc();
			cEnemy.HitCalc(cApple);
			cApple.SetAppleGauge();
		}
	}
}
//敵の弾がプレイヤーに当たった時
void CHitManager::CheckHitEShotToEnemy1(CPlayer& cPlayer, ShotManager& cShotManager, CApple& cApple)
{
	for (int i = 0; i < EM_SHOT_NUM; i++)
	{
		//弾情報を取得し、発射されていなければ次へ
		CShot& cEnemyShot = cShotManager.GetEnemyShot(i);
		if (!cEnemyShot.CBaseAnim::IsSurvival()) continue;

		DrawSphere3D(cPlayer.GetPosition(), cPlayer.GetRadius(), 20, GetColor(255, 255, 255), GetColor(0, 0, 0), FALSE);


		//球と球の当たり判定 （敵と球）
		if (CCollision::CheckHitSphereToSphere
		(cEnemyShot.GetPosition(), cPlayer.GetPosition(), cEnemyShot.GetRadius(), cPlayer.GetRadius()))
		{
			//ここまでくれば当たった
			cPlayer.HitCalc();
			cEnemyShot.HitCalc();
			cApple.SetAppleGauge();

		}
	}
}

//プレイヤーと水場を壊す敵2の当たり判定=========================================================================================
//====================================================================================================================
//敵２と弾(球)
void CHitManager::CheckHitShotToEnemy2(CEnemyManager& cEnemyManager, ShotManager& cShotManager, CApple& cApple)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		//弾情報を取得し、発射されていなければ次へ
		CShot& cPlayerShot = cShotManager.GetPLayerShot(i);
		if (!cPlayerShot.CBaseAnim::IsSurvival()) continue;

		for (int j = 0; j < BREAK_ENEMY_NUM; j++)
		{
			//敵情報を取得し、生成されていなければ次へ
			CEnemyBase& cEnemy = cEnemyManager.GetBreakEnemy(j);
			if (!cEnemy.CBaseAnim::IsSurvival()) continue;

			//座標と半径を取得
			VECTOR vEnemyPos = cEnemy.GetPosition();
			VECTOR vPlayerShotPos = cPlayerShot.GetPosition();

			//弾の当たり判定をさげる
			vPlayerShotPos.y -= 15;
			//敵の方は当たり判定の中心を半分浮かせる
			vEnemyPos.y += cEnemy.GetRadius();

			//球と球の当たり判定 （敵と球）
			if (CCollision::CheckHitSphereToSphere
			(vPlayerShotPos, vEnemyPos, cPlayerShot.GetRadius(), cEnemy.GetRadius()))
			{
				//ここまでくれば当たった
				cPlayerShot.HitCalc();
				cEnemy.HitCalc(cApple);
			}
		}
	}

}
//敵２とプレイヤー
void CHitManager::CheckHitPlayerToEnemy2(CEnemyManager& cEnemyManager, CPlayer& cPlayer, CApple& cApple)
{
	//敵の数分回す
	for (int j = 0; j < BREAK_ENEMY_NUM; j++)
	{
		//敵情報を取得し、生成されていなければ次へ
		CEnemyBase& cEnemy = cEnemyManager.GetBreakEnemy(j);
		if (!cEnemy.CBaseAnim::IsSurvival()) continue;

		VECTOR vEnemyPos = cEnemy.GetPosition();
		float fEnemyRadius = cEnemy.GetRadius();

		//敵の方は当たり判定の中心を半分浮かせる
		vEnemyPos.y += fEnemyRadius;

		//球と球の当たり判定 （敵とプレイヤー）
		if (CCollision::CheckHitSphereToSphere
		(cPlayer.GetPosition(), vEnemyPos, cPlayer.GetRadius(), fEnemyRadius))
		{
			//ここまでくれば当たった
			cPlayer.HitCalc();
			cEnemy.HitCalc(cApple);
			cApple.SetAppleGauge();

		}
	}

}
//敵２と水飲み場
void CHitManager::CheckHitWaterToEnemy2(CEnemyManager& cEnemyManager, CWater& cWater)
{
	for (int j = 0; j < BREAK_ENEMY_NUM; j++)
	{
		//敵情報を取得し、生成されていなければ次へ
		CEnemyBase& cEnemy = cEnemyManager.GetBreakEnemy(j);
		if (!cEnemy.CBaseAnim::IsSurvival()) continue;


		if (CCollision::CheckHitSphereToSphere
		(cEnemy.GetPosition(), cWater.GetPosition(), cEnemy.GetRadius(), cWater.GetRadius()))
		{
			//水場を壊す処理
			cEnemy.BreakWater(cWater);
			cWater.HitBreakWater();
		}
		else
		{
			//敵と水場はヒットしてない
			cWater.SetHitFrg(false);
		}
	}
}


//プレイヤーとアイテム================================================================================================
//====================================================================================================================
//プレイヤーとリンゴの当たり判定
void CHitManager::CheckHitApple(CPlayer& cPlayer, CItemManager& cItemManager)
{

	//リンゴの数分回す
	for (int j = 0; j < APPLE_NUM; j++)
	{

		//りんご情報を取得し、生成されていなければ次へ
		CItemBase& cAppleBase = cItemManager.GetApple(j);
		if (!cAppleBase.GetSurvivalFrg()) continue;

		//アイテムが描画されていないと判定をとらない
		if (!cAppleBase.GetSurvivalFrg())
			return;

		//プレイヤーとリンゴ（球と球）
		if (CCollision::CheckHitSphereToSphere
		(cPlayer.GetPosition(), cAppleBase.GetPosition(), cPlayer.GetRadius(), cAppleBase.GetRadius()))
		{
			//描画しない
			cAppleBase.HitItem();
			//そのほかのヒット処理
			cItemManager.cApple.HitItem();
		}
	}
}
//プレイヤーと水飲み場の当たり判定
void CHitManager::CheckHitWater(CPlayer& cPlayer, CWater& cWater)
{
	////アイテムが描画されていないと判定をとらない
	//if (!cWater.GetSurvivalFrg())
	//	return;

	//プレイヤーと水（球と球）
	if (CCollision::CheckHitSphereToSphere
	(cPlayer.GetPosition(), cWater.GetPosition(), cPlayer.GetRadius(), cWater.GetRadius()))
	{

		cWater.HitRepairWater();
		//プレイヤーが持っている水を水クラスの変数にセット
		cWater.SetWaterNum(cPlayer.GetWaterNum());
		if (cWater.GetSurvivalFrg())
		{
			//水場に水を戻す関数
			cWater.HitReturnWater(cPlayer.GetWaterNum());

		}

		//水場が壊れたら修理する関数
		cPlayer.WatrRepair(cWater);

	}
}
//プレイヤーと木の枝の当たり判定
void CHitManager::CheckHitBranch(CPlayer& cPlayer, CBranch& cBranch)
{

	//アイテムが描画されていないと判定をとらない
	if (!cBranch.GetSurvivalFrg())
		return;


	//プレイヤーと水（球と球）
	if (CCollision::CheckHitSphereToSphere
	(cPlayer.GetPosition(), cBranch.GetPosition(), cPlayer.GetRadius(), cBranch.GetRadius()))
	{
		cBranch.HitItem();
	}

}
//プレイヤーと藁の当たり判定
void CHitManager::CheckHitStraw(CPlayer& cPlayer, CItemManager& cItemManager)
{
	//アイテムの数回す
	for (int j = 0; j < STRAW_NUM; j++)
	{
		//藁情報を取得し、生成されていなければ次へ
		CItemBase& cStrawBase = cItemManager.GetStraw(j);
		if (!cStrawBase.GetSurvivalFrg()) continue;

		//アイテムが描画されていないと判定をとらない
		if (!cStrawBase.GetSurvivalFrg())
			return;

		//プレイヤーとリンゴ（球と球）
		if (CCollision::CheckHitSphereToSphere
		(cPlayer.GetPosition(), cStrawBase.GetPosition(), cPlayer.GetRadius(), cStrawBase.GetRadius()))
		{
			//描画しない
			cStrawBase.HitItem();
			//そのほかのヒット処理
			cItemManager.cStraw.HitItem();
		}
	}
}
//プレイヤーと木の当たり判定
void CHitManager::CheckHitTree(CPlayer& cPlayer, CItemManager& cItemManager)
{
	//木の数分回す
	for (int j = 0; j < TREE_NUM; j++)
	{

		//りんご情報を取得し、生成されていなければ次へ
		CItemBase& cTreeBase = cItemManager.GetTree(j);
		if (!cTreeBase.GetSurvivalFrg()) continue;

		//アイテムが描画されていないと判定をとらない
		if (!cTreeBase.GetSurvivalFrg())
			return;

		//プレイヤーと木（球と球）
		if (CCollision::CheckHitSphereToSphere
		(cPlayer.GetPosition(), cTreeBase.GetPosition(), cPlayer.GetRadius(), cTreeBase.GetRadius()))
		{
			////描画しない
			//cTreeBase.HitItem();
			//そのほかのヒット処理
			cItemManager.cApple.HitItem();
		}
	}

}
//プレイヤーと敵が落とした水の当たり判定
void CHitManager::CheckHitDropWater(CPlayer& cPlayer, CEnemyManager& cEnemyManager, CWater& cWater)
{
	//水の数分回す
	for (int j = 0; j < DROP_WATER_MAXNUM; j++)
	{
		//水情報を取得
		CDropWater& cDropWater = cEnemyManager.GetDropWater(j);

		//座標・半径を取得
		VECTOR vWaterPos = cDropWater.GetPosition();
		float fWaterRadius = cDropWater.GetRadius();

		//水の方は当たり判定の中心を半分浮かせる
		vWaterPos.y += fWaterRadius;

		//アイテムが描画されていないと判定をとらない
		if (!cDropWater.GetSurvival())
			return;


		//球と球の当たり判定 （敵とプレイヤー）
		if (CCollision::CheckHitSphereToSphere
		(cPlayer.GetPosition(), vWaterPos, cPlayer.GetRadius(), fWaterRadius))
		{
			//当たった
			cDropWater.HitCalc(cPlayer);
			//プレイヤーが持っている水を水クラスの変数にセット
			cWater.SetWaterNum(cPlayer.GetWaterNum());
		}
	}

}


//アイテムとアイテム==================================================================================================
//====================================================================================================================
//リンゴと水飲み場
void CHitManager::CheckHitAppleToWater(CApple& cApple, CWater& cWater)
{
	//リンゴと水（球と球）
	if (CCollision::CheckHitSphereToSphere
	(cApple.GetPosition(), cWater.GetPosition(), cApple.GetRadius(), cWater.GetRadius()))
	{
		//即刻リスポーン
	}
}
//木の枝と水飲み場
void CHitManager::CheckHitBranchToWater(CBranch& cBranch, CWater& cWater)
{
	//木の枝と水（球と球）
	if (CCollision::CheckHitSphereToSphere
	(cBranch.GetPosition(), cWater.GetPosition(), cBranch.GetRadius(), cWater.GetRadius()))
	{
		//即刻リスポーン
		cBranch.RespawnApple();
	}
}





