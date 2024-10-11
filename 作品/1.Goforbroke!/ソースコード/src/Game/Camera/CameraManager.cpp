#include "CameraManager.h"
#include <DxLib.h>

//定義関連
//基本となる視点・注視点・アップベクトル
VECTOR DEFAULT_EYE_POS = { 0.0f, 10.0f, -20.0f };
VECTOR DEFAULT_FORCUS_POS = { 0.0f, 0.0f, 0.0f };
VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };


//コンストラクタ
CCameraManager::CCameraManager()
{
	m_eCurrentCameraID = CAMERA_ID_PLAY;
}

//デストラクタ
CCameraManager::~CCameraManager()
{

}

//初期化
void CCameraManager::Init()
{
	//m_cPlayCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);
	//m_DebugCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);
}

//毎フレーム呼ぶ処理
void CCameraManager::Step(VECTOR vForcus, float fRot)
{
	//カメラのタイプに合わせて、更新処理を変更する
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
	{
		m_cPlayCam.Loop(vForcus, fRot);
		m_cPlayCam.Update();

		break;
	}
	case CAMERA_ID_DEBUG:
	{
		m_DebugCam.Step(vForcus, fRot);
		m_DebugCam.Update();

		break;
	}
	}




}

//カメラのニア・ファーの設定
void CCameraManager::SetNearFar(float fNear, float fFar)
{
	SetCameraNearFar(fNear, fFar);

}

