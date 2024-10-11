#include "Day1PlayScene.h"


//コンストラクタ
CDay1PlayScene::CDay1PlayScene()
{
	//初期化
	CBaseScene::Init();
}

//デストラクタ
CDay1PlayScene::~CDay1PlayScene()
{
	Exit();
}

//毎フレーム呼ぶ処理
void CDay1PlayScene::Loop()
{
	cMission.SetDay1Scene();
	CBaseScene::Loop();

}

//描画処理（影あり）
void CDay1PlayScene::ShadowDraw()
{
	CBaseScene::Draw();

}

//描画処理（影なし）
void CDay1PlayScene::Draw()
{
	cMission.Draw();
	cScreen.Day1Draw(m_eSceneID);

//それぞれの当たり判定（球）表示
	cItemManager.MyDbug();

}

//初期化
void CDay1PlayScene::Init()
{
	CBaseScene::Init();
}

//終了処理
void CDay1PlayScene::Exit()
{
	CBaseScene::Exit();
}

void CDay1PlayScene::Next()
{
	Exit();
	m_eSceneID = SCENE_INIT;

}

//データロード
void CDay1PlayScene::Load()
{
	CBaseScene::Load();
}


//毎フレーム呼ぶ処理
//午前の処理　アイテム集め。ミッション。
void CDay1PlayScene::AmStep()
{

	CBaseScene::AmStep();

}

//午後の処理
void CDay1PlayScene::PmStep()
{


	CBaseScene::PmStep();

}

bool CDay1PlayScene::GetClearFlg()
{
	//終了処理まですべて終わったらクリアフラグ
	if (m_eSceneID == SCENE_NEXT)
		return true;
	else if (m_eSceneID != SCENE_NEXT)
		return false;


	return false;
}








