#include "BaseEnemy.h"
#include <math.h>

const float ENEMY_SPEED = 1.0f;				//弾の速度
static const int WAIT_BULLET_TIME = 180;     //敵の次の弾の発射時間
static const float ENEMY_SLOW_DOWN = 0.3f;	//どれだけ敵のスピードを落とすか

//2d　敵のｈｐ画像
#define ENEMY_HP_PATH ("data/Character/Enemy/EnemyHP.Png")

#define ENEMY_RADIUS (5)
#define MY_DEBUG	(1)

//初期化
void CEnemyBase::Init(CApple& cApple)
{
	CBaseAnim::Init();
	m_fRadius = ENEMY_RADIUS;
	m_bSurvival = false;
	m_enemy_count = 0;
	Clear = false;
	m_vRot = { 0.0f,0.0f,0.0f };
	m_iWaitBulletCnt = WAIT_BULLET_TIME;
	m_vInitPos = (VGet((float)GetRand(200) - 100.0f, 0, 200.0f));
	m_fTransparency = 1.0f;
	m_iHpGaugeHndl = -1;
	m_bStopBEnemy = false;
	m_DropItem = -1;
}

//終了処理
void CEnemyBase::Exit()
{
	CBaseAnim::Exit();
}

//データロード
void CEnemyBase::Load(int iMdlHndl)
{


	//３ｄ敵モデル描画
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
		MV1SetScale(m_iHndl, VGet(0.05f, 0.05f, 0.05f));
	}

	//２ｄ　ｈｐ画像ロード
	m_iHpGaugeHndl = LoadGraph(ENEMY_HP_PATH);

}


//描画処理
void CEnemyBase::Draw()
{
	if (m_bSurvival)
	{
		//モデル描画
		MV1DrawModel(m_iHndl);
		//体力を描画する
		VECTOR m_pos = m_vPos;
		m_pos.y += 25;
		DrawModiBillboard3D(m_pos, -15.f, 0.f, (float)m_iHp - 15, 0.f, (float)m_iHp - 15, 5.f, -15.f, 5.f, m_iHpGaugeHndl, TRUE);

	}

}

//敵１のループ処理（弾を撃つ敵）
void CEnemyBase::GunEnemyStep(CPlayer& cPlayer, ShotManager& cEnemyShot)
{


	if (!m_bSurvival) return;
	m_iWaitBulletCnt--;

	//透明度を設定
	Transparency(m_iHndl, m_fTransparency);


	//モデルの大きさ
	VECTOR scale = { 0.1f,0.1f,0.1f };
	MV1SetScale(m_iHndl, scale);

	//==敵が常にプレイヤーの方に向く処理==
	EnemyLook(cPlayer.GetPosition(), m_vPos);

	//弾発射処理関数
	EnemyShot(cEnemyShot);

	//==敵の移動処理==
	EnemyMove();
}

//敵２のループ処理（水場を壊す敵）
void CEnemyBase::BreakEnemyStep(CWater& cWater)
{

	//透明度を設定
	Transparency(m_iHndl, m_fTransparency);

	m_iWaitBulletCnt--;

	//敵が死んだら次の敵は水場に向かって移動するように
	if (m_bSurvival == false)
		m_bStopBEnemy = false;

	//水場が生きている
	if (cWater.GetSurvivalFrg())
	{
		//敵が生きている
		if (m_bSurvival)
		{
			//敵が常に水場の方に向く処理==
			EnemyLook(cWater.GetPosition(), m_vPos);

			if (m_bStopBEnemy == false)
			{
				//水場に向かって移動する
				EnemyMove();

			}

		}
	}
	//水場が壊れている
	else
	{
		m_bStopBEnemy = false;
		//水場から逃げる 常に水場と反対方向を向く スタート地点を向く
		EnemyLook(m_vInitPos, m_vPos);

		//目標に向かって移動する
		EnemyMove();

		//特定の位置を超えたら敵を消す
		if (m_vPos.z > 190.0f)
		{
			m_bSurvival = false;
		}

	}
}

//向いてる方向に進む処理
void CEnemyBase::EnemyMove()
{
	//座標に速度を加算
	VECTOR vSpeed;
	vSpeed.x = sinf(m_fAngle) * ENEMY_SLOW_DOWN;
	vSpeed.z = cosf(m_fAngle) * ENEMY_SLOW_DOWN;
	vSpeed.y = 0.0f;

	m_vPos = VAdd(m_vPos, vSpeed);

	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
}

//常に指定された方向を向く関数
void CEnemyBase::EnemyLook(VECTOR TargetPos, VECTOR EnemyPos)
{
	// EnemyPosからTargetPosに向かうベクトルを算出
	//ターゲット座標から敵の座標をひく
	SubVector = VSub(TargetPos, EnemyPos);

	// atan2（ｘ軸ｙ軸間での間の角度） を使用して角度を取得
	m_fAngle = static_cast<float> (atan2(SubVector.x, SubVector.z));

	// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F （π）)を
	// 足した値を３Ｄモデルの Y軸回転値として設定
	MV1SetRotationXYZ(m_iHndl, VGet(0.0f, m_fAngle + DX_PI_F, 0.0f));

}

//弾発射関数
void CEnemyBase::EnemyShot(ShotManager& cEnemyShot)
{
	//==弾の処理==
	//敵の体から出るように座標を上げる
	VECTOR vPos = CBaseAnim::m_vPos;
	vPos.y += 5.0f;

	////速度はプレイヤーと同じ方法で移動方向を決める
	//プレイヤーに向かって弾を飛ばす
	VECTOR vSpd;
	vSpd.x = sinf(m_fAngle) * ENEMY_SPEED;
	vSpd.z = cosf(m_fAngle) * ENEMY_SPEED;
	vSpd.y = 0.0f;
	//発射待機時間が０になったら
	if (m_iWaitBulletCnt == 0)
	{
		//発射関数を呼ぶ　RequestEnemtShotの中に発射処理
		cEnemyShot.RequestEnemyShot(vPos, vSpd);
		m_iWaitBulletCnt = WAIT_BULLET_TIME;
	}
}

//リクエスト
bool CEnemyBase::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//すでに敵が出ている  エラー情報を返す
	if (m_bSurvival) return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_bSurvival = true;

	//一度座標を更新
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

//当たった時の処理
void CEnemyBase::HitCalc(CApple& cApple)
{
	if (m_bSurvival == true)
	{
		//リンゴの数に合わせてｈｐを減らす
		//m_iHp-= (int)cApple.GetHp();
		m_iHp -= PLAYER_ATTACK;

	}
	//ｈｐがなくなったら
	if (m_iHp <= 0)
	{
		//敵フラグを消す
		m_bSurvival = false;
		//hpを元通りに
		m_iHp = spare;

	}
}

//水場に当たった時の処理・水場を壊す
void CEnemyBase::BreakWater(CWater& cwater)
{
	m_bStopBEnemy = true;

}

//ダメージ受けたとき点滅させる処理 画像ハンドル、float透明度（０は透明１は不透明）
void CEnemyBase::Transparency(int Hndl, float Transparency)
{

	//透明度を設定
	MV1SetOpacityRate(m_iHndl, Transparency);


}




