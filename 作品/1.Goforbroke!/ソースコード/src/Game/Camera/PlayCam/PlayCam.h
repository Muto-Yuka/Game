#include <dxlib.h>

class CPlayCamera {
private:
	VECTOR m_vPos;			//視点
	VECTOR m_vForcus;		//注視点
	VECTOR m_vUp;			//上方向
	VECTOR SubVector;		//カメラが敵に向かうベクトル
	float m_iCameraLen;		//カメラ距離

public:
	CPlayCamera();
	~CPlayCamera();

	void Init();
	void Loop(VECTOR vForcus, float fRot);
	void Update();



};



