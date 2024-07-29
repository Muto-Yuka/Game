#include <DxLib.h>
#include <crtdbg.h>
#include <math.h>
#include "DebugCam.h"

static const float ROTATE_SPEED = 0.1f;		//プレイヤーの回転速度

#define CAMERA_LENGTH (50.0f)
#define CAMERA_OFFSET_Y (20.0f)
#define FORCUS_OFFSET_Y (10.0f)
static const float DEBUG_CAMERA_SPEED = 1.0f;		//の移動速度


//コンストラクタ
DebugCamera::DebugCamera()
{
	//初期化
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vForcus, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//デストラクタ
DebugCamera::~DebugCamera()
{

}


void DebugCamera::Init()
{
	m_vPos = VGet(0.0f, 0.0f, 1.0f);
	m_vForcus = VGet(0.0f, 0.0f, 0.0f);
	m_vUp = VGet(0.0f, 1.0f, 0.0f);
}

//初期化
void DebugCamera::Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp)
{
	m_vPos = vPos;
	m_vForcus = vForcus;
	m_vUp = vUp;
}


//毎フレーム呼ぶ処理
void DebugCamera::Step(VECTOR vForcus, float fRot)
{

	//注視点上下
	if (CheckHitKey(KEY_INPUT_UP)) m_vForcus.y += DEBUG_CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_DOWN)) m_vForcus.y -= DEBUG_CAMERA_SPEED;
	//注視点
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//if (m_vForcus.x >= -DX_PI_F * 0.5f)
		m_vForcus.x += DEBUG_CAMERA_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		//if (m_vForcus.x >= DX_PI_F * 0.5f)
		m_vForcus.x -= DEBUG_CAMERA_SPEED;

	}

	//カメラの前進後退
	float speed = 0.0f;
	if (CheckHitKey(KEY_INPUT_W)) speed += DEBUG_CAMERA_SPEED;
	if (CheckHitKey(KEY_INPUT_S)) speed -= DEBUG_CAMERA_SPEED;
	m_vPos.x += sinf(m_vForcus.y) * speed;


	////キャラクターのかいてん
	//if (CheckHitKey(KEY_INPUT_RIGHT)) m_vRot.y += ROTATE_SPEED;
	//else if (CheckHitKey(KEY_INPUT_LEFT)) m_vRot.y -= ROTATE_SPEED;

	////キャラクターの移動
	//float fSpd = 0.0f;
	//if (CheckHitKey(KEY_INPUT_UP)) fSpd = -MODEL_SPEED;
	//if (CheckHitKey(KEY_INPUT_DOWN)) fSpd = MODEL_SPEED;

	////入力したキー情報とプレイヤーの角度から、移動速度を求める
	//m_vSpeed.x = sinf(m_vRot.y) * fSpd;
	//m_vSpeed.z = cosf(m_vRot.y) * fSpd;
	////移動速度を現在の座標に加算する
	//m_vPos = VAdd(m_vPos, m_vSpeed);

}

//更新したデータを反映させる
void DebugCamera::Update()
{
	//DxLibの方にカメラを更新
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vForcus, m_vUp);
}
