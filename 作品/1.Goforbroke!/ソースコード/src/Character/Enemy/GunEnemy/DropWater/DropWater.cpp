#include "DropWater.h"

#define DROP_WATER_RADIUS	(3)

//初期化
void CDropWater::Init()
{
	m_iDropHndl = -1;
	m_vWaterPos = { 0.f, 0.f, 0.f };
	m_fRadius = DROP_WATER_RADIUS;
	m_bSurvival = false;
	m_bMove = false;
	m_bPlayerHit = false;
}

//複製ロード
void CDropWater::DuplicateLoad(int DropHndl)
{

	//３ｄアイテムモデル描画
	if (m_iDropHndl == -1)
	{
		m_iDropHndl = MV1DuplicateModel(DropHndl);
		MV1SetScale(m_iDropHndl, VGet(0.1f, 0.1f, 0.1f));
	}
}

//ループ
void CDropWater::Step()
{

	//座標をセット
	MV1SetPosition(m_iDropHndl, m_vWaterPos);

}

//描画
void CDropWater::Draw()
{
	if (m_bSurvival)
	{
		//水が初期値から移動してたら描画
		if (m_vWaterPos.x != 0.0f || m_vWaterPos.z != 0.0f)
		{
			//モデル描画
			MV1DrawModel(m_iDropHndl);

		}

	}
}

//破棄
void CDropWater::Exit()
{
	MV1DeleteModel(m_iDropHndl);
}

//プレイヤーとHITした時の処理
void CDropWater::HitCalc(CPlayer& cPlayer)
{
	m_bPlayerHit = true;

	//描画しない
	m_bSurvival = false;
	//再び座標セット
	m_bMove = false;

	//プレイヤーに水を持たせる 変数に＋＋する
	cPlayer.SetWaterNum();

	//持っている水を水場に返す
	HitReturn();
}

//持っている水を水場に返す
void CDropWater::HitReturn()
{
	//修理・返すボタンが押されたら
	if (CheckHitKey(KEY_INPUT_Q) || CPlayer::input.Buttons[2] > 0)
	{


	}

}


