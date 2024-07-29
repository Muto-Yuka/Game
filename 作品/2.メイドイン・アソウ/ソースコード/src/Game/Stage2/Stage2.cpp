#include <DxLib.h>
#include "Stage2.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"
#define PI 3.141592654

//背景
static const char BG_PATH[] = { "data/Game/Stage2/bg.png" };
//制限時間
static const int TIME_LIMIT = 1800;
//時間が減る速度　
static const int TIME_SPEED = 3;
//何回たたけばクリアか
static const int NAIL_HIT = 30;

CStage2::CStage2()
{
	Init();
}
CStage2::~CStage2()
{
	Exit();
}

//初期化
void CStage2::Init()
{
	for (int i = 0; i < tag_NUM; i++)
	{
		m_iGraph[i] = -1;
	}
	m_fRot = 0.f;
	m_iKeyCount = 0;
	m_iTime = TIME_LIMIT;
	//文字の大きさ変更
	SetFontSize(150);
	CSound::SetVolume(CSound::SOUND_STAGE2, 0.5);

}
//ロード
void CStage2::Load()
{
	m_iGraph[tag_BG] = LoadGraph(BG_PATH, true);
	m_iGraph[tag_DESK] = LoadGraph("data/Game/Stage2/desk.png", true);
	m_iGraph[tag_HAMMER] = LoadGraph("data/Game/Stage2/hammer.png", true);
	m_iGraph[tag_NAIL] = LoadGraph("data/Game/Stage2/nail.png", true);
	m_iGraph[tag_SPACE] = LoadGraph("data/Game/Stage2/Space.png", true);

	CSound::Play(CSound::SOUND_STAGE2, DX_PLAYTYPE_BACK, true);
}
//ステップ 
int  CStage2::Step()
{
	int ret = -1;

	//スペースキーでハンマーの角度変更
	if (CInput::IsInputPush(CInput::INPUT_SPACE))
	{
		m_fRot = (float)-(PI / 4);
		m_iKeyCount += 1;
	}
	if (CInput::IsInputRelese(CInput::INPUT_SPACE))
	{
		m_fRot = 0;
	}

	//時間を減らす
	m_iTime -= TIME_SPEED;

	//破棄へ進む
	if (m_iKeyCount / 2 > NAIL_HIT || m_iTime < 20)
	{
		ret = 1;
		CSound::AllStop();
	}
	return ret;

}
//描画
void CStage2::Draw()
{
	DrawGraph(0, 0, m_iGraph[tag_BG], true);		//背景
	DrawGraph(945, 540, m_iGraph[tag_NAIL], true);	//釘
	DrawGraph(0, 0, m_iGraph[tag_DESK], true);		//机
	DrawRotaGraph(1400, 600, 1.0, m_fRot, m_iGraph[tag_HAMMER], true);//ハンマー
	DrawRotaGraph(700, 550, 0.3, 0.f, m_iGraph[tag_SPACE], true);//スペースキー

	//残り時間を四角形で描画
	DrawBox(20, 10, m_iTime, 40, GetColor(255, 190, 70), TRUE);
	//何回叩いたか表示
	DrawFormatString(670, 700, GetColor(255, 51, 51), "%d", m_iKeyCount / 2);
	//〇回叩け！
	DrawFormatString(300, 50, GetColor(255, 255, 255), "%d回叩け！", NAIL_HIT);

}
//破棄
void CStage2::Exit()
{
	for (int i = 0; i < tag_NUM; i++)
		DeleteGraph(m_iGraph[i]);
}
//リザルト情報を返す 0:待機　1:クリア　2:ゲームオーバー
int CStage2::GetResult()
{
	int ret = 0;

	if (m_iKeyCount / 2 > NAIL_HIT)
		ret = 1;
	if (m_iTime < 20)
		ret = 2;

	return ret;
}


