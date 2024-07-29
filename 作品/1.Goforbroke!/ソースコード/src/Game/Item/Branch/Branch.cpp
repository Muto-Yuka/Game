#include "Branch.h"

static const char MODEL_PATH[] = { "data/Game/Item/Branch/Branch.x" };
//出現させるｘの範囲
#define DRAW_ITEM_X	(200)
//出現させるｚの範囲
#define DRAW_ITEM_Z (200)
//アイテムの半径
#define ITEM_RADIUS (3)
//出現させるアイテムの数
#define ITEM_NUM (2)

//コンストラクタ
CBranch::CBranch()
{
	Init();
}

//デストラクタ
CBranch::~CBranch()
{
	Exit();
}

//初期化
void CBranch::Init()
{
	CItemBase::Init(ITEM_RADIUS);
	CItemBase::m_fRadius = ITEM_RADIUS;
}

//ロード
void CBranch::Load()
{

	if (m_iHndl == -1)
	{
		m_iHndl = MV1LoadModel(MODEL_PATH);
	}

	CItemBase::Load(DRAW_ITEM_X, DRAW_ITEM_Z);

}

//ループ
void CBranch::Step()
{
	CItemBase::Step();

	//ヒットしてから時間を図る
	if (m_bSurvival == false)
		m_RespawnTime++;

	//リンゴにあたって描画されなくなりリスポーン時間に到達したら
	if (m_bSurvival == false && m_RespawnTime % 240 == 0)
	{
		//リスポーンする
		RespawnApple();
	}
}

//プレイヤーかアイテム当たった後の処理
void CBranch::HitItem()
{
	//描画しない
	m_bSurvival = false;


}

//リスポーン関数
void CBranch::RespawnApple()
{
	//再度ランダムで出現する座標を取得
	m_vPos = VGet((float)GetRand(DRAW_ITEM_X), 0, (float)GetRand(DRAW_ITEM_Z));
	//再び描画
	m_bSurvival = true;
	m_RespawnTime = 0;



}

