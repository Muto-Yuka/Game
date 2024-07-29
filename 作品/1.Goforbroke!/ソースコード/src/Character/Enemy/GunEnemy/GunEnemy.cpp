#include "GunEnemy.h"

static const int WAIT_TIME = 300;		//敵の出現時間
static const int RESPAWN_TIME = 800;	//敵が倒されてから復活するまでの時間

//<3d>モデル・画像パス
static const char ENEMY_MODEL_PATH[] = { "data/Character/Enemy/TemporaryEnemy１.mv1" };	//敵モデル
static const char ENEMY_DROP_PATH[] = { "data/Character/Enemy/DropWater.x" };				//敵が落とす水モデル

#define NEXT_TIME	(500)			//午後時間が終われば強制で次のシーンへ

//コンストラクタ
CGunEnemy::CGunEnemy()
{
	m_iWaitCnt = 0;
}

//デストラクタ
CGunEnemy::~CGunEnemy()
{
	Exit();
}

//初期化
void CGunEnemy::Init(CApple& cApple)
{
	m_iWaitCnt = WAIT_TIME;

	//敵の数分初期化
	for (int i = 0; i < GUN_ENEMY_NUM; i++)
	{
		//モデル初期化
		m_cGunEnemy[i].Init(cApple);
		//ドロップ水初期化
		m_cDropWater[i].Init();

		//敵のｈｐをセット（初期化）
		m_cGunEnemy[i].SetEnemyHP(G_ENEMY_HP * PLAYER_ATTACK);
	}



	//リスポーン時間を設定
	m_iWaitRespawn = RESPAWN_TIME;

	NextDayFrg = false;
	NextDayCount = NEXT_TIME;
}

//ロード
void CGunEnemy::Load()
{
	//オリジナル敵モデルを読み込み
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	//オリジナル水モデルを読み込み
	int iDropHndl = MV1LoadModel(ENEMY_DROP_PATH);

	//敵の数分モデルの複製
	for (int i = 0; i < GUN_ENEMY_NUM; i++)
	{
		//敵を複製ロード
		m_cGunEnemy[i].Load(iHndl);

		//水を複製ロード
		m_cDropWater[i].DuplicateLoad(iDropHndl);
	}

	//オリジナルモデル破棄
	MV1DeleteModel(iHndl);
	//オリジナルモデル破棄
	MV1DeleteModel(iDropHndl);

}

//終了処理
void CGunEnemy::Exit()
{
	for (int i = 0; i < GUN_ENEMY_NUM; i++)
	{
		m_cGunEnemy[i].Exit();
		m_cDropWater[i].Exit();
	}

}

//毎フレーム呼ぶ処理
void CGunEnemy::Step(CPlayer& cPlayer, ShotManager& cEnemyShot, CScreen& cScreen)
{

	int iEnemyCnt = 0;

	//敵の数分回す
	for (int i = 0; i < GUN_ENEMY_NUM; i++)
	{

		//敵の移動処理
		m_cGunEnemy[i].GunEnemyStep(cPlayer, cEnemyShot);
		if (m_cGunEnemy[i].CBaseAnim::IsSurvival())
			iEnemyCnt++;

		if (m_cDropWater[i].GetSurvival())
		{
			//水が停止中でなければ更新
			if (!m_cDropWater[i].GetMove())
			{

				//敵の座標を水の座標にセット
				m_cDropWater[i].SetWaterPos(m_cGunEnemy[i].GetPos());
				//水の座標を更新
				m_cDropWater[i].Step();
			}
		}
	}

	//午後の時間カウントが終わっていたら敵を出さない
	if (cScreen.GetPmTimeLimit() >= 0)
	{
		//敵の出現
		m_iWaitCnt--;
		if (m_iWaitCnt < 0)
		{
			RequestEnemy();
			m_iWaitCnt = WAIT_TIME;
			m_iWaitRespawn = RESPAWN_TIME;


		}

	}
	//午後時間が終われば次へ
	if (cScreen.GetPmTimeLimit() <= 0)
	{
		NextDayCount--;

		for (int i = 0; i < GUN_ENEMY_NUM; i++)
		{
			//敵がみんな倒されたら
			if (!m_cDropWater[0].GetSurvival() && !m_cDropWater[1].GetSurvival())
			{
				NextDayFrg = true;
			}

		}


		//時間が過ぎれば強制的に次のシーンへ
		if (NextDayCount < 0)
		{
			NextDayCount = NEXT_TIME;
			NextDayFrg = true;
		}
	}



}


//描画処理
void CGunEnemy::Draw()
{
	for (int i = 0; i < GUN_ENEMY_NUM; i++)
	{
		//敵描画
		m_cGunEnemy[i].Draw();
		//水描画
		m_cDropWater[i].Draw();
	}
}

//敵のリクエスト
void CGunEnemy::RequestEnemy()
{
	VECTOR vPos = VGet((float)GetRand(200) - 100.0f, 0, 200.0f);
	VECTOR vSpeed = VGet(0.0f, 0.0f, -0.5f);


	for (int i = 0; i < GUN_ENEMY_NUM; i++)
	{


		if (m_cGunEnemy[i].RequestEnemy(vPos, vSpeed))
		{

			//水が描画されてなかったら
			if (!m_cDropWater[i].GetSurvival())
				m_cDropWater[i].SetSurvival();

			break;
		}
	}
}

