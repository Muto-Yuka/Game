#pragma once
#include <DxLib.h>
#include "../../MyLib/BaseAnim/BaseAnim.h"

class CShot : public CBaseAnim
{
private:
	float m_fRadius; //半径（球なのでfloat）

public:
	//コンストラクタ.デストラクタ
	CShot();
	~CShot();

	void Init();
	void Exit();
	void Draw();

	//データ関連のロード
	void Load(int iMdlHndl);

	//毎フレーム呼ぶ処理
	void Step();

	//弾が発射されているかどうか　true　発射済み false　発射されてない
	bool RequestShot(const VECTOR& vPos, const VECTOR& Speed);

	//座標取得
	VECTOR GetPosition() { return m_vPos; }
	//半径取得
	float GetRadius(void) { return m_fRadius; }

	//当たり判定
	void HitCalc();
};

