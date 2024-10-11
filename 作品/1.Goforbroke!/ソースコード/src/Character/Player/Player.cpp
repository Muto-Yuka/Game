#include "player.h"
#include "../../MyLib/Input/Input.h"

//プレイヤー情報
static const float RADIUS = 5.0f;				//半径
static const int REPAIR_TIME = 150;				//水場の修理時間
static const float ROTATE_SPEED = 0.02f;		//プレイヤーの回転速度  DX_PI_Fはπ
static const float MODEL_SPEED = 1.0f;			//プレイヤーの移動速度
static const float MODEL_RUN_SPEED = 2.0f;		//プレイヤーの走った時の移動速度
static const float SHOT_SPEED = 5.0f;			//弾の速度
static const int WAIT_BULLET_TIME = 20;			//弾の発射時間
//パス
static const char PLAYER_MODEL_PATH[] = { "data/Character/Player/Playerblend.mv1" };
static const char REPAIR_PATH[] = { "data/Character/Player/Repair.png" };


CPlayer::CPlayer()
{
	Init();
}

CPlayer::~CPlayer()
{
	CBaseAnim::Exit();
	CPlayAnim::Exit();
	DeleteGraph(m_iRepairHndl);
}

//初期化
void CPlayer::Init()
{
	CBaseAnim::Init();
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_vRot.y = 3.1f;						
	m_fRadius = RADIUS;
	m_iWaitBulletCnt = WAIT_BULLET_TIME;
	m_iRepair_time = REPAIR_TIME;
	m_iWaterNum = 0;
	m_iRepairHndl = -1;

}

//ロード
void CPlayer::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1LoadModel(PLAYER_MODEL_PATH);
	}

	m_iRepairHndl = LoadGraph(REPAIR_PATH);

	CPlayAnim::Load();
}

//ループ
void CPlayer::Loop(ShotManager& cShotManager, CWater& cWater)
{

	//プレイヤー弾設定処理
	PlayerShot(cShotManager);

	//プレイヤー行動処理
	PlayerMove();

	//アニメ更新
	CPlayAnim::Loop();

}

//プレイヤー行動
void CPlayer::PlayerMove()
{
	//速度などを反映
	Update();
	float Rotate = ROTATE_SPEED;
	float Speed = MODEL_SPEED;

	//ズーム
	if (CheckHitKey(KEY_INPUT_RSHIFT) || (input.Z != 0))
	{
		Rotate = 0.01f;
	}

	//走る
	if (CInput::IsInputDown(CInput::INPUT_DASH) || (input.Buttons[4] > 0))
		Speed = MODEL_RUN_SPEED;
	else
		Speed = MODEL_SPEED;

	//左右回転
	if (CheckHitKey(KEY_INPUT_RIGHT) || (input.Rx > 0)) m_vRot.y += Rotate;
	if (CheckHitKey(KEY_INPUT_LEFT) || (input.Rx < 0)) m_vRot.y -= Rotate;

	//キャラクターの移動
	VECTOR fSpd = { 0.0f,0.0f,0.0f };
	//前後
	if (CInput::IsInputDown(CInput::INPUT_UP) || (input.Y < 0))
	{
		fSpd.x = sinf(m_vRot.y) * -Speed;
		fSpd.z = cosf(m_vRot.y) * -Speed;
	}
	if (CInput::IsInputDown(CInput::INPUT_DOWN) || (input.Y > 0))
	{
		fSpd.x = sinf(m_vRot.y) * Speed;
		fSpd.z = cosf(m_vRot.y) * Speed;
	}
	//左右
	if (CInput::IsInputDown(CInput::INPUT_LEFT) || (input.X < 0))
	{
		fSpd.x = sinf(m_vRot.y - DX_PI_F / 2) * -Speed;
		fSpd.z = cosf(m_vRot.y - DX_PI_F / 2) * -Speed;

	}
	if (CInput::IsInputDown(CInput::INPUT_RIGHT) || (input.X > 0))
	{
		fSpd.x = sinf(m_vRot.y - DX_PI_F / 2) * Speed;
		fSpd.z = cosf(m_vRot.y - DX_PI_F / 2) * Speed;
	}

	m_vSpeed = fSpd;

	//地面に合わせる
	m_vPos.y = 3.5f;
	//移動速度を現在の座標に加算する
	m_vPos = VAdd(m_vPos, m_vSpeed);

}

//プレイヤーに当たった時の処理
void CPlayer::HitCalc()
{
	//初期値にリスポーン
	memset(&m_vPos, 0, sizeof(VECTOR));
	m_vRot.y = 3.1f;

	m_HP--;
}

//プレイヤー弾発射処理
void CPlayer::PlayerShot(ShotManager& cShotManager)
{
	m_iWaitBulletCnt--;

	//高さ調整
	VECTOR vPos = m_vPos;
	vPos.y += 15.0f;
	//移動方向
	VECTOR vSpd = { 0.0f, 0.0f, 0.0f };

	vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
	vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;

	//発射
	if (CInput::IsInputDown(CInput::INPUT_SHOT) || (input.Buttons[5] > 0))
	{
		if (m_iWaitBulletCnt < 0)
		{
			cShotManager.RequestPlayerShot(vPos, vSpd);

			m_iWaitBulletCnt = WAIT_BULLET_TIME;
		}
	}
}

//現在位置に座標を加算
void CPlayer::ReflectCollision(VECTOR vAddVec)
{
	//移動していなければreturn
	if (vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;

	m_vPos = VAdd(m_vPos, vAddVec);
}

//水場を修理する処理関数　水場と当たっている時に呼ばれる
void CPlayer::WatrRepair(CWater& cWater)
{
	//水場にヒットしている ＆ 修理ボタンが押され続けている
	if (CInput::IsInputKeep(CInput::INPUT_REPAIR) || (input.Buttons[2] > 0))
	{
		//時間のカウントを減らす
		m_iRepair_time--;

		cWater.SetHp(10.f);

		//カウントが０または０以下になれば修理する
		if (m_iRepair_time < 0 || m_iRepair_time == 0)
		{
			cWater.SetSurvivalFrg(true);
			m_iRepair_time = REPAIR_TIME;
		}
	}
	//修理キーが離されるとカウントをもとに戻す
	else
	{
		m_iRepair_time = REPAIR_TIME;
	}

	//水を持っている状態で修理キーを押す
	if (CInput::IsInputPush(CInput::INPUT_REPAIR) || (input.Buttons[2] > 0))
	{
		if (m_iWaterNum > 0)
			m_iWaterNum--;
	}
}

//フィールド用プレイヤーの中心当たり判定を取得する
VECTOR CPlayer::GetCenter()
{
	VECTOR	vCenter = MV1GetPosition(m_iHndl);
	return vCenter;
}








