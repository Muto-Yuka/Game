#include <DxLib.h>
#include "Ground.h"

const char GROUND_PATH[] = { "data/Game/Field/Ground/Stage.x" };

CGround::CGround()
{
	Init();
}

CGround::~CGround()
{
	Exit();
}

//初期化
void CGround::Init()
{
	m_isHitFlag = false;
	m_iHndl = -1;
	MV1SetPosition(m_iHndl, VGet(0.0f, 0.0f, 0.0f));
}

//ロード
void CGround::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1LoadModel(GROUND_PATH);
	}
	//モデルデータのポリゴン情報を構築する
	MV1SetupCollInfo(m_iHndl);
}

//ループ
void CGround::Loop()
{
	MV1SetPosition(m_iHndl, VGet(0.0f, -2.0f, 0.0f));
}

//描画
void CGround::Draw()
{
	MV1DrawModel(m_iHndl);
}

//破棄
void CGround::Exit()
{
	//ポリゴン情報破棄
	MV1TerminateCollInfo(m_iHndl);
}

//フィールド全体の当たり判定用
VECTOR CGround::HitCheck(VECTOR anotherPos, float anotherRadius)
{
	//押し戻す距離を保存する変数
	VECTOR vOut = { 0.0f, 0.0f, 0.0f };
	//構造体
	MV1_COLL_RESULT_POLY_DIM res;
	//情報をもとに当たり判定を取得し、変数の中に戻り値を受け取る
	res = MV1CollCheck_Sphere(m_iHndl, -1, anotherPos, anotherRadius);

	if (res.HitNum == 0) m_isHitFlag = false;
	else if (res.HitNum > 0)
	{
		//ぶつかったときに押し戻す距離を計算する
		m_isHitFlag = true;
		//複数ぶつかる場合
		for (int i = 0; i < res.HitNum; i++)
		{
			//プレイヤーとフィールドの距離を調べる
			//ぶつかったポリゴンと相手側の座標を引き算する
			VECTOR v = VSub(res.Dim[i].HitPosition, anotherPos);
			//引き算したベクトルの長さを求める
			float length = VSize(v);
			//めり込んだ距離を計算していく
			length = anotherRadius - length;
			//法線情報をもとに押し出し(掛け算)
			v = VScale(res.Dim[i].Normal, length);

			vOut = VAdd(vOut, v);
		}
	}
	//当たり判定情報を破棄
	MV1CollResultPolyDimTerminate(res);

	return vOut; //押し戻す距離が保存された変数を返す

}



