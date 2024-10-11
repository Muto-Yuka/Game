#include "Fade.h"
#include <DxLib.h>

CFade* CFade::m_instance = nullptr;

//インスタンス取得
CFade* CFade::GetInstance()
{
	Alloc();
	return m_instance;
}

//クラスを生成してメモリ確保
void CFade::Alloc()
{
	if (m_instance == nullptr)
	{
		m_instance = new CFade;
	}
}

//破棄
void CFade::DeleteInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

//フェードのリクエスト
//(フェードの速さ(1～255)、trueフェードインfalseフェードアウト)
void CFade::Request(float speed, bool isFadeIn)
{
	m_speed = speed;
	m_state = isFadeIn == true ? FADE_IN : FADE_OUT;
	m_cnt = isFadeIn == true ? 255.0f : 0.0f;
	m_windowX = 1280;
	m_windowY = 720;
}

//更新
void CFade::UpDate()
{
	switch (m_state)
	{
	case FADE_IN:
		m_cnt -= m_speed;
		if (m_cnt <= 0.0f) m_cnt = 0.0f;
		break;

	case FADE_OUT:
		m_cnt += m_speed;
		if (m_cnt >= 255.0f) m_cnt = 255;
		break;
	}
}

//描画
void CFade::Draw()
{
	if (m_state == FADE_NON) return;

	//アルファ値を変更して四角い画像を描画表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_cnt));
	//指定した座標で四角を作る
	DrawBox(0, 0, m_windowX, m_windowY, GetColor(0, 0, 0), TRUE);
	//ブレンドモードをもとに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//終了
bool CFade::IsEnd()
{
	bool isRed = true;

	switch (m_state)
	{
	case FADE_IN:
		//フェードイン時は値が０になったら終了
		if (m_cnt > 0.0f) isRed = false;
		break;

	case FADE_OUT:
		//フェードアウト時は値が255になったら終了
		if (m_cnt < 255.0f) isRed = false;
		break;
	}

	return isRed;
}










