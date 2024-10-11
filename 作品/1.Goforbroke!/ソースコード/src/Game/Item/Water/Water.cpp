#include "Water.h"
#include "../../../Character/Player/Player.h"

//3dモデル
static const char MODEL_PATH[] = { "data/Game/Item/Water/Water.mv1" };
//水場の体力描画
static const char HP_PATH[] = { "data/Game/Item/Water/2dWaterHp.png" };
//水分不足の時に描画
static const char FOGGYPATH[] = { "data/Game/Item/Water/NeedWater.png" };


//２ｄイラストのファイルパス
#define ON_WATER_PATH	("data/Game/Mission/Water/OnWater.png")
#define UNDER_WATER_PATH	("data/Game/Mission/Water/UnderWater.png")

//ｘ初期座標
#define DRAW_ITEM_X	(50.0f)
//ｚ初期座標
#define DRAW_ITEM_Z (50.0f)
//アイテムの半径
#define ITEM_RADIUS (22.0f)
//水場の体力
#define WATER_HP	(50.f)
//水分ゲージのｙ座標
#define WATER_2D_Y			(650)		
//水分が減る時間 (速度)
#define WATER_TIME		(300)	

//コンストラクタ
CWater::CWater()
{
	Init();
}

//デストラクタ
CWater::~CWater()
{
	Exit();

	//画像削除
	DeleteGraph(m_2dHpHndl);
	DeleteGraph(m_iFoggyHndl);
	//2d画像を削除
	for (int i = 0; i < GAUGE_NUM; i++)
	{
		DeleteGraph(m_iOnHndl[i]);
		DeleteGraph(m_iUnderHndl[i]);
	}

	//数字用画像削除
	cNumber.ExitNumber();

}

//初期化
void CWater::Init()
{
	CItemBase::Init(ITEM_RADIUS);
	CItemBase::m_fRadius = ITEM_RADIUS;
	m_hp = WATER_HP;					//水場の体力
	WaterGauge = GAUGE_NUM;				//水分ゲージの表示数
	HitFrg = false;						//敵に当たってない
	m_bResult = false;
	m_iPlayerWater = 0;
	m_iFoggyHndl = -1;
	HitCount = 0;

	//スコア（数字の初期化）
	cNumber.InitNumber();
}

//ロード
void CWater::Load()
{
	//スコア数字ロード
	cNumber.LoadNumber();

	//3dモデルをロード
	if (m_iHndl == -1)
	{
		m_iHndl = MV1LoadModel(MODEL_PATH);
	}

	//2d画像をロード
	for (int i = 0; i < GAUGE_NUM; i++)
	{
		m_iOnHndl[i] = LoadGraph(ON_WATER_PATH);
		m_iUnderHndl[i] = LoadGraph(UNDER_WATER_PATH);
	}
	//水分不足画像ロード
	if (m_iFoggyHndl == -1)
	{
		m_iFoggyHndl = LoadGraph(FOGGYPATH);
	}

	//水場の体力画像ロード
	m_2dHpHndl = LoadGraph(HP_PATH);

	//水の位置を初期位置に
	m_vPos = VGet(DRAW_ITEM_X, 0.0f, DRAW_ITEM_Z);
}

//ループ
void CWater::Step()
{
	StartTime++;

	CItemBase::Step();

	//敵が水場に当たっている時
	if (HitFrg == true)
	{
		//水場の体力を減らす
		m_hp -= 0.1f;

		//体力がなくなったら
		if (m_hp <= 0)
		{
			//フラグをオフに
			m_bSurvival = false;
			HitFrg = false;
			//m_hp = WATER_HP;

		}
	}

	//一定時間経てば水分を減らす
	if (StartTime % WATER_TIME == 0)
	{
		SetWaterGauge();
	}

	//水分ゲージが０になるとリザルト
	if (GetWaterGauge() == 0)
		m_bResult = true;

	//水場の数字更新処理
	cNumber.UpdateNumber();

}

//描画
void CWater::Draw()
{

	MV1SetPosition(m_iHndl, m_vPos);

	//３ｄモデル描画
	CItemBase::Draw();


	//水場の％テージを表示する
	//水場の数字描画 描画する座標 画像サイズ
	VECTOR NumberPos = m_vPos;
	NumberPos.y += 40;
	cNumber.Draw3dNumber(NumberPos, 28.0f);

	VECTOR waterPos = m_vPos;
	waterPos.y += 10;

	float Hp = m_hp;

	//3d水場の体力ゲージ描画
	DrawModiBillboard3D(waterPos, -25.f, 0.f, Hp - 25, 0.f, Hp - 25, 20.f, -25.f, 20.f, m_2dHpHndl, TRUE);


	//水分不足時に描画
	if (WaterGauge == 1)
	{
		DrawGraph(0, 0, m_iFoggyHndl, true);
	}

	//2d水分ゲージ描画
	for (int i = 0; i < GAUGE_NUM; i++)
		DrawGraph(i * SHIFT_ITEM_PICTURE, WATER_2D_Y, m_iUnderHndl[i], true);
	for (int k = 0; k < WaterGauge; k++)
		DrawGraph(k * SHIFT_ITEM_PICTURE, WATER_2D_Y, m_iOnHndl[k], true);

	//プレイヤーが取った水を描画する
	for (int k = 0; k < m_iPlayerWater; k++)
		DrawGraph(1100, WATER_2D_Y, m_iOnHndl[k], true);

}

//水場を壊す
void CWater::HitBreakWater()
{
	//壊し始めるフラグをonに
	HitFrg = true;

}

//水場に水を戻す 引数で持っている水の数を受け取る
void CWater::HitReturnWater(int WaterNum)
{
	//水場に当たっている　かつ　プレイヤーが水を持っていたら
	if (WaterNum == 1)
	{
		//修理ボタンを押したら
		if (CheckHitKey(KEY_INPUT_Q) || CPlayer::input.Buttons[2] > 0)
		{
			if (HitCount == 0)
				//水場の％をアップする　足す
				cNumber.AddNumber(1);
			HitCount++;
		}
		else
			HitCount = 0;
	}
}

//水場を修理する　２ｄ処理
void CWater::HitRepairWater()
{
	interval++;

	//当たっている状態で取得ボタンを押す かつ　水場が生きている
	if (CheckHitKey(KEY_INPUT_E) && m_bSurvival == true)
	{
		//もともとある水分の最大値より少なかったら回復 2d画像
		if (WaterGauge < GAUGE_NUM)
		{
			WaterGauge++;

		}

	}
	else if ((CPlayer::input.Buttons[0] > 0) && (m_bSurvival == true))
	{
		//もともとある水分の最大値より少なかったら回復 2d画像
		if (WaterGauge < GAUGE_NUM)
		{
			WaterGauge++;

		}

	}

	//修理ボタンが押される
	if (CheckHitKey(KEY_INPUT_Q) || CPlayer::input.Buttons[2] > 0)
	{
		//３ｄゲージ回復
		if (m_hp < WATER_HP)
			m_hp += 0.1f;
	}
}





