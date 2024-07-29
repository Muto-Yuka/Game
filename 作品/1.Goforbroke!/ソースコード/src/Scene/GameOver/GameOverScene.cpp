#include "GameOverScene.h"
#include <DxLib.h> 
#include "../../MyLib/Sound/Sound.h"
#include "../../MyLib/Fade/Fade.h"

static const char PATH[] = { "data/Scene/GameOver/GameOver.png" };
static const char LACK_PATH[] = { "data/Scene/GameOver/WaterGM2.png" };
static const char PLACE_PATH[] = { "data/Scene/GameOver/WaterGM1.png" };

//コンストラクタ
CGameOverScene::CGameOverScene()
{
	Init();
}

//デストラクタ
CGameOverScene::~CGameOverScene()
{
	Exit();
	CFade::DeleteInstance();
}

//初期化
void CGameOverScene::Init(void)
{
	m_iHndl = -1;		//初期化
	m_iWaterlack = -1;
	m_iWaterplace = -1;
	Load();

}

//データロード
void CGameOverScene::Load()
{
	//通常ゲームオーバー
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(PATH);
	}
	//水分不足
	if (m_iWaterlack == -1)
	{
		m_iWaterlack = LoadGraph(LACK_PATH);
	}
	//水場未達成
	if (m_iWaterplace == -1)
	{
		m_iWaterplace = LoadGraph(PLACE_PATH);
	}
	CFade::GetInstance()->Request(4.0f, true);

}

//毎フレーム呼ぶ処理
void CGameOverScene::Step()
{
	if (!CFade::GetInstance()->IsEnd())
		return;


}

//描画処理
void CGameOverScene::Draw()
{
	//通常
	DrawGraph(0, 0, m_iHndl, true);
}

//水分不足　描画
void CGameOverScene::LackDraw()
{

	//水分不足
	DrawGraph(0, 0, m_iWaterlack, true);

}

//水場未達成　描画
void CGameOverScene::PlaceDraw()
{

	//未達成
	DrawGraph(0, 0, m_iWaterplace, true);

}

//終了処理
void CGameOverScene::Exit()
{
	CSound::AllStop();
	DeleteGraph(m_iHndl);
	DeleteGraph(m_iWaterplace);
	DeleteGraph(m_iWaterlack);

	CFade::DeleteInstance();

}
