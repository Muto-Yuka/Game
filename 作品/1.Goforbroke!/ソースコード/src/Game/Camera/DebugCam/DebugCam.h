#pragma once
#include <dxlib.h>

class DebugCamera {
private:
	// カメラに使用する変数
	VECTOR m_vPos;	// 視点
	VECTOR m_vForcus;// 注視点
	VECTOR m_vUp;	// 上方向
	VECTOR m_vRot;			//回転角度

public:
	//コンストラクタ・デストラクタ
	DebugCamera();

	~DebugCamera();

	//初期化

	void Init();
	void Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp);

	//毎フレーム呼ぶ処理
	void Step(VECTOR vForcus, float fRot);

	//更新したデータを反映させる
	void Update();
};
