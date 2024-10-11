#include "SceneBase.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Sound/Sound.h"

//毎ループ
void CBaseScene::Loop()
{
	//関数ポインタを宣言し関数をscene配列に入れる
	void (CBaseScene:: * scene[])() = {
		 &CBaseScene::Init,& CBaseScene::Load,& CBaseScene::AmStep,& CBaseScene::PmStep,& CBaseScene::Exit,& CBaseScene::Next
	};
	//idに合わせて処理を実行
	(this->*scene[m_eSceneID])();
}


//描画処理
void CBaseScene::Draw()
{
	cFieldManager.Draw(m_eSceneID);
	cPlayer.CBaseAnim::Draw();
	cShotManager.Draw();
	cEnemyManager.Draw();
	cItemManager.Draw();


}

//初期化
void CBaseScene::Init()
{
	m_eSceneID = SCENE_INIT;

	cMission.Init();
	//カメラ初期化
	cCameraManager.SetNearFar(1.0f, 5000.0f);

	//プレイヤー初期化
	cPlayer.Init();
	cFieldManager.Init();
	cShotManager.Init();
	cEnemyManager.Init(cItemManager.cApple);
	cScreen.Init();
	//cItemManager.Init();
	cItemManager.Init(cPlayer);

	m_eSceneID = SCENE_LOAD;


}

//終了処理
void CBaseScene::Exit()
{
	if (!CFade::GetInstance()->IsEnd()) return;

	CSound::AllStop();
	cMission.Exit();
	cPlayer.CBaseAnim::Exit();
	cFieldManager.Exit();
	cShotManager.Exit();
	cEnemyManager.Exit();
	cScreen.Exit();
	//cItemManager.Exit();
	cItemManager.Exit();

	m_eSceneID = SCENE_NEXT;

}

void CBaseScene::Next()
{
	Exit();
	CFade::DeleteInstance();
	m_eSceneID = SCENE_INIT;

}

//データロード
void CBaseScene::Load()
{

	cMission.Load();
	cPlayer.Load();
	cFieldManager.Load();
	cShotManager.Load();
	cEnemyManager.Load();
	cScreen.Load();
	//cItemManager.Load();
	cItemManager.Load();
	CSound::Play(CSound::SOUND_PLAY, DX_PLAYTYPE_LOOP);


	m_eSceneID = SCENE_AM_STEP;
	CFade::GetInstance()->Request(4.0f, true);

}


//毎フレーム呼ぶ処理
//午前の処理　アイテム集め。ミッション。
void CBaseScene::AmStep()
{

	cMission.Step(cItemManager);
	cPlayer.Loop(cShotManager, cItemManager.cWater);
	cPlayer.CPlayer::Update();
	cShotManager.Step();
	cScreen.Step(m_eSceneID,cPlayer);
	cItemManager.Step();
	cScreen.SetPlayerHp(cPlayer.GetPlayerHP());
	//当たり判定
	Collision();
	cFieldManager.Loop();

	//カメラ更新処理
	cCameraManager.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());

	if (cScreen.GetAmTimeLimit() == 0 || cPlayer.GetPlayerHP() == 0)
	{
		m_eSceneID = SCENE_PM_STEP;

	}

	//waterクラスからゲットしたｈｐをscreenクラスへセット
	cScreen.SetWaterHp(cItemManager.cWater.GetWaterHp());
}

//午後の処理
void CBaseScene::PmStep()
{

	cMission.Step(cItemManager);
	

	//プレイヤー更新処理
	if (cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		cPlayer.Loop(cShotManager, cItemManager.cWater);
		cPlayer.CPlayer::Update();

		cShotManager.Step();
		cEnemyManager.Step(cPlayer, cShotManager, cItemManager.cWater, cScreen);

		cItemManager.Step();

		cScreen.Step(m_eSceneID, cPlayer);

		cScreen.SetPlayerHp(cPlayer.GetPlayerHP());

		//プレイイヤーのｈｐがなくなれば次のシーンへ
		if (cEnemyManager.GetNextDayFrg())
		{
			cEnemyManager.SetNextDayFrg(false);
			m_eSceneID = SCENE_EXIT;
			CFade::GetInstance()->Request(4.0f, false);

		}
		//当たり判定
		Collision();
	}
	//カメラ更新処理
	cCameraManager.Step(cPlayer.GetPosition(), cPlayer.GetRotateY());

	//waterクラスからゲットしたｈｐをscreenクラスへセット
	cScreen.SetWaterHp(cItemManager.cWater.GetWaterHp());
}

//当たり判定処理=====================================================================================
void CBaseScene::Collision()
{
//弾を撃つ敵の当たり判定
	CHitManager::CheckHitShotToEnemy1(cEnemyManager, cShotManager, cItemManager.cApple);						//弾を撃つ(敵１)と弾
	CHitManager::CheckHitPlayerToEnemy1(cEnemyManager, cPlayer, cItemManager.cApple);	//敵１とプレイヤー
	CHitManager::CheckHitEShotToEnemy1(cPlayer, cShotManager, cItemManager.cApple);		//敵1の弾とプレイヤー
//水場を壊す敵の当たり判定
	CHitManager::CheckHitShotToEnemy2(cEnemyManager, cShotManager, cItemManager.cApple);						//水場を壊す敵(2)と弾
	CHitManager::CheckHitPlayerToEnemy2(cEnemyManager, cPlayer, cItemManager.cApple);	//敵２とプレイヤー
	CHitManager::CheckHitWaterToEnemy2(cEnemyManager, cItemManager.cWater);				//敵２と水場		
//プレイヤーとアイテムの当たり判定
	CHitManager::CheckHitApple(cPlayer, cItemManager);									//プレイヤーとりんご
	CHitManager::CheckHitBranch(cPlayer, cItemManager.cBranch);							//プレイヤーと木の枝
	CHitManager::CheckHitWater(cPlayer, cItemManager.cWater);							//プレイヤーと水飲み場
	CHitManager::CheckHitStraw(cPlayer, cItemManager);									//プレイヤーとわら
	CHitManager::CheckHitTree(cPlayer, cItemManager);									//プレイヤーと木
	CHitManager::CheckHitDropWater(cPlayer, cEnemyManager, cItemManager.cWater);

//アイテムとアイテムの当たり判定
	CHitManager::CheckHitAppleToWater(cItemManager.cApple, cItemManager.cWater);		//リンゴと水飲み場
	CHitManager::CheckHitBranchToWater(cItemManager.cBranch, cItemManager.cWater);		//木の枝と水飲み場

//フィールドの当たり判定
	cPlayer.ReflectCollision(cFieldManager.HitCheck(cPlayer.GetCenter(), cPlayer.GetRadius()));

}






