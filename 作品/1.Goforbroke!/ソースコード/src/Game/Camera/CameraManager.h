#pragma once
#include "PlayCam/PlayCam.h"
#include "DebugCam/DebugCam.h"

class CCameraManager
{
public:

	//カメラのタイプ
	enum tagCAMERA_ID
	{
		CAMERA_ID_PLAY,			//ゲーム中のカメラ
		CAMERA_ID_DEBUG,		//デバック用カメラ

		CAMERA_ID_NUM
	};

private:
	CPlayCamera m_cPlayCam;				//プレイヤーカメラ
	DebugCamera m_DebugCam;				//プレイヤーカメラ
	tagCAMERA_ID m_eCurrentCameraID;	//現在のカメラb


public:

	//コンストラクタ.デストラクタ
	CCameraManager();
	~CCameraManager();

	//初期化
	void Init();
	//更新処理
	void Step(VECTOR vForcus, float fRot);

	//カメラのニア・ファー設定
	void SetNearFar(float fNear, float fFar);
	//現在のカメラタイプ取得
	tagCAMERA_ID GetCameraID() { return m_eCurrentCameraID; }


};


