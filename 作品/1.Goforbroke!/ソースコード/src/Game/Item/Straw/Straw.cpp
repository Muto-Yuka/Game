#include "Straw.h"

//パス
static const char MODEL_PATH[] = { "data/Game/Item/Straw/Straw.x" };

//出現させるｘの範囲
#define DRAW_ITEM_X	(200)
//出現させるｚの範囲
#define DRAW_ITEM_Z (200)
//アイテムの半径
#define ITEM_RADIUS (3)
//出現させるアイテムの数
#define ITEM_NUM (2)

//コンストラクタ
CStraw::CStraw()
{

}

//デストラクタ
CStraw::~CStraw()
{
	Exit();

	for (int i = 0; i < STRAW_NUM; i++)
		m_cStraw[i].Exit();
}

//初期化
void CStraw::Init()
{
	for (int i = 0; i < STRAW_NUM; i++)
	{

		m_cStraw[i].Init(ITEM_RADIUS);
	}

	m_iItemNum = 0;
}

//ロード
void CStraw::Load()
{
	//オリジナルモデルを読み込み
	int iHndl = MV1LoadModel(MODEL_PATH);

	//モデルの複製
	for (int i = 0; i < STRAW_NUM; i++)
	{
		//複製する
		m_cStraw[i].DuplicateLoad(iHndl, DRAW_ITEM_X, DRAW_ITEM_Z);
	}

	//オリジナルモデル削除
	MV1DeleteModel(iHndl);

}

//ループ
void CStraw::Step()
{

	for (int i = 0; i < STRAW_NUM; i++)
	{
		//通常ループ
		m_cStraw[i].Step();
		//リスポーンするループ処理
		m_cStraw[i].RespawnStep(DRAW_ITEM_X, DRAW_ITEM_Z, STRAW_NUM);
	}
}

//描画
void CStraw::Draw()
{
	//３ｄモデル描画
	for (int i = 0; i < STRAW_NUM; i++)
		m_cStraw[i].Draw();

}

//プレイヤーかアイテム当たった後の処理
void CStraw::HitItem()
{
	//描画しない
	m_bSurvival = false;
	//取得したアイテム変数を+1
	m_iItemNum++;


}

