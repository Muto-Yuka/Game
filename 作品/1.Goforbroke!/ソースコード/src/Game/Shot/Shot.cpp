#include "shot.h"
#include <Math.h>

#define SHOT_RADIUS (3)

//コンストラクタ
CShot::CShot()
{
	//初期化
	memset(&m_vPos, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_bSurvival = false;
	m_fRadius = SHOT_RADIUS;
	m_vSpeed = VGet(0.0f, 0.0f, 0.0f);
}

//デストラクタ
CShot::~CShot()
{
	Exit();
}

//初期化
void CShot::Init()
{
	CBaseAnim::Init();
	m_bSurvival = false;
	m_fRadius = SHOT_RADIUS;
}

//終了処理
void CShot::Exit()
{
	CBaseAnim::Exit();
}

//データ関連のロード
void CShot::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
	}
}

//描画処理
void CShot::Draw()
{
	CBaseAnim::Draw();
}

//毎フレーム呼ぶ処理
void CShot::Step()
{
	if (!m_bSurvival) return;

	//座標に速度を加算
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//一定範囲を超えたら球を消す
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.x < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_bSurvival = false;
	}

	//弾の大きさを変更
	VECTOR scale = { 1.5f,1.5f,1.5f };
	MV1SetScale(m_iHndl, scale);


	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);

}

//リクエスト
bool CShot::RequestShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//すでに発射されている  エラー情報を返す
	if (m_bSurvival) return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_bSurvival = true;

	return true;


}

//当たり判定
void CShot::HitCalc()
{
	m_bSurvival = false;
}


