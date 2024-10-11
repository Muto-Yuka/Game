#include "BaseItem.h"

//コンストラクタ
CItemBase::CItemBase()
{

}

//デストラクタ
CItemBase::~CItemBase()
{
	Exit();
}

//初期化
void CItemBase::Init(float Radius)
{
	m_iHndl = -1;
	m_bSurvival = true;
	m_RespawnTime = 0;
	m_fRadius = Radius;

}

//通常ループ
void CItemBase::Step()
{
	VECTOR scale = { 0.1f,0.1f,0.1f };
	MV1SetScale(m_iHndl, scale);


	MV1SetPosition(m_iHndl, m_vPos);

}

//リスポーンするループ処理
void CItemBase::RespawnStep(int x, int z, int ItemNum)
{
	//ヒットしてから時間を図る
	if (m_bSurvival == false)
		m_RespawnTime++;

	//リンゴにあたって描画されなくなりリスポーン時間に到達したら
	if (m_bSurvival == false && m_RespawnTime % 120 == 0)
	{
		//リスポーンする
		RespawnItem(x, z, ItemNum);

	}
}



//ロード 範囲を設定	普通のランダム値ロード
void CItemBase::Load(int x, int y)
{


	m_vPos = VGet((float)GetRand(x), 0, (float)GetRand(y));

}

//複製ランダム値ロード
void CItemBase::DuplicateLoad(int Hndl, int x, int z)
{
	if (m_iHndl == -1)
	{
		//複製する
		m_iHndl = MV1DuplicateModel(Hndl);
		//スケールをセット
		MV1SetScale(m_iHndl, VGet(0.1f, 0.1f, 0.1f));
		//座標をセット
		m_vPos = VGet((float)GetRand(x) - (x / 2), 0, (float)GetRand(z) - (z / 2));
		//座標を更新
		MV1SetPosition(m_iHndl, m_vPos);

	}

}

//描画
void CItemBase::Draw()
{
	if (m_bSurvival)
		MV1DrawModel(m_iHndl);
}

//終了
void CItemBase::Exit()
{
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}


}

//リクエスト
bool CItemBase::RequestItem(const VECTOR& vPos)
{
	//すでに敵が出ている  エラー情報を返す
	if (m_bSurvival) return false;

	m_vPos = vPos;
	m_bSurvival = true;

	//一度座標を更新
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

//リスポーン処理
void CItemBase::RespawnItem(int x, int z, int ItemNum)
{
	//再度ランダムで出現する座標を取得
	m_vPos = VGet((float)GetRand(x - (x / 2)), 0, (float)GetRand(z - (z / 2)));
	//再び描画
	m_bSurvival = true;
	m_RespawnTime = 0;

	for (int i = 0; i < ItemNum; i++)
	{
		if (RequestItem(m_vPos))
		{
			break;
		}
	}

}


