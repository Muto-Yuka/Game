#include "BreakEnemy.h"

static const char ENEMY_MODEL_PATH[] = { "data/Character/Enemy/TemporaryEnemy１.mv1" };
static const int WAIT_TIME = 120;		//敵の出現時間
static const int RESPAWN_TIME = 600;	//敵が倒されてから復活するまでの時間

#define B_ENEMY_HP	(3)			
#define NEXT_TIME	(500)			//午後時間が終われば強制で次のシーンへ

CBreakEnemy::CBreakEnemy()
{

}
CBreakEnemy::~CBreakEnemy()
{
	Exit();
}

//初期化
void CBreakEnemy::Init(CApple& cApple)
{
	for (int i = 0; i < BREAK_ENEMY_NUM; i++)
	{
		//初期化
		m_cBreakEnemy[i].Init(cApple);
		//敵のｈｐをセット
		m_cBreakEnemy[i].SetEnemyHP(B_ENEMY_HP * PLAYER_ATTACK);
	}
	//リスポーン時間を設定
	m_iWaitRespawn = RESPAWN_TIME;

	NextDayFrg = false;
	NextDayCount = NEXT_TIME;
}

//ロード
void CBreakEnemy::Load()
{
	//オリジナルモデルを読み込み
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);

	//モデルの複製
	for (int i = 0; i < BREAK_ENEMY_NUM; i++)
		m_cBreakEnemy[i].Load(iHndl);

	MV1DeleteModel(iHndl);
}

//終了処理
void CBreakEnemy::Exit()
{
	for (int i = 0; i < BREAK_ENEMY_NUM; i++)
		m_cBreakEnemy[i].Exit();
}

//毎フレーム呼ぶ処理
void CBreakEnemy::Step(CWater& cWater, CScreen& cScreen)
{

	int iEnemyCnt = 0;
	//敵の移動処理
	for (int i = 0; i < BREAK_ENEMY_NUM; i++)
	{
		m_cBreakEnemy[i].BreakEnemyStep(cWater);
		if (m_cBreakEnemy[i].CBaseAnim::IsSurvival())
			iEnemyCnt++;
	}

	//水場が描画されていて描画されて時間が経っている
	if (cWater.GetSurvivalFrg())
	{
		m_iWaitRespawn--;

		//午後の時間が０になるまでは敵を出す
		if (cScreen.GetPmTimeLimit() >= 0)
		{
			//倒されてから時間が経った
			if (m_iWaitRespawn < 0)
			{

				RequestEnemy();

				m_iWaitRespawn = RESPAWN_TIME;
			}
		}
	}

	//午後時間が終われば次へ
	if (cScreen.GetPmTimeLimit() <= 0)
	{
		NextDayCount--;

		//敵がみんな倒されたら
		if (!m_cBreakEnemy[0].GetSurvival() && !m_cBreakEnemy[1].GetSurvival())
		{
			NextDayFrg = true;
		}

		//時間が経てば強制で次のシーンへ
		if (NextDayCount < 0)
		{
			NextDayCount = NEXT_TIME;
			NextDayFrg = true;
		}
	}
}


//描画処理
void CBreakEnemy::Draw()
{
	for (int i = 0; i < BREAK_ENEMY_NUM; i++)
		m_cBreakEnemy[i].Draw();

}

//敵のリクエスト
void CBreakEnemy::RequestEnemy()
{
	//出現する位置をランダムで取得
	VECTOR vPos = VGet((float)GetRand(200) - 100.0f, 0, 200.0f);
	//敵のスピード
	VECTOR vSpeed = VGet(0.0f, 0.0f, -0.5f);

	for (int i = 0; i < BREAK_ENEMY_NUM; i++)
	{
		if (m_cBreakEnemy[i].RequestEnemy(vPos, vSpeed))
		{
			break;
		}
	}
}



