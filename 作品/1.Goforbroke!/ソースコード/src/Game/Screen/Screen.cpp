#include "Screen.h"
#include <DxLib.h>

unsigned int color = GetColor(255, 30, 30);

#define HP_SHIFT	(28)		//どれくらいずらして描画するか
#define HP_X		(1000)		//ｈｐのｘ座標
#define HP_Y		(600)

CScreen::CScreen()
{
	Init();
}

CScreen::~CScreen()
{
	Exit();
}

void CScreen::Init()
{
	m_UpHndl = -1;
	m_AmCount = AM_TIME_COUNT;
	m_PmCount = PM_TIME_COUNT;
	m_PlayerHp = 0;

	WaterHp = 0;

	//全体のフォントサイズ変更
	SetFontSize(30);
}

void CScreen::Load()
{
	m_UpHndl = LoadGraph("data/Game/Screen/screen.png");		//画面上部表示（スコアやHPSを見やすくする・中央ターゲットポインタ）
	//フォントロード
	ChangeFont("廻想体 ネクスト UP B");


}

//常にループする処理
void CScreen::Step(int SceneId, CPlayer& cPlayer)
{
	//プレイヤーのｈｐを取得
	m_PlayerHp = cPlayer.GetPlayerHP();


	//それぞれ午前と午後の時間カウント処理
	if (SceneId == 2)
	{
		//午前
		m_AmCount--;

		if (m_PmCount < 0)
			m_PmCount = PM_TIME_COUNT;

	}
	else if (SceneId == 3)
	{
		//午後
		m_PmCount--;

		if (m_AmCount < 0)
			m_AmCount = AM_TIME_COUNT;

	}
}

//一日目の描画処理
void CScreen::Day1Draw(int SceneId)
{

	//午前の処理
	if (SceneId == 2)
	{
		DrawGraph(0, 0, m_UpHndl, TRUE);

		//タイムが０になれば描画しない
		if (m_AmCount > 0)
			DrawFormatString(400, 10, GetColor(255, 69, 0), "Time %d", m_AmCount);


	}
	//午後の処理
	else if (SceneId == 3)
	{

		DrawGraph(0, 0, m_UpHndl, TRUE);

		//DrawFormatString(200, 10, color, "残りのHP[%d]", m_PlayerHp);


		if (m_PmCount > 0)
			DrawFormatString(400, 10, GetColor(255, 69, 0), "Time %d", m_PmCount);


	}



	DrawFormatString(600, 10, GetColor(255, 0, 0), "Day1");





}

//二日目の描画処理
void CScreen::Day2Draw(int SceneId)
{
	//午前
	if (SceneId == 2)
	{
		DrawGraph(0, 0, m_UpHndl, TRUE);

		DrawFormatString(400, 10, GetColor(255, 69, 0), "Time %d", m_AmCount);

	}
	//午後
	else if (SceneId == 3)
	{

		DrawGraph(0, 0, m_UpHndl, TRUE);


		if (m_PmCount > 0)
			DrawFormatString(400, 10, GetColor(255, 69, 0), "Time %d", m_PmCount);

	}


	DrawFormatString(600, 10, GetColor(255, 0, 0), "Day2");

}

void CScreen::Exit()
{
	DeleteGraph(m_UpHndl);
}

