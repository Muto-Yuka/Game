#include "Tree.h"
//3dモデル
static const char MODEL_PATH[] = { "data/Game/Item/Tree/Tree.x" };

//出現させるｘの範囲
#define DRAW_ITEM_X	(400)
//出現させるｚの範囲
#define DRAW_ITEM_Z (400)
//アイテムの半径
#define ITEM_RADIUS (5.0f)
//木の体力
#define TREE_HP	(50.f)

//コンストラクタ
CTree::CTree()
{


}

//デストラクタ
CTree::~CTree()
{
	Exit();
}

//初期化
void CTree::Init()
{
	for (int i = 0; i < TREE_NUM; i++)
	{
		//半径初期化
		m_cTree[i].Init(ITEM_RADIUS);
		//木の体力初期化
		m_cTree[i].SetHp(TREE_HP);
		//HitFrg = false;	//敵が当たってない

	}

}

//ロード
void CTree::Load()
{



	//オリジナルモデルを読み込み
	int iHndl = MV1LoadModel(MODEL_PATH);

	//モデルの複製
	for (int i = 0; i < TREE_NUM; i++)
	{
		//複製する
		m_cTree[i].DuplicateLoad(iHndl);


	}

	//座標をセット
	m_cTree[0].SetInitPos(VGet(200.f, 0.f, 30.f));
	m_cTree[1].SetInitPos(VGet(-200.f, 0.f, 30.f));

	//オリジナルモデル削除
	MV1DeleteModel(iHndl);


}

//ループ
void CTree::Step()
{
	for (int i = 0; i < TREE_NUM; i++)
	{
		//通常ループ
		m_cTree[i].Step();
	}

}

//描画
void CTree::Draw()
{


	//３ｄモデル描画
	for (int i = 0; i < TREE_NUM; i++)
		m_cTree[i].Draw();

}
//
////水場を壊す
//void CTree::HitBreakWater()
//{
//
//
//}
//
////水場を修理する
//void CTree::HitRepairWater()
//{
//
//
//}
//


