#include "Day2PlayScene.h"

//コンストラクタ
CDay2PlayScene::CDay2PlayScene()
{
	//初期化
	CBaseScene::Init();

}

//デストラクタ
CDay2PlayScene::~CDay2PlayScene()
{
	Exit();
}


//毎フレーム呼ぶ処理
void CDay2PlayScene::Loop()
{

	cMission.SetDay2Scene();

	CBaseScene::Loop();


}



//描画処理（影あり）
void CDay2PlayScene::ShadowDraw()
{
	CBaseScene::Draw();

}
//描画処理（影なし）
void CDay2PlayScene::Draw()
{
	cMission.Draw();
	cScreen.Day2Draw(m_eSceneID);
	cItemManager.MyDbug();

}
//初期化
void CDay2PlayScene::Init()
{

	CBaseScene::Init();
}

//終了処理
void CDay2PlayScene::Exit()
{
	CBaseScene::Exit();

}
void CDay2PlayScene::Next()
{
	CBaseScene::Next();
}


//データロード
void CDay2PlayScene::Load()
{
	CBaseScene::Load();
}


//毎フレーム呼ぶ処理
//午前の処理　アイテム集め。ミッション。
void CDay2PlayScene::AmStep()
{

	CBaseScene::AmStep();

}

//午後の処理
void CDay2PlayScene::PmStep()
{

	CBaseScene::PmStep();

}

bool CDay2PlayScene::GetClearFlg()
{
	//終了処理まですべて終わったらクリアフラグ
	if (m_eSceneID == SCENE_NEXT)
		return true;
	else if (m_eSceneID != SCENE_NEXT)
		return false;


	return false;

}

//水場％が達成できているか　true:達成　false:未達成
bool CDay2PlayScene::GetWaterClear()
{
	if (cItemManager.GetWaterClearFrg())
		return true;
	

	return false;
}



