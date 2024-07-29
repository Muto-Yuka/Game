#include <DxLib.h>
#include <crtdbg.h>
#include <math.h>
#include "PlayCam.h"
#include "../../../MyLib/Input/Input.h"
#include "../../../Character/Player/Player.h"

#define CAMERA_MAX_LENGTH		(70.0f)		//走った時に離れる最大の距離
#define CAMERA_USUALLY_LENGTH	(50.0f)		//通常のプレイヤーとカメラの距離
#define CAMERA_MIN_LENGTH		(40.0f)		//ズーム時のプレイヤーとカメラの距離

#define CAMERA_OFFSET_Y (35.0f)
#define FORCUS_OFFSET_Y (30.0f)

//コンストラクタ
CPlayCamera::CPlayCamera()
{
	//初期化
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vForcus, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
	m_iCameraLen = CAMERA_USUALLY_LENGTH;
	Init();
}

//デストラクタ
CPlayCamera::~CPlayCamera()
{

}


void CPlayCamera::Init()
{
	m_vPos = VGet(0.0f, 0.0f, 1.0f);
	m_vForcus = VGet(0.0f, 0.0f, 0.0f);
	m_vUp = VGet(0.0f, 1.0f, 0.0f);
	SubVector = { 0.0f,0.0f,0.0f };

}

//毎フレーム呼ぶ処理
void CPlayCamera::Loop(VECTOR vForcus, float fRot)
{

	//コントローラー用
	CPlayer::Key = GetJoypadDirectInputState(DX_INPUT_PAD1, &CPlayer::input);		//使用するパッドを指定

	//プレイヤーが原点にいて、ｙ軸回転が０どであることを前提に考える
	//プレイヤーの回転角度に合わせて上記方向ベクトルを回転させる
	VECTOR vDir;
	vDir.x = sinf(fRot) * m_iCameraLen;
	vDir.z = cosf(fRot) * m_iCameraLen;
	//視点の高さは固定
	vDir.y = CAMERA_OFFSET_Y;

	//注視店（プレイヤー）の一課r計算結果の距離を移動させれば
	//カメラの視点になる
	m_vPos = VAdd(vForcus, vDir);

	//注視点はターゲットの位置を利用する
	m_vForcus = vForcus;
	m_vForcus.y = FORCUS_OFFSET_Y;

	//シフト押すとズーム機能
	if (CInput::IsInputDown(CInput::INPUT_ZOOM) /*|| (&CPlayer::input.Z > 0)*/)
	{
		//近づける
		if (m_iCameraLen > CAMERA_MIN_LENGTH)
			m_iCameraLen--;

	}
	else
	{
		//通常距離に戻す
		if (m_iCameraLen < CAMERA_USUALLY_LENGTH)
			m_iCameraLen++;
	}

	//プレイヤーが走るとカメラが離れたり近づいたり
	if (CInput::IsInputDown(CInput::INPUT_DASH) && CInput::IsInputDown(CInput::INPUT_UP))
	{
		//カメラを遠ざける
		if (m_iCameraLen < CAMERA_MAX_LENGTH)
			m_iCameraLen += 0.5f;

	}
	else
	{
		//通常距離に戻す
		if (m_iCameraLen > CAMERA_USUALLY_LENGTH)
			m_iCameraLen -= 0.5f;

	}

}

//更新したデータを反映させる
void CPlayCamera::Update()
{
	//DxLibの方にカメラを更新
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vForcus, m_vUp);
}


