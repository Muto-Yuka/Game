#include "shotManager.h"

static const char PLSHOT_MODEL_PATH[] = { "data/Game/Shot/Shot.x" };

//コンストラクタ
ShotManager::ShotManager()
{
	Init();
}

//デストラクタ
ShotManager::~ShotManager()
{
	Exit();
}

//初期化
void ShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Init();
	}

	for (int k = 0; k < EM_SHOT_NUM; k++)
	{
		cEnemyShot[k].Init();
	}
}

//ロード
void ShotManager::Load()
{
	//オリジナルモデルを読み込み
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);

	//プレイヤーの弾モデルの複製
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Load(iHndl);
	//敵モデルの弾の複製
	for (int k = 0; k < EM_SHOT_NUM; k++)
		cEnemyShot[k].Load(iHndl);

	MV1DeleteModel(iHndl);
}

//終了処理
void ShotManager::Exit()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Exit();
	for (int k = 0; k < EM_SHOT_NUM; k++)
		cEnemyShot[k].Exit();
}

//毎フレーム呼ぶ処理
void ShotManager::Step()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Step();
	for (int k = 0; k < EM_SHOT_NUM; k++)
		cEnemyShot[k].Step();
}


//更新処理
void ShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
		cPlayerShot[i].Draw();
	for (int k = 0; k < EM_SHOT_NUM; k++)
		cEnemyShot[k].Draw();
}

//プレイヤーのショットリクエスト
void ShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		if (cPlayerShot[i].RequestShot(vPos, vSpeed))
		{
			break;
		}
	}
}

//敵のリクエストショット
void ShotManager::RequestEnemyShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int k = 0; k < EM_SHOT_NUM; k++)
	{
		if (cEnemyShot[k].RequestShot(vPos, vSpeed))
		{
			break;
		}
	}
}





