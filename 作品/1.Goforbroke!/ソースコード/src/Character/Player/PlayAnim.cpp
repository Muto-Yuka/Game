#include "PlayAnim.h"
#include "../../MyLib/Input/Input.h"

int CPlayAnim::Key;
DINPUT_JOYSTATE CPlayAnim::input;		//コントローラー情報

CPlayAnim::CPlayAnim()
{
	Init();
}

//初期化
void CPlayAnim::Init()
{
	CBaseAnim::Init();
}

//ロード
void CPlayAnim::Load()
{
	RequestLoop(ANIMID_WAIT, 0.5f);
}

//ループ
void CPlayAnim::Loop()
{
	//パッド指定
	Key = GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//アニメーション更新
	UpdataAnim();
	//アニメーション切り替え
	AnimLoop();
	//プレイヤー更新
	Update();
}

//更新
void CPlayAnim::Update()
{
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);

	//プレイヤーの大きさを1/10に
	VECTOR scale = { 0.1f,0.1f,0.1f };
	MV1SetScale(m_iHndl, scale);
}

//ループアニメ処理
void CPlayAnim::AnimLoop()
{
	//各処理を関数ポインタに入れる
	//関数ポインタを宣言し関数をPlayerAnim配列に入れる
	void (CPlayAnim:: * PlayerAnim[])() =
	{ &CPlayAnim::ExecWait,&CPlayAnim::ExecWalk,&CPlayAnim::ExecRun,&CPlayAnim::ExecSideWalk, &CPlayAnim::ExecTake };
	//idに合わせて処理を実行
	(this->*PlayerAnim[m_sAnimData.m_iID])();
}

//待機
void CPlayAnim::ExecWait()
{
	//ものをとる
	if (CInput::IsInputDown(CInput::INPUT_TAKE) || (input.Buttons[0] > 0))
		Request(ANIMID_TAKE, 1.0f);

	//前後移動キーが押されたら
	if (CInput::IsInputDown(CInput::INPUT_UP) || CInput::IsInputDown(CInput::INPUT_DOWN))
	{
		//前進+シフトキーで走る
		if (CInput::IsInputDown(CInput::INPUT_DASH) || (input.Buttons[4] > 0))
			RequestLoop(ANIMID_RUN, 0.5f);
		else
			RequestLoop(ANIMID_WALK, 0.5f);
	}
	else if ((input.Y < 0) || (input.Y > 0))
	{
		//前進+シフトキーで走る
		if (CInput::IsInputDown(CInput::INPUT_DASH) || (input.Buttons[4] > 0))
			RequestLoop(ANIMID_RUN, 0.5f);
		//前進のみ
		else
			RequestLoop(ANIMID_WALK, 0.5f);
	}

	//右方向または左方向が押される
	if (CInput::IsInputDown(CInput::INPUT_LEFT) || CInput::IsInputDown(CInput::INPUT_RIGHT))
	{
		RequestLoop(ANIMID_SIDEWALK, 0.5f);
	}
	else if ((input.X < 0) || (input.X > 0))
	{
		RequestLoop(ANIMID_SIDEWALK, 0.5f);
	}
}

//歩き
void CPlayAnim::ExecWalk()
{
	//ものを取るアニメーション
	if (CInput::IsInputDown(CInput::INPUT_TAKE) || (input.Buttons[0] > 0))
		Request(ANIMID_TAKE, 1.0f);

	//前後移動キー
	if (CInput::IsInputDown(CInput::INPUT_UP) || CInput::IsInputDown(CInput::INPUT_DOWN))
	{
		//+シフトキーで走る
		if (CInput::IsInputDown(CInput::INPUT_DASH))
			RequestLoop(ANIMID_RUN, 0.5f);
	}
	if ((input.Y < 0) || (input.Y > 0))
	{
		//+シフトキーで走る
		if (input.Buttons[4] > 0)
			RequestLoop(ANIMID_RUN, 0.5f);
	}

	if (CInput::IsInputRelese(CInput::INPUT_UP) || CInput::IsInputRelese(CInput::INPUT_DOWN))
		RequestLoop(ANIMID_WAIT, 0.5f);

}

//走り
void CPlayAnim::ExecRun()
{
	//ものをとる
	if (CInput::IsInputDown(CInput::INPUT_TAKE) || (input.Buttons[0] > 0))
		Request(ANIMID_TAKE, 1.0f);

	//走るのをやめた
	if (CInput::IsInputRelese(CInput::INPUT_DASH))
		RequestLoop(ANIMID_WALK, 0.5f);

	//移動キーを離した
	if (CInput::IsInputRelese(CInput::INPUT_UP) || CInput::IsInputRelese(CInput::INPUT_DOWN))
		RequestLoop(ANIMID_WAIT, 0.5f);

}

//左右移動
void CPlayAnim::ExecSideWalk()
{
	//ものをとる
	if (CInput::IsInputDown(CInput::INPUT_TAKE) || (input.Buttons[0] > 0))
		Request(ANIMID_TAKE, 1.0f);

	//左右キーを離す
	if (CInput::IsInputRelese(CInput::INPUT_LEFT) || CInput::IsInputRelese(CInput::INPUT_RIGHT))
		RequestLoop(ANIMID_WAIT, 0.5f);

}

//取得
void CPlayAnim::ExecTake()
{
	//アニメ再生が終わったら
	if (m_sAnimData.m_bPlay == false)
		RequestLoop(ANIMID_WAIT, 0.5f);
}











