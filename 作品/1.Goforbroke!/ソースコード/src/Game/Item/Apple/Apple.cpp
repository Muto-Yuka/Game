#include "Apple.h"

//２ｄイラストのファイルパス
#define ON_APPLES_PATH	("data/Game/Mission/Apple/OnApple.png")
#define UNDER_APPLES_PATH	("data/Game/Mission/Apple/UnderApple.png")
//モデルパス
static const char MODEL_PATH[] = { "data/Game/Item/Apple/Apple.x" };

//出現させるｘの範囲
#define DRAW_ITEM_X	(400)
//出現させるｚの範囲
#define DRAW_ITEM_Z (400)
//アイテムの半径
#define ITEM_RADIUS (3)
//食料ゲージのｙ座標
#define APPLE_2D_Y		(600)		
//おなかが減る時間
#define HUNGRY_TIME		(600)	
//アイテムの出現時間
#define WAIT_TIME		(120)

//コンストラクタ
CApple::CApple()
{

}

//デストラクタ
CApple::~CApple()
{
	Exit();

	for (int i = 0; i < APPLE_NUM; i++)
		m_cApple[i].Exit();

}

//初期化
void CApple::Init(CPlayer& cPlayer)
{
	m_fRadius = ITEM_RADIUS;
	m_iHp = cPlayer.GetPlayerHP();	//プレイヤーのhｐを受け取る
	StartTime = 0;
	ResultFrg = false;
	MaxPlayerHp = cPlayer.GetPlayerHP();
	m_iWaitCnt = WAIT_TIME;


	for (int i = 0; i < APPLE_NUM; i++)
	{
		m_cApple[i].Init(ITEM_RADIUS);
	}

}

//ロード
void CApple::Load()
{
	//２ｄ画像ロード ｈｐ分ロードする
	for (int i = 0; i < m_iHp; i++)
	{
		m_iOnHndl[i] = LoadGraph(ON_APPLES_PATH);
		m_iUnderHndl[i] = LoadGraph(UNDER_APPLES_PATH);

	}

	//オリジナルモデルを読み込み
	int iHndl = MV1LoadModel(MODEL_PATH);

	//モデルの複製
	for (int i = 0; i < APPLE_NUM; i++)
	{
		//出現範囲を設定
		m_cApple[i].Load(DRAW_ITEM_X, DRAW_ITEM_Z);
		//複製する
		m_cApple[i].DuplicateLoad(iHndl, DRAW_ITEM_X, DRAW_ITEM_Z);
	}

	//オリジナルモデル削除
	MV1DeleteModel(iHndl);

}

//ループ
void CApple::Step()
{
	StartTime++;

	for (int i = 0; i < APPLE_NUM; i++)
	{

		//通常ループ
		m_cApple[i].Step();
		//リスポーンするループ処理
		m_cApple[i].RespawnStep(DRAW_ITEM_X, DRAW_ITEM_Z, APPLE_NUM);


	}

	//一定時間経てば食料を減らす
	if (StartTime % HUNGRY_TIME == 0)
	{
		SetAppleGauge();
	}

	////食料ゲージが０になるとリザルト
	//if (m_iHp == 0)
	//{
	//	ResultFrg = true;
	//}

}

//描画
void CApple::Draw()
{
	//３ｄモデル描画
	for (int i = 0; i < APPLE_NUM; i++)
	m_cApple[i].Draw();

	////食料ゲージ描画(どれくらいおなかがへっているかわかるように暗く描画)
	//for (int i = 0; i < MaxPlayerHp; i++)
	//	DrawGraph(i * SHIFT_ITEM_PICTURE, APPLE_2D_Y, m_iUnderHndl[i], true);

	//for (int k = 0; k < m_iHp; k++)
	//	DrawGraph(k * SHIFT_ITEM_PICTURE, APPLE_2D_Y, m_iOnHndl[k], true);


}

//プレイヤーかアイテム当たった後の処理
void CApple::HitItem()
{

	//もともとある食料の最大値より少なかったら回復
	if (m_iHp < PLAYER_HP)
		m_iHp++;

}

