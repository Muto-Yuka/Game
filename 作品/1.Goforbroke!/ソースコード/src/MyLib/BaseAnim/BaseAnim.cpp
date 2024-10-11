#include "BaseAnim.h"

static const VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };

//初期化
void CBaseAnim::Init()
{
	//アニメ関連データ初期化
	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	m_sAnimData.m_iAnimHndl = -1;
	m_sAnimData.m_iID = -1;

	//モデル関連データ初期化
	m_vPos = VECTOR_ZERO;
	m_vRot = VECTOR_ZERO;
	m_vScale = VECTOR_ZERO;
	m_vSpeed = VECTOR_ZERO;
	m_iHndl = -1;
	m_fRadius = 0;
	m_bSurvival = true;
	m_sAnimData.m_bPlay = true;
}

//描画
void CBaseAnim::Draw()
{
	if (m_bSurvival)
		MV1DrawModel(m_iHndl);
}

//破棄
void CBaseAnim::Exit()
{
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//更新
void CBaseAnim::UpData()
{
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);
}

//**ロード関数**
//通常ロード
bool CBaseAnim::LoadModel(const char* pFilePath)
{
	if (m_iHndl != -1) return false;	
	m_iHndl = MV1LoadModel(pFilePath);
	if (m_iHndl == -1) return false;	

	return true;
}

//モデル複製ロード
bool CBaseAnim::DuplicateModel(int iModelHndl)
{
	if (m_iHndl != -1) return false;	
	m_iHndl = MV1DuplicateModel(iModelHndl);
	if (m_iHndl == -1) return false;	

	return true;
}

//モデル削除
void CBaseAnim::DeleteModel()
{
	if (m_iHndl == -1) return;

	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;

}

//**アニメーション関数**
//アニメ更新
void CBaseAnim::UpdataAnim()
{
	//アニメーションが再生されてないと抜ける
	if (m_sAnimData.m_iAnimHndl == -1) return;
	//速度更新
	m_sAnimData.m_fFrm += m_sAnimData.m_fSpd;
	//最後まで再生されたら動作を変える
	if (m_sAnimData.m_fFrm >= m_sAnimData.m_fEndFrm)
	{
		switch (m_sAnimData.m_iState)
		{
			//通常再生
		case ANIMSTATE_NORMAL:
			DetachAnim();
			m_sAnimData.m_fEndFrm = 0.f;
			m_sAnimData.m_fFrm = 0.0f;
			m_sAnimData.m_fSpd = 0.0f;
			m_sAnimData.m_bPlay = false;
			return;

			//ループ再生　最初にもどす
		case ANIMSTATE_LOOP:
			m_sAnimData.m_fFrm = 0.0f;
			m_sAnimData.m_bPlay = true;
			break;

			//エンドループ　最後で止める
		case ANIMSTATE_END:
			m_sAnimData.m_fFrm = m_sAnimData.m_fEndFrm;
			m_sAnimData.m_bPlay = false;	//再生終了
			break;
		}
	}

	//再生時間設定
	MV1SetAttachAnimTime(m_iHndl, m_sAnimData.m_iAnimHndl, m_sAnimData.m_fFrm);
}

//アニメＩＤ、再生速度、アニメのモデルハンドル、別モデルのアニメを使う場合アタッチするか
void CBaseAnim::Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	//アニメ消去
	DetachAnim();

	//アニメ再生・各種データセット
	m_sAnimData.m_iAnimHndl = MV1AttachAnim(m_iHndl, iAnimID, iAnimSrcHndl, NameCheck);
	m_sAnimData.m_iID = iAnimID;
	m_sAnimData.m_fEndFrm = MV1GetAnimTotalTime(m_iHndl, iAnimID);
	m_sAnimData.m_fFrm = 0.0f;
	m_sAnimData.m_fSpd = iAnimSpd;
	//通常再生
	m_sAnimData.m_iState = ANIMSTATE_NORMAL;
}

//ループアニメ　 アニメが最後まで再生されると最初に戻す
void CBaseAnim::RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	m_sAnimData.m_bPlay = true;
	//ループ再生へ
	m_sAnimData.m_iState = ANIMSTATE_LOOP;
}

//エンドループ　　アニメが最後まで再生されても戻さずそのまま
void CBaseAnim::RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, iAnimSpd, iAnimSrcHndl, NameCheck);
	//一回のみ再生へ
	m_sAnimData.m_iState = ANIMSTATE_END;
}

//アニメをデタッチ
void CBaseAnim::DetachAnim()
{
	if (m_sAnimData.m_iAnimHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimData.m_iAnimHndl);
		m_sAnimData.m_iAnimHndl = -1;
	}
}


